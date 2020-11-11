#include "includes/lexeme.h"

lexeme::lexeme(lexeme_v&& value, lexeme_t&& type):
    value_(std::move(value)),
    type_(std::move(type))
{}

lexeme::~lexeme() {}

const lexeme_v& lexeme::get_value()
{
    return value_;
}

const lexeme_t& lexeme::get_type()
{
    return type_;
}

const lexeme_t_ptr lexeme::get_ptr_type() 
{
    return &type_;
}

const lexeme_v_ptr lexeme::get_ptr_value() 
{
    return &value_;
}
