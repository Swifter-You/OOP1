#include "main_wobc.h"
#include "ui_main_wobc.h"
#include <fstream>
#include <QMessageBox>
#include "CollectionWOBC_wind.h"

main_wobc::main_wobc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::main_wobc)
{
    ui->setupUi(this);
    input_prod(ui);
    input_lim_prod(ui);
    input_drinks(ui);
    this->pur_collection.input_from_file("save_pur.txt");
}

void main_wobc::input_prod(Ui::main_wobc *ui)
{
    string item;
    ifstream file("C:\prod.txt");


    if (file.is_open())
    {
        while(!file.eof())
        {
            getline(file, item);
            ui->listWidget_prod_pur->addItem(QString::fromStdString(item));
        }
        file.close();
    }
}

void main_wobc::input_drinks(Ui::main_wobc *ui)
{
    string item;
    ifstream file("C:\drinks.txt");


    if (file.is_open())
    {
        while(!file.eof())
        {
            getline(file, item);
            ui->listWidget_prod_pur_2->addItem(QString::fromStdString(item));
        }
        file.close();
    }
}

void main_wobc::input_lim_prod(Ui::main_wobc *ui)
{

    string item;
    ifstream file("C:\lim_prod.txt");


    if (file.is_open())
    {
        while(!file.eof())
        {
            getline(file, item);
            ui->listWidget_lim_prod_pur->addItem(QString::fromStdString(item));
        }
        file.close();
    }
}


main_wobc::~main_wobc()
{
    delete ui;
}

void main_wobc::on_pushButton_add_prod_pur_clicked()
{
    char *item = (char *)ui->listWidget_prod_pur->currentItem()->text().toStdString().c_str();
    while(!isdigit(*item))
        item++;
    int price_item = atoi(item);
    int amount = ui->label_amount_pur->text().toInt();
    ui->label_amount_pur->setNum(price_item + amount);
    ui->listWidget_check_pur->addItem(ui->listWidget_prod_pur->currentItem()->text());
}

void main_wobc::on_pushButton_add_drinks_pur_clicked()
{
    char *item = (char *)ui->listWidget_prod_pur_2->currentItem()->text().toStdString().c_str();
    while(!isdigit(*item))
        item++;
    int price_item = atoi(item);
    int amount = ui->label_amount_pur->text().toInt();
    ui->label_amount_pur->setNum(price_item + amount);
    ui->listWidget_check_pur->addItem(ui->listWidget_prod_pur_2->currentItem()->text());
}

void main_wobc::on_pushButton_add_lim_prod_pur_clicked()
{
    char *item = (char *)ui->listWidget_lim_prod_pur->currentItem()->text().toStdString().c_str();
    while(!isdigit(*item))
        item++;
    int price_item = atoi(item);
    int amount = ui->label_amount_pur->text().toInt();
    ui->label_amount_pur->setNum(price_item + amount);
    ui->listWidget_check_pur->addItem(ui->listWidget_lim_prod_pur->currentItem()->text());

}

void main_wobc::on_pushButton_check_del_pur_clicked()
{
    char *item = (char *)ui->listWidget_check_pur->currentItem()->text().toStdString().c_str();
    while(!isdigit(*item))
        item++;
    int price_item = atoi(item);
    int amount = ui->label_amount_pur->text().toInt();
    ui->label_amount_pur->setNum(amount - price_item);
    ui->listWidget_check_pur->takeItem(ui->listWidget_check_pur->currentRow());

}

void main_wobc::on_pushButton_back_pur_clicked()
{

    QMessageBox::StandardButton save = QMessageBox::question(this, "Save", "Save collection?", QMessageBox::Yes | QMessageBox::No);
    if(save == QMessageBox::No)
    {
        this->pur_collection.clear();
    }
    pur_save_data(this->pur_collection);
    this->close();
}

void main_wobc::on_pushButton_pay_pur_clicked()
{
    QMessageBox::information(this,"Purchase", "Thanks for you visit!\nTotal amount is " + ui->label_amount_pur->text());
    char buffer[80];
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    char* format_time = "%X";
    char* format_day = "%d:%m:%Y";
    strftime(buffer, 80, format_time, timeinfo);
    string time = string(buffer);
    strftime(buffer, 80, format_day, timeinfo);
    string date = string(buffer);
    auto pur = new purchase(time,date,ui->label_amount_pur->text().toInt());
    this->pur_collection.push(*pur);


    ui->listWidget_check_pur->clear();
    ui->label_amount_pur->setText(QString::number(0));
}

void main_wobc::on_pushButton_about_pur_clicked()
{
    collectionWOBC_wind window;
    window.set_dialog_coll(&this->pur_collection);
    window.setModal(true);
    window.exec();
}
