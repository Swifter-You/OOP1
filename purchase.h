#ifndef PURCHASE_H
#define PURCHASE_H
#include <string>
using namespace std;

class purchase
{
public:
    purchase();
    purchase(const string &time,const string& date , int amount);
    purchase(const purchase &other);
    const string& get_time() const;
    const string& get_date() const;
    int get_amount() const;
    void set_time(const string& value);
    void set_date(const string& value);
    void set_amount(const int value);
    virtual string get_data(const string& type) const;
private:
    int check_time(const string &s) const;
    int check_date(const string &s) const;
    string time;
    string date;
    float amount;
};

#endif // PURCHASE_H
