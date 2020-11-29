#include "mainwindow.h"

#include <QApplication>

#include "purchase.h"
#include "test.h"
#include "collection.h"
#include "main_card.h"
int main(int argc, char *argv[])
{
 //   test_class();
   // test_collection_class();
    //test_bc_class();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
