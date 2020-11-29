#include "main_card.h"
#include "ui_dialog.h"
#include <fstream>
#include <string>
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>
#include "bonus_card.h"
#include <ctime>
#include <iostream>
#include "collection_wind.h"

using namespace std;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    input_prod(ui);
    input_lim_prod(ui);
    input_drinks(ui);
    this->bc_collection.bc_input_from_file("save_bc.txt");
}

void Dialog::input_prod(Ui::Dialog *ui)
{
    string item;
    ifstream file("C:\prod.txt");


    if (file.is_open())
    {
        while(!file.eof())
        {
            getline(file, item);
            ui->listWidget_prod->addItem(QString::fromStdString(item));
        }
        file.close();
    }
}

void Dialog::input_drinks(Ui::Dialog *ui)
{
    string item;
    ifstream file("C:\drinks.txt");


    if (file.is_open())
    {
        while(!file.eof())
        {
            getline(file, item);
            ui->listWidget_prod_2->addItem(QString::fromStdString(item));
        }
        file.close();
    }
}

void Dialog::input_lim_prod(Ui::Dialog *ui)
{

    string item;
    ifstream file("C:\lim_prod.txt");


    if (file.is_open())
    {
        while(!file.eof())
        {
            getline(file, item);
            ui->listWidget_lim_prod->addItem(QString::fromStdString(item));
        }
        file.close();
    }
}
Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_add_prod_clicked()
{
    char *item = (char *)ui->listWidget_prod->currentItem()->text().toStdString().c_str();
    while(!isdigit(*item))
        item++;
    int price_item = atoi(item);
    int amount = ui->label_amount->text().toInt();
    ui->label_amount->setNum(price_item + amount);
    ui->listWidget_check->addItem(ui->listWidget_prod->currentItem()->text());
}

void Dialog::on_pushButton_add_drinks_clicked()
{
    char *item = (char *)ui->listWidget_prod_2->currentItem()->text().toStdString().c_str();
    while(!isdigit(*item))
        item++;
    int price_item = atoi(item);
    int amount = ui->label_amount->text().toInt();
    ui->label_amount->setNum(price_item + amount);
    ui->listWidget_check->addItem(ui->listWidget_prod_2->currentItem()->text());
}

void Dialog::on_pushButton_add_lim_prod_clicked()
{
    char *item = (char *)ui->listWidget_lim_prod->currentItem()->text().toStdString().c_str();
    while(!isdigit(*item))
        item++;
    int price_item = atoi(item);
    int amount = ui->label_amount->text().toInt();
    ui->label_amount->setNum(price_item + amount);
    ui->listWidget_check->addItem(ui->listWidget_lim_prod->currentItem()->text());
}

void Dialog::on_pushButton_check_del_clicked()
{
    char *item = (char *)ui->listWidget_check->currentItem()->text().toStdString().c_str();
    while(!isdigit(*item))
        item++;
    int price_item = atoi(item);
    int amount = ui->label_amount->text().toInt();
    ui->label_amount->setNum(amount - price_item);
    ui->listWidget_check->takeItem(ui->listWidget_check->currentRow());
}


purchase* date_30()
{
    char buffer[80];
    time_t seconds = time(NULL) - 2592000;
    tm* timeinfo = localtime(&seconds);
    char* format_time = "%X";
    char* format_day = "%d:%m:%Y";
    strftime(buffer, 80, format_time, timeinfo);
    string time = string(buffer);
    strftime(buffer, 80, format_day, timeinfo);
    string date = string(buffer);
    auto pur = new purchase(time,date,0);
    return pur;
}

void curr_date(string *time_c, string *date_c)
{
    char buffer[80];
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    char* format_time = "%X";
    char* format_day = "%d:%m:%Y";
    strftime(buffer, 80, format_time, timeinfo);
    *time_c = string(buffer);
    strftime(buffer, 80, format_day, timeinfo);
    *date_c = string(buffer);
}


int check_lim(Ui::Dialog *ui)
{
    int len = ui->listWidget_check->count();
    int len_lim = ui->listWidget_lim_prod->count();

    for (int i = 0; i < len; i++)
    {
        string check_prod = ui->listWidget_check->item(i)->text().toStdString();
        for (int j = 0; j < len_lim;j++)
            if (check_prod == ui->listWidget_lim_prod->item(j)->text().toStdString())
                return 1;
    }
    return 0;
}

void Dialog::on_pushButton_pay_clicked()
{
    string num_card = ui->lineEdit_num_card->text().toStdString();
    if (num_card == "")
        QMessageBox::critical(this,"Card number", "Please, input bonus card");
    else
    {
        int i = 0;
        bool ok;
        while(i < this->bc_collection.size() && this->bc_collection.get_iterator()[i]->get_data("card") != num_card)
            i++;

        if (i == this->bc_collection.size())
        {
            QString text = QInputDialog::getText(this, tr("First visit"),
                                                     tr("Please, write a telephone num to activate your b.c.:"), QLineEdit::Normal,
                                                     "+7", &ok);
            if (ok && !text.isEmpty() && text.toStdString() != "+7" && text.toStdString().size() == 12)
            {
                QMessageBox::information(this,"Purchase", "Thanks for you visit!\nTotal amount is " + ui->label_amount->text());
                char buffer[80];
                time_t seconds = time(NULL);
                tm* timeinfo = localtime(&seconds);
                char* format_time = "%X";
                char* format_day = "%d:%m:%Y";
                strftime(buffer, 80, format_time, timeinfo);
                string time = string(buffer);
                strftime(buffer, 80, format_day, timeinfo);
                string date = string(buffer);
                auto card = new bonus_card(time,date,ui->label_amount->text().toInt(),
                           num_card, text.toStdString());
                this->bc_collection.push(*card);
            }
            else
                QMessageBox::critical(this,"Card number", "Incorrect telephone num.\nPlease try to pay one more time");

        }
        else
        {
            int flag = 0;
            int count = 0;
            int sum = 0;
            purchase *date30 = date_30();
            while(i < this->bc_collection.size())
            {
                if (this->bc_collection.get_iterator()[i]->get_data("card") == num_card)
                    if(this->bc_collection.get_iterator()[i]->get_data("tele") != "+7")
                    {
                        count++;
                        sum +=this->bc_collection.get_iterator()[i]->get_amount();
                        if (sum >= 500 && count == 5 && check_lim(ui) &&
                                this->bc_collection.check_queue_date(*date30,*this->bc_collection.get_iterator()[i]))
                        {

                            string time;
                            string date;
                            string tele = this->bc_collection.get_iterator()[i]->get_data("tele");
                            flag = 1;
                            int amount = ui->label_amount->text().toInt();

                            amount = amount * 0.9;
                            curr_date(&time, &date);
                            auto card = new bonus_card(time,date,amount, num_card, tele);
                            this->bc_collection.push(*card);
                            QMessageBox::information(this,"Purchase", "You achieve all points!\n"
                                                                      "Therefore we will have 10% discount\n"
                                                                     "Total amount will be " + QString::number(amount));
                            delete date30;
                        }
                    }
                i++;
            }
            if (!flag)
                QMessageBox::information(this,"Purchase", "Thanks for you visit!\nYou don't achieve all points\nTotal amount is " + ui->label_amount->text());
        }
    }
    ui->listWidget_check->clear();
    ui->label_amount->setText(QString::number(0));
}

void Dialog::on_pushButton_num_card_ok_clicked()
{
   string input_card = ui->lineEdit_num_card->text().toStdString();
   int i = 0;
   while(i < 12 && i < input_card.size())
   {
       if (!isdigit(input_card.c_str()[i]))
       {
           QMessageBox::critical(this,"Card number", "Please, input correct bonus card");
           break;
       }
       i++;
   }
   if (i == 12)
       QMessageBox::information(this,"Card number", "You input bonus card!");
   else
       QMessageBox::critical(this,"Card number", "Please, input correct bonus card");
}

void Dialog::on_pushButton_about_clicked()
{
    collection_wind window;
    window.set_dialog_coll(&this->bc_collection);
    window.setModal(true);
    window.exec();
}

void Dialog::on_pushButton_clicked()
{
    QMessageBox::StandardButton save = QMessageBox::question(this, "Save", "Save collection?", QMessageBox::Yes | QMessageBox::No);
    if(save == QMessageBox::No)
    {
        bc_collection.clear();
    }
    bc_save_data(bc_collection);
    this->close();
}


