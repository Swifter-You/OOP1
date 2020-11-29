#include "purchase.h"
#include <string>

purchase::purchase()
{
    this->time = "00:00:00";
    this->date = "01:01:1970";
    this->amount = 0;
}

purchase::purchase(const string &time, const string &date, int amount)
{
    if (check_date(date) && check_time(time) && amount >= 0)
    {
        this->date = date;
        this->time = time;
        this->amount = amount;
    }
    else
    {
        this->time = "00:00:00";
        this->date = "01:01:1970";
        this->amount = 0;
    }
}

purchase::purchase(const purchase &other)
{
    this->date = other.date;
    this->time = other.time;
    this->amount = other.amount;
}

const string &purchase::get_time() const
{
    return this->time;
}



const string &purchase::get_date() const
{
    return this->date;
}


 int purchase::get_amount() const
{
    return this->amount;
}

void purchase::set_time(const string& value)
{
    if(check_time(value))
        this->time = value;
    else
        this->time = "00:00:00";
}

void purchase::set_date(const string& value)
{
    if(check_date(value))
        this->date = value;
    else
        this->date = "01:01:1970";
}


void purchase::set_amount(const int value)
{
    if(value >= 0)
        this->amount = value;
    else
        this->amount = 0;
}

string purchase::get_data(const string &type) const
{
    if(type == "time")
        return this->get_time();
    if(type == "date")
        return this->get_date();
    return " ";
}

int purchase::check_time(const string &s) const
{
    if(s.size() != 8)
        return 0;
    if(!(isdigit(s[0]) & isdigit(s[1]) & ((s[0] - '0')*10 + s[1] - '0') < 24))
        return 0;
    if(!(isdigit(s[3]) & isdigit(s[4]) & ((s[3] - '0')*10 + s[4] - '0') < 60))
        return 0;
    if(!(isdigit(s[6]) & isdigit(s[7]) & ((s[6] - '0')*10 + s[7] - '0') < 60))
        return 0;
    return 1;
}

int purchase::check_date(const string &s) const
{
    if(s.size() != 10)
        return 0;
    if(!(isdigit(s[0]) & isdigit(s[1]) & ((s[0] - '0')*10 + s[1] - '0') < 32))
        return 0;
    if(!(isdigit(s[3]) & isdigit(s[4]) & ((s[3] - '0')*10 + s[4] - '0') < 13))
        return 0;
    if(!(isdigit(s[6]) & isdigit(s[7]) & isdigit(s[8]) & isdigit(s[9])))
        return 0;
    int day = (s[0] - '0')*10 + s[1] - '0';
    int month = (s[3] - '0')*10 + s[4] - '0';
    int year = (s[6] - '0')*1000 + (s[7] - '0')*100 + (s[8] - '0')*10 + (s[9] - '0');
    if (day == 0 || month == 0 || year == 0)
        return 0;
    if (day > 28 && month == 2 && year % 4)
        return 0;
    if (day > 29 && month == 2 && year % 4 == 0)
        return 0;
    if (day == 31)
    {
        if(month % 2 && month > 8)
            return 0;
        else if (month % 2 == 0 && month < 8)
            return 0;
    }
    if (day == 30)
    {
        if(month % 2 && month < 8)
            return 0;
        else if (month % 2 == 0 && month > 8)
            return 0;
    }
    return 1;
}


