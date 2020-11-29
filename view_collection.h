#ifndef VIEW_COLLECTION_H
#define VIEW_COLLECTION_H

#include <QDialog>
#include "collection.h"

namespace Ui {
class view_collection;
}

class view_collection : public QDialog
{
    Q_OBJECT

public:
    explicit view_collection(QWidget *parent = nullptr);
    void insert_data(Queue* collection, int size) const;
    ~view_collection();

private slots:
    void on_pushButton_clicked();

private:
    Ui::view_collection *ui;
};

#endif // VIEW_COLLECTION_H
