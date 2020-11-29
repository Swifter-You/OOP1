#ifndef COLLECTION_H
#define COLLECTION_H
#include <string>
#include "purchase.h"
using namespace std;

class Queue
{
public:
    Queue();
    Queue(purchase &pur);
    Queue(const Queue &other);
    int push(purchase &pur);
    int pop();
    int clear();
    int size() const;
    int sum(const string &time_from, const string &date_from, const string &time_to, const string &date_to) const;
    int input_from_file(const string &name);
    int bc_input_from_file(const string &name);
    int output_to_file(const string &name);
    ~Queue();
    purchase** get_iterator() const {return this->queue;}
    int get_count() const {return  this->count;}
    int check_queue_date(const purchase &prev,const purchase &curr) const;
private:
    int equal(const Queue& curr) const;
    purchase **queue;
    int count;
};

#endif // COLLECTION_H
