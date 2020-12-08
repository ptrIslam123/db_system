#include "includes/transaction.h"
#include "includes/sys_error.h"
#include "includes/sys_functions.h"

transaction::transaction(base_parse_api_ptr base_p_api):
    command(base_p_api),
    oprt_(base_p_api)
{}

transaction::~transaction()
{}

void transaction::execute()
{
    next(1);        // '{'
    while (!is_end_transact_block())
    {
        try
        {
            oprt_.execute();
        }
        catch(sys_error& e)
        {
            e.write_log();
            e.rolback_records();
            close_transact_contecste();
            break;
        } 
    }
    next(1);        // '}'
    clear_buf_memento();    // !clear_buf_memento after exec transaction code 
}



bool transaction::is_it_command() const
{
    return get(0)->get_type() == LEXEME_TYPE::L_SHAPE_BRACKET;
}


void transaction::close_transact_contecste() 
{
    while (!is_end_transact_block())
    {
        next(1);   
    }
}


bool transaction::is_end_transact_block() const
{
    return get(0)->get_type() == LEXEME_TYPE::R_SHAPE_BRACKET;
}


lexeme_ptr transaction::get(size_t pos) const
{
    return get_lexeme(pos);
}

void transaction::next(size_t offset)
{
    next_lexeme(offset);
}