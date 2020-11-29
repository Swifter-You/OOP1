#include "bonus_card.h"
#include <ctype.h>

int check_bonus_card(const string& value)
{
    if(value.size() != 12)
        return 0;
    for(int i = 0; i < 12;i++)
        if(!isdigit(value[i]))
            return 0;
    return 1;
}

bonus_card::bonus_card()
{
    this->bonus_card_number = "000000000000";
    this->telephone_num = "+7";
}

bonus_card::bonus_card(const string &time, const string &date, int amount, const string &bonus_card_number, const string &telephone):purchase(time, date,amount)
{
    if(check_bonus_card(bonus_card_number))
        this->bonus_card_number = bonus_card_number;
    else
        this->bonus_card_number = "000000000000";
    this->telephone_num = telephone;

}

bonus_card::bonus_card(const bonus_card &other):purchase(other)
{
    this->bonus_card_number = other.bonus_card_number;
    this->telephone_num = other.telephone_num;
}

const string &bonus_card::get_bonus_card_number() const
{
    return this->bonus_card_number;
}

void bonus_card::set_bonus_card_number(const string &value)
{
    if(check_bonus_card(value))
        this->bonus_card_number = value;
    else
        this->bonus_card_number = "000000000000";
}

string bonus_card::get_data(const string &type) const
{
    if(type == "time")
        return this->get_time();
    if(type == "date")
        return this->get_date();
    if(type == "card")
        return this->get_bonus_card_number();
    if(type == "tele")
        return this->telephone_num;
    return "  ";
}


