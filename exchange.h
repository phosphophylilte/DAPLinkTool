#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <QMainWindow>

namespace Ui {
class Exchange;
}

class Exchange : public QMainWindow
{
    Q_OBJECT

public:
    explicit Exchange(QWidget *parent = nullptr);
    ~Exchange();

private slots:
    void on_closeButton_clicked();

    void on_exchangeButton_clicked();

private:
    Ui::Exchange *ui;
};

#endif // EXCHANGE_H
