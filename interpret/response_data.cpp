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

response_data::container_t response_data::get_response()
{
    return std::move(poll_indx_);
}