#include "mainwindow.h"
#include "publicstack.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon(":/resource/favicon.ico"));
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    QFile cssFile(":/Qss/resource/style.css");

    // cmd进程变量
    process = new QProcess(this);


    cssFile.open(QFile::ReadOnly);
    if(cssFile.isOpen())
        {
            QString css = QLatin1String(cssFile.readAll());
            qApp->setStyleSheet(css);
            cssFile.close();
        }
        else
        {
            qDebug() << "无法打开文件";
        }

    // 连接 QProcess 的信号，获取输出内容
    connect(process, &QProcess::readyReadStandardOutput, this, &MainWindow::cmdProcessOutput);

    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 2025-3-5：通过按键选择磁盘内文件
void MainWindow::on_ChooseFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开文件"), "C:/", tr("All files(*.*)"));
    if(fileName.isEmpty())
    {
        QMessageBox::warning(this, "注意", "打开失败");
    }
    else
    {
        ui->FilePathLine->setText(fileName);
    }
}

// 2025-3-5：重写dragEnterEvent函数，开放拖拽功能
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    //解析路径
    if(event->mimeData()->hasUrls())
    {
        const QList<QUrl> urls = event->mimeData()->urls();
        if(urls.size() == 1 && (urls[0].toLocalFile().endsWith(".hex")||urls[0].toLocalFile().endsWith(".bin"))){
            event->acceptProposedAction();
        }
    }
}

// 2025-3-5：重写dropEvent函数，实现拖拽放入功能
void MainWindow::dropEvent(QDropEvent *event) {
    const QList<QUrl> urls = event->mimeData()->urls();
    if (urls.size() == 1)
    {
        QString filePath = urls[0].toLocalFile();
        if (filePath.endsWith(".hex") || filePath.endsWith(".bin"))
        {
            ui->FilePathLine->setText(filePath);
        }
    }
}

// 利用openocd转换
void MainWindow::on_ExchangeButton_clicked()
{
    Exchange *obj = new Exchange();
    statuShow("Exchanging...");
    obj->show();

}

// 利用openocd烧录
void MainWindow::on_ProgramButton_clicked()
{
    if(ui->FilePathLine->text().isEmpty())
    {
        QMessageBox::warning(this, "注意", "文件路径不能为空");
        return;
    }
    //失能按钮
    statuShow("Programming...");
    ui->ProgramButton->setDisabled(true);

    //清除标志位bit0
    eventFlag &= ~0x80;

    //设置新弹出的窗口为销毁属性
    Programmer *obj = new Programmer();
    obj->setAttribute(Qt::WA_DeleteOnClose);

    //新建QEventLoop，窗口弹出后将槽函数堵塞
    QEventLoop loop;

    //绑定信号，Programmer对象销毁时结束loop
    connect(obj, &Programmer::destroyed, &loop, &QEventLoop::quit);

    //显示窗口，开始堵塞
    obj->show();
    loop.exec();

    //结束堵塞后使能窗口
    ui->ProgramButton->setDisabled(false);

    //提取字符串，发送烧录指令
    QString interfaceName = ui->interfaceCfg->currentText();
    QString targetName = ui->targetCfg->currentText();
    QString downloadFileName = ui->FilePathLine->text();

    if(writeFlashSure)
    {
            ui->textEdit->setText(" ");
            QString commandProgrammer = "openocd -f interface/"
            + interfaceName + ".cfg -f target/"
            + targetName + ".cfg -c \"program "
            + downloadFileName + " verify reset exit "
            + startAddress + "\"";

            ui->textEdit->insertPlainText(commandProgrammer);

            // 设置 QProcess 隐藏 CMD 窗口
            process->setProcessChannelMode(QProcess::MergedChannels);  // 合并标准输出和错误输出
            process->start(commandProgrammer);  // 替换为你的 CMD 命令
    }

}


// 状态栏显示函数
void MainWindow::statuShow(QString string)
{
    statusBar()->showMessage(string);
}

// 命令行打印函数
void MainWindow::cmdProcessOutput()
{
    while (process->canReadLine()) {
                QString output = process->readLine().trimmed();
                appendColoredText(output);
            }
}

void MainWindow::appendColoredText(const QString &text) {
        if (text.startsWith("Info :")) {
            ui->textEdit->setTextColor(Qt::yellow);
        } else if (text.startsWith("Error:") || text.startsWith("** OpenOCD init failed **")) {
            ui->textEdit->setTextColor(Qt::red);
        } else {
            ui->textEdit->setTextColor(Qt::white);
        }
        ui->textEdit->append(text);
}
