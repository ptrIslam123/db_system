#include "includes/command.h"

command::command(base_parse_api_ptr base_p_api):
    base_p_api_(base_p_api)
{}

command::~command()
{}


lexeme_ptr command::get_lexeme(size_t pos) const
{
    return base_p_api_->get_lexeme(pos);
}
void command::next_lexeme(size_t offset)
{
    base_p_api_->next_lexeme(offset);
}

bool command::is_end() const
{
    return base_p_api_->is_end();
}