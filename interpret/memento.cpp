#include "includes/memento.h"


memento::memento():
    size_table_records_(0)  // config_traits.size_records
{}

memento::~memento()
{}

void memento::reserve(size_t size_table_records)
{
    size_table_records_ = size_table_records;
    records_.reserve(size_table_records_);
}

void memento::set_state(index_t index, token_t&& value, controller_transact_t controller)
{
    records_.push_back(
        std::make_unique<record>(
            index, std::move(value), controller
        )
    );
}

void memento::rolback()
{
    record_ptr r_ptr                    = nullptr; 
    container_revers_iter_t rend_iter_  = records_.rend();
    controller_transact_t controller;

    for (auto record = records_.rbegin(); record != rend_iter_; ++record)
    {
        r_ptr = (*record).get();
        controller = r_ptr->get_controller();
        controller(r_ptr);
    }
}

void memento::clear_buf()
{
    records_.clear();
}

size_t memento::size_records() const
{
    return records_.size();
}

size_t memento::capacity_records() const
{
    return records_.capacity();
}