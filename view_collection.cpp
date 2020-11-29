#include "view_collection.h"
#include "ui_view_collection.h"
#include "collection.h"
#include <QStandardItem>
#include <QStandardItemModel>

view_collection::view_collection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view_collection)
{
    ui->setupUi(this);
}

view_collection::~view_collection()
{
    delete ui;
}

void view_collection::on_pushButton_clicked()
{
    hide();
}

void view_collection::insert_data(Queue* collection, int size) const
{
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;
    for (int i = 0; i < size;i++)
    {
        item = new QStandardItem(QString("#" + QString::number(i+1)));
        model->appendRow(item);
        item = new QStandardItem(QString(QString::fromStdString(collection->get_iterator()[i]->get_data("date"))));
        model->appendRow(item);
        item = new QStandardItem(QString(QString::fromStdString(collection->get_iterator()[i]->get_data("time"))));
        model->appendRow(item);
        item = new QStandardItem(QString(QString::number(collection->get_iterator()[i]->get_amount())));
        model->appendRow(item);
        item = new QStandardItem(QString(QString::fromStdString(collection->get_iterator()[i]->get_data("card"))));
        model->appendRow(item);
        item = new QStandardItem(QString(QString::fromStdString(collection->get_iterator()[i]->get_data("tele"))));
        model->appendRow(item);
        item = new QStandardItem(QString("   "));
        model->appendRow(item);
    }
    ui->listView->setModel(model);
}
