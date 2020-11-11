#include "includes/record.h"

record::record(index_t index, token_t&& value, controller_transact_t controller):
    index_(index),
    value_(std::move(value)),
    controller_(controller)
{
    
}

record::~record()
{

}

index_t record::get_index() const
{
    return index_;
}

token_t record::get_value()
{
    return std::move(value_);
}

controller_transact_t record::get_controller() const
{   
    return controller_;
}