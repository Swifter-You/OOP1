#ifndef COLLECTION_WIND_H
#define COLLECTION_WIND_H

#include <QDialog>
#include <collection.h>
#include "main_card.h"
namespace Ui {
class collection_wind;
}

class collection_wind : public QDialog
{
    Q_OBJECT

public:
    explicit collection_wind(QWidget *parent = nullptr);
    void set_dialog_coll(Queue *coll){this->bc_collectiom_dial = coll;}
    ~collection_wind();

private slots:



    void on_bc_view_collection_clicked();

    void on_bc_size_clicked();

    void on_bc_delete_queue_clicked();

    void on_bc_delete_first_clicked();

    void on_bc_amount_ok_clicked();

    void on_bc_file_input_ok_clicked();

    void on_bc_file_output_ok_clicked();



private:
    Queue bc_collection;
    Ui::collection_wind *ui;
    Queue *bc_collectiom_dial;
};
void bc_save_data(const Queue& col);

#endif // COLLECTION_WIND_H
