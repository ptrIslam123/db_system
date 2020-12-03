#include "includes/option_parse.h"
#include "includes/sys_error.h"

option_parse::option_parse():
    size_(0),
    pos_(0)
{
    buffer_.reserve(_B_BUF_SIZE_OPTION_);
}

option_parse::~option_parse()
{}

void option_parse::parse(data_ptr data, lexeme_v_ptr value)
{
    value_  = value;
    size_   = value->size();
    pos_    = 0;

    while (true)
    {
        if (get(0) == '|')
        {
            next(1);
            if (is_end())
            {
                set_option(data, &buffer_);
                buffer_.clear();
                break;
            }
            else
            {
                set_option(data, &buffer_);
                buffer_.clear();
                continue;
            }
           
        }
        else if (pos_ > size_)
        {
            throw sys_error(error_type::UNDEFINE_PARAM_TYPE,
                            "method: option_parse::parse | error option (undefine token) => '|'");
        }
        buffer_ += get(0);
        next(1);
    }
}

void option_parse::set_option(data_ptr data, word_ptr buf)
{
    if (*buf == ADD_OP)
    {
        data->set_opt_type(_ADD_EV_);
    }
    else if (*buf == INSERT_OP)
    {
        data->set_opt_type(_INSERT_EV_);
    }
    else if (*buf == REMOVE_OP)
    {
        data->set_opt_type(_REMOVE_EV_);
    }
    else 
    {
        throw sys_error(error_type::UNDEFINE_PARAM_TYPE,
                        "method: option_parse::set_option | undefine option");
    }
}

char option_parse::get(size_t pos)
{
    const auto position = pos_ + pos;
    if (position >= size_)
    {
        return '\0';
    }
    return (*value_)[position];
}

void option_parse::next(size_t offset)
{
    pos_ += offset;
}

bool option_parse::is_end() const
{
    return (pos_ >= size_);
}