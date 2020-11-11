#include "includes/transaction.h"
#include "includes/transact_error.h"

transaction::transaction()
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

void transaction::close_transact_contecste() const
{

}

lexeme_ptr transaction::get(size_t ) const
{
    return nullptr;
}

void transaction::next(size_t )
{

}

bool transaction::is_it_commat() const
{
    return true;
}

bool transaction::is_end_transact_block() const
{
    return true;
}