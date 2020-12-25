#include "includes/token.h"
#include "../interpret/includes/sys_error.h"
#include <iostream>

token::token()
{}

token::token(date_t_&& date, time_t_&& time, type_t_ type,  descript_t_&& descript):
    date_(std::move(date)),
    time_(std::move(time)),
    type_(type),
    descript_(std::move(descript))
{}

token::~token() 
{}


token_t token::clone()
{
    date_t_     cdate = date_;
    time_t_     ctime = time_;
    type_t_     ctype = type_;
    descript_t_ cdescript = descript_;
    return std::make_unique<token>(
        std::move(cdate),
        std::move(ctime),
        ctype,
        std::move(cdescript)
    );
}

date_t_& token::get_date()
{
    return date_;
}

time_t_& token::get_time()
{
    return time_;
}

type_t_ token::get_type()
{
    return type_;
}

descript_t_& token::get_descript()
{
    return descript_;
}

void token::set_date(const date_t_& date)
{
    date_ = date;
}

void token::set_time(const time_t_& time)
{
    time_ = time;
}
void token::set_type(type_t_ type)
{
    type_ = type;
}

void token::set_descript(const descript_t_& descript)
{
    descript_ = descript;
}


void token::set_date(date_t_&& date)
{
    date_ = std::move(date);
}

void token::set_time(time_t_&& time)
{
    time_ = std::move(time);
}

void token::set_descript(descript_t_&& descript)
{
    descript_ = std::move(descript);
}


void token::print(const size_t index)
{
    printf("\n%-10d\t%-10s\t%-10s\t%-300s\n",
            index, date_.c_str(), time_.c_str(), descript_.c_str());
}

void token::print()
{
    printf("\n\t%-10s\t%-10s\t%-20s\t%-300s\n",
            date_.c_str(), time_.c_str(), type_.c_str(), descript_.c_str());
}

word_t get_type_token()
{
    return std::string("Аудит");
}

token_t make_token()
{
    return std::unique_ptr<token>(nullptr);
}

token_t make_token(token* tok_p)
{
    if (tok_p == nullptr)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
            "method : token:(make_token) | segmentation error | invalid memory");
    }
    return std::unique_ptr<token>(tok_p);
}