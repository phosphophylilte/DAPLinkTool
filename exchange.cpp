#include "exchange.h"
#include "ui_exchange.h"
#include "publicstack.h"

Exchange::Exchange(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Exchange)
{
    ui->setupUi(this);
}

Exchange::~Exchange()
{
    delete ui;
}

void Exchange::on_closeButton_clicked()
{
    this->close();
}

void Exchange::on_exchangeButton_clicked()
{
    // 确认转化标志
    eventFlag |= 0x40;

    // 转换类型标志
    eventFlag |= (ui->comboBox->currentIndex())<<5;
    this->close();
}
