#ifndef COLLECTIONWOBC_WIND_H
#define COLLECTIONWOBC_WIND_H

#include <QDialog>
#include <collection.h>

namespace Ui {
class collectionWOBC_wind;
}

class collectionWOBC_wind : public QDialog
{
    Q_OBJECT

public:
    explicit collectionWOBC_wind(QWidget *parent = nullptr);
    void set_dialog_coll(Queue *coll){this->pur_collection_dial = coll;}
    ~collectionWOBC_wind();

private slots:

    void on_view_collection_clicked();

    void on_delete_first_clicked();

    void on_delete_queue_clicked();

    void on_size_clicked();

    void on_amount_ok_clicked();

    void on_file_input_ok_clicked();

    void on_file_output_ok_clicked();



private:
    Queue pur_collection;
    Queue *pur_collection_dial;
    Ui::collectionWOBC_wind *ui;
};
void pur_save_data(const Queue& col);

#endif // collectionWOBC_wind_H
