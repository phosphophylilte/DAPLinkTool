#include "programmer.h"
#include "ui_programmer.h"
#include "mainwindow.h"
#include "publicstack.h"

Programmer::Programmer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Programmer)
{
    ui->setupUi(this);
}

Programmer::~Programmer()
{
    delete ui;
}

void Programmer::on_pushButton_clicked()
{
//    program_mutex.unlock();
    this->close();
}

void Programmer::on_pushButton_2_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "注意", "起始地址不能为空");
        return;
    }
    startAddress = ui->lineEdit->text();
    eventFlag |= 0x80;
    this->close();
}
