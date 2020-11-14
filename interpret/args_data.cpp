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
    is_f_true(f_date_, "date");
    date_ = date;
    f_date_ = true;
}

void args_data::set_time_ptr(const time_ptr time)
{
    is_f_true(f_time_, "time");
    time_ = time;
    f_time_ = true;
}

void args_data::set_descript_ptr(const descript_ptr descript)
{
    is_f_true(f_descript_, "ds");
    descript_ =  descript;
    f_descript_ = true;
}

void args_data::set_table_name_ptr(const table_name_ptr table_name)
{
    is_f_true(f_table_name_, "tn");
    table_name_ = table_name;
    f_table_name_ = true;
}

void args_data::set_file_name_ptr(const file_name_ptr file_name)
{
    is_f_true(f_file_name_, "fn");
    file_name_ = file_name;
    f_file_name_ = true;
}

void args_data::set_size_ptr(const size_ptr size)
{
    is_f_true(f_size_, "sz");
    size_ = size;
    f_size_ = true;
}

void args_data::set_pos_ptr(const pos_ptr pos)
{
    is_f_true(f_pos_, "ps");
    pos_ = pos;
    f_pos_ = true;
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

file_name_ptr args_data::get_file_name_ptr() const
{
    return file_name_;
}

size_ptr args_data::get_size_ptr() const
{
    return size_;
}

pos_ptr args_data::get_pos_ptr() const
{
    return pos_;
}


void args_data::is_f_true(const bool& flage, std::string&& p) 
{
    if (flage)
    {
        throw "multi difinition param: " + p;
    }
}   