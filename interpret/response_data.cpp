#include "includes/response_data.h"

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
    poll_indx_.push_back(indx);
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
    return poll_indx_[pos];
}

size_t response_data::size() const
{
    return poll_indx_.size();
}

size_t response_data::capacity() const
{
    return poll_indx_.capacity();
}