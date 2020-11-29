#include "CollectionWOBC_wind.h"
#include "ui_collectionWOBC_wind.h"
#include <QMessageBox>
#include <string>
#include <stdlib.h>
#include <view_collection.h>
#include <QStandardItem>
#include <QStandardItemModel>
#include "bonus_card.h"
#include "mainwindow.h"
#include <fstream>

collectionWOBC_wind::collectionWOBC_wind(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::collectionWOBC_wind)
{
    ui->setupUi(this);
    this->pur_collection.input_from_file("pur_save.txt");
}



void collectionWOBC_wind::on_view_collection_clicked()
{
    if(this->pur_collection.get_iterator() && this->pur_collection.size())
    {
        view_collection window;
        window.setModal(true);
        window.insert_data(&this->pur_collection, this->pur_collection.size());
        window.exec();
    }
    else
        QMessageBox::critical(this,"Show", "There is no data to show");

}

void collectionWOBC_wind::on_delete_first_clicked()
{
    if(this->pur_collection.get_iterator() && this->pur_collection.size())
    {
        this->pur_collection.pop();
        this->pur_collection_dial->pop();
        QMessageBox::information(this, "Pop", "You pop first purchase");
    }
    else
        QMessageBox::critical(this,"Pop", "There is no data to pop");
}

void collectionWOBC_wind::on_delete_queue_clicked()
{
    if(this->pur_collection.get_iterator() && this->pur_collection.size())
    {
        this->pur_collection.clear();
        this->pur_collection_dial->clear();
        QMessageBox::information(this, "Clean", "You delete all queue");
    }
    else
        QMessageBox::critical(this,"Clear", "There is no data to clean");
}

void collectionWOBC_wind::on_size_clicked()
{
    if(this->pur_collection.get_iterator() && this->pur_collection.size())
    {
        QMessageBox::information(this, "Size", "The size of the queue is " + QString::number(this->pur_collection.size()));
    }
    else
        QMessageBox::critical(this,"Size", "There is no queue");
}



void collectionWOBC_wind::on_amount_ok_clicked()
{
    if(this->pur_collection.get_iterator() && this->pur_collection.size())
    {
        std:: string time_from  = ui->amount_time_from->text().toStdString();
        std:: string date_from  = ui->amount_date_from->text().toStdString();
        std:: string time_to  = ui->amount_time_to->text().toStdString();
        std:: string date_to  = ui->amount_date_to->text().toStdString();
        QMessageBox::information(this, "Sum", "The total amount in this period is " + QString::number(this->pur_collection.sum(time_from, date_from,time_to,date_to)));
    }
    else
        QMessageBox::critical(this,"Sum", "There is no queue");
}

void collectionWOBC_wind::on_file_input_ok_clicked()
{
    this->pur_collection.input_from_file(ui->file_input_name->text().toStdString());
    this->pur_collection_dial->input_from_file(ui->file_input_name->text().toStdString());
    QMessageBox::information(this, "Input from file", "Success input from file");
}

void collectionWOBC_wind::on_file_output_ok_clicked()
{
    if(this->pur_collection.get_iterator() && this->pur_collection.size())
    {
        this->pur_collection.output_to_file(ui->file_output_name->text().toStdString());
        QMessageBox::information(this, "Output to file", "Success output to file");
    }
    else
        QMessageBox::critical(this,"Output to file", "There is no queue");
}

collectionWOBC_wind::~collectionWOBC_wind()
{
    delete ui;
}

void pur_save_data(const Queue& col)
{
    ofstream fout("pur_save.txt");
    for(int i = 0;i < col.get_count();i++)
    {
        fout << col.get_iterator()[i]->get_time()<< endl;
        fout << col.get_iterator()[i]->get_date() << endl;
        fout << col.get_iterator()[i]->get_amount() << endl << endl;
    }
    fout.close();
}

//void collectionWOBC_wind::on_pushButton_clicked()
//{

//    QMessageBox::StandardButton save = QMessageBox::question(this, "Save", "Save collection?", QMessageBox::Yes | QMessageBox::No);
//    if(save == QMessageBox::No)
//    {
//        this->pur_collection.clear();
//    }
//    pur_save_data(this->pur_collection);
//    this->close();
//}
