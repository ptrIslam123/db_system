#include "includes/response_data.h"
#include "includes/sys_error.h"
#include "../tools/includes/utils.h"

response_data::response_data()
{}

response_data::~response_data()
{}

void response_data::reserve(size_t size)
{
    size_ = size;
    poll_indx_.reserve(size_);
}

void response_data::add(size_t indx)
{
    try
    {
        poll_indx_.push_back(indx);   
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
            "method response_data::add | size_records : " + cast_i_str(size()));
    }
}

void response_data::clear_buf()
{
    poll_indx_.clear();
}

response_data::container_t response_data::get_response()
{
    return std::move(poll_indx_);
}

response_data::index_t response_data::get_index(size_t pos) const
{
    index_t indx = 0;
    try
    {
        indx = poll_indx_.at(pos); 
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
            "method response_data::get_index | index = " + cast_i_str(pos));
    }
    return indx;
}

size_t response_data::size() const
{
    return poll_indx_.size();
}

size_t response_data::capacity() const
{
    return poll_indx_.capacity();
}