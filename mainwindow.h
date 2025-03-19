#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QEventLoop>
#include <QProcess>
#include <QByteArray>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qdrag.h>
#include "programmer.h"
#include "exchange.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void statuShow(QString string);

signals:
    void fileNameSignals(QString string);

private slots:
    void on_ChooseFileButton_clicked();

    void on_ExchangeButton_clicked();

    void on_ProgramButton_clicked();

    void cmdProcessOutput();

    void appendColoredText(const QString &text);

private:
    QProcess *process;
    void dragEnterEvent (QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
