#include "includes/args_data.h"
#include "../db_kernel/includes/tokenize_grammar.h"

args_data::args_data():
    date_(nullptr),
    time_(nullptr),
    f_date_(false),
    f_time_(false),
    f_descript_(false),
     type_(_NULL_TYPE)
{}

void args_data::set_null_type()
{
    type_ = _NULL_TYPE;
}

void args_data::set_args_type(args_type_t type)
{
    type_ += type;
}

void args_data::set_date_ptr(const date_ptr date)
{
    if (f_date_)
    {
        throw "multi difinition param date";
    }
    date_ = date;
    f_date_ = true;
}

void args_data::set_time_ptr(const time_ptr time)
{
    if (f_time_)
    {
        throw "multi difinition param time";
    }
    time_ = time;
    f_time_ = true;
}

void args_data::set_descript_ptr(const descript_ptr descript)
{
    if (f_descript_)
    {
        throw "multi difinition param description";
    }
    descript_ =  descript;
}

void args_data::set_table_name_ptr(const table_name_ptr table_name)
{
    table_name_ = table_name;
}

date_ptr args_data::get_date_ptr() const
{
    return date_;
}

time_ptr args_data::get_time_ptr() const
{
    return time_;
}

descript_ptr args_data::get_descript_ptr() 
{
    return descript_;
}

args_type_t args_data::get_args_type() 
{
    return type_;
}

table_name_ptr args_data::get_table_name_ptr() const
{
    return table_name_;
}