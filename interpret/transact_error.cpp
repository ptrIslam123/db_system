#include "includes/transact_error.h"
#include "includes/memento.h"

transact_error::transact_error()
{}

transact_error::~transact_error()
{}

void transact_error::rolback_records()
{
    memento_t::instance().rolback();
}