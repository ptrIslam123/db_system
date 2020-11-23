#include "includes/command.h"
#include <iostream>

command::command(base_parse_api_ptr base_p_api):
    base_p_api_(base_p_api)
{}

command::~command()
{}

bool command::is_it_command() const
{
    return false;
}

lexeme_ptr command::get_lexeme(size_t pos) const
{
    return base_p_api_->get_lexeme(pos);
}

lexeme_uptr command::get_lexeme_uptr(size_t pos)
{
    return base_p_api_->get_lexeme_uptr(pos);
}

void command::next_lexeme(size_t offset)
{
    base_p_api_->next_lexeme(offset);
}

bool command::is_end() const
{
    return base_p_api_->is_end();
}