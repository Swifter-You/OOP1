#include "collection.h"
#include "bonus_card.h"
#include <iostream>
#include <fstream>
#include <string.h>



Queue::Queue()
{
    this->queue = nullptr;
    this->count = 0;
}

Queue::Queue(purchase &pur)
{
    this->queue = new purchase*[1];
    *this->queue = &pur;
    this->count = 1;
}

Queue::Queue(const Queue &other)
{
    if(other.queue)
    {
        this->queue = new purchase*[other.count];
        this->count = other.count;
        for(int i = 0; i < this->count; i++)
            this->queue[i] = other.queue[i];
    }
    else
    {
        this->queue = nullptr;
        this->count = 0;
    }

}

int Queue::push(purchase &pur)
{
    if (this->queue && this->size() != 0)
    {
        if (check_queue_date(*this->queue[this->count -1], pur))
        {
            this->count++;
            purchase **pc = new purchase*[this->count];
            for(int i = 0; i < this->count - 1; i++)
                pc[i] = this->queue[i];
            delete [] this->queue;
            pc[this->count - 1] = &pur;
            this->queue = pc;
        }
    }
    else
    {
        this->count++;
        purchase **pc = new purchase*[this->count];
        pc[this->count - 1] = &pur;
        this->queue = pc;
    }
    return 1;
}

int Queue::pop()
{
    if (this->count > 1)
    {
        this->count--;
        purchase **pc = new purchase*[this->count];
        for(int i = 0; i < this->count; i++)
            pc[i] = this->queue[i+1];
        delete [] this->queue;
        this->queue = pc;
    }
    else
    {
        this->count = 0;
        this->queue = nullptr;
    }
    return 1;
}

int Queue::clear()
{
    if (this->queue)
    {
        delete [] this->queue;
        this->queue = nullptr;
        this->count = 0;
    }
    return 1;
}

int Queue::size() const
{
    return this->count;
}

int Queue::sum(const string &time_from, const string &date_from, const string &time_to, const string &date_to) const
{
    purchase pur_from(time_from, date_from,0);
    purchase pur_to(time_to, date_to,0);
    int count = 0;
    for(int i = 0; i < this->count; i++)
        if(check_queue_date(pur_from, *this->queue[i]) && check_queue_date(*this->queue[i], pur_to))
            count += this->queue[i]->get_amount();
    return count;
}

int Queue::input_from_file(const string &name)
{
    string time;
    string date;
    int amount;
    ifstream file(name);

    if(this->queue)
    {
        delete [] this->queue;
        this->queue = nullptr;
        this->count = 0;
    }
    if (file.is_open())
    {
        while(!file.eof())
        {
            file >> time;
            file >> date;
            file >> amount;
            auto pur = new purchase(time, date, amount);
            if (!(pur->get_time() == "00:00:00" && pur->get_date() == "01:01:1970" && pur->get_amount() == 0))
                this->push(*pur);
        }
        file.close();
    }

    return 1;
}

int Queue::bc_input_from_file(const string &name)
{
    string time;
    string date;
    int amount;
    string number;
    string telenum;
    ifstream file(name);

    if(this->queue)
    {
        delete [] this->queue;
        this->queue = nullptr;
        this->count = 0;
    }
    if (file.is_open())
    {
        while(!file.eof())
        {
            file >> time;
            file >> date;
            file >> amount;
            file >> number;
            file >> telenum;
            auto card = new bonus_card(time, date, amount,number,telenum);
            if (!(card->get_time() == "00:00:00" && card->get_date() == "01:01:1970" && card->get_amount() == 0 && card->get_bonus_card_number() == "000000000000"))
                this->push(*card);
        }
        file.close();
    }

    return 1;
}

int Queue::output_to_file(const string &name)
{
    ofstream fout(name);

    for(int i = 0;i < this->count;i++)
    {
        fout << "#" << i+1 << endl;
        fout << this->queue[i]->get_time()<< endl;
        fout << this->queue[i]->get_date() << endl;
        fout << this->queue[i]->get_amount() << endl;
        fout << this->queue[i]->get_data("card") << endl;
        fout << this->queue[i]->get_data("tele") << endl <<endl;
    }
    fout.close();
    return 1;
}


int Queue::equal(const Queue &curr) const
{
    if(this->get_count() != curr.get_count())
            return 0;
    for (int i = 0; i < this->get_count();i++)
        if (!(this->get_iterator()[1]->get_date() == curr.get_iterator()[1]->get_date() && this->get_iterator()[1]->get_time() == curr.get_iterator()[1]->get_time() && this->get_iterator()[1]->get_amount() == curr.get_iterator()[1]->get_amount()))
            return 0;
    return 1;
}




Queue::~Queue()
{
    this->count = 0;
    delete [] this->queue;
    this->queue = nullptr;
}

int Queue::check_queue_date(const purchase &prev, const purchase &curr) const
{
    int hour_p = (prev.get_time()[0] - '0')*10 + prev.get_time()[1] - '0';
    int min_p = (prev.get_time()[3] - '0')*10 + prev.get_time()[4] - '0';
    int sec_p = (prev.get_time()[6] - '0')*10 + prev.get_time()[7] - '0';
    int day_p = (prev.get_date()[0] - '0')*10 + prev.get_date()[1] - '0';
    int month_p = (prev.get_date()[3] - '0')*10 + prev.get_date()[4] - '0';
    int year_p = (prev.get_date()[6] - '0')*1000 + (prev.get_date()[7] - '0')*100 + (prev.get_date()[8] - '0')*10 + (prev.get_date()[9] - '0');

    int hour_c = (curr.get_time()[0] - '0')*10 + curr.get_time()[1] - '0';
    int min_c = (curr.get_time()[3] - '0')*10 + curr.get_time()[4] - '0';
    int sec_c = (curr.get_time()[6] - '0')*10 + curr.get_time()[7] - '0';
    int day_c = (curr.get_date()[0] - '0')*10 + curr.get_date()[1] - '0';
    int month_c = (curr.get_date()[3] - '0')*10 + curr.get_date()[4] - '0';
    int year_c = (curr.get_date()[6] - '0')*1000 + (curr.get_date()[7] - '0')*100 + (curr.get_date()[8] - '0')*10 + (curr.get_date()[9] - '0');

    if (year_c < year_p)
        return 0;
    if (year_c == year_p && month_c < month_p)
        return 0;
    if (year_c == year_p && month_c == month_p && day_c < day_p)
        return 0;
    if (year_c == year_p && month_c == month_p && day_c == day_p && hour_c < hour_p)
        return 0;
    if (year_c == year_p && month_c == month_p && day_c == day_p && hour_c == hour_p && min_c < min_p)
        return 0;
    if (year_c == year_p && month_c == month_p && day_c == day_p && hour_c == hour_p && min_c == min_p && sec_c <= sec_p)
        return 0;

    return 1;

}

