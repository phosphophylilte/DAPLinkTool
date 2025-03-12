#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include <QMainWindow>

namespace Ui {
class Programmer;
}

class Programmer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Programmer(QWidget *parent = nullptr);
    ~Programmer();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Programmer *ui;
};

#endif // PROGRAMMER_H
