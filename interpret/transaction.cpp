#include "includes/transaction.h"
#include "includes/transact_error.h"

transaction::transaction(base_parse_api_ptr base_p_api):
    command(base_p_api),
    oprt_(base_p_api)
{}

transaction::~transaction()
{}

void transaction::execute()
{
    while (!is_end_transact_block())
    {
        try
        {
            oprt_.execute();
        }
        catch(transact_error& e)
        {
            e.rolback_records();
            close_transact_contecste();
            return;
        } 
    }
}

lexeme_ptr transaction::get(size_t pos) const
{
    return get_lexeme(pos);
}

void transaction::next(size_t offset)
{
    next_lexeme(offset);
}

void transaction::close_transact_contecste() const
{

}


bool transaction::is_it_commat() const
{
    return false;
}

bool transaction::is_end_transact_block() const
{
    return false;
}