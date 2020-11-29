#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <string>
#include <stdlib.h>
#include <view_collection.h>
#include <QStandardItem>
#include <QStandardItemModel>
#include "bonus_card.h"
#include "CollectionWOBC_wind.h"
#include "collection_wind.h"
#include "main_card.h"
#include "main_wobc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_bc_clicked()
{
    Dialog window;
    //collection_wind window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_pushButton_pur_clicked()
{
    main_wobc window;
    //hide();
    //purchase_window window;
    window.setModal(true);
    window.exec();
}
