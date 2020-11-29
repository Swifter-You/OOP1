#ifndef MAIN_WOBC_H
#define MAIN_WOBC_H

#include <QDialog>
#include "collection.h"

namespace Ui {
class main_wobc;
}

class main_wobc : public QDialog
{
    Q_OBJECT

public:
    explicit main_wobc(QWidget *parent = nullptr);
    void input_prod(Ui::main_wobc *ui);
    void input_drinks(Ui::main_wobc *ui);
    void input_lim_prod(Ui::main_wobc *ui);
    ~main_wobc();

private slots:
    void on_pushButton_add_prod_pur_clicked();

    void on_pushButton_add_drinks_pur_clicked();

    void on_pushButton_add_lim_prod_pur_clicked();

    void on_pushButton_check_del_pur_clicked();

    void on_pushButton_back_pur_clicked();

    void on_pushButton_pay_pur_clicked();

    void on_pushButton_about_pur_clicked();

private:
    Queue pur_collection;
    Ui::main_wobc *ui;
};

#endif // MAIN_WOBC_H
