#include "exchange.h"
#include "ui_exchange.h"

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
