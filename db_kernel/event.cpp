#include "includes/event.h"


event::event()
{
    poll_triger_.reserve(_SIZE_TRIGERS_);
}

event::~event()
{}

void event::attach(const trigger_ptr t)
{
    poll_triger_.push_back(t); 
}

void event::detach(const trigger_ptr t)
{
    auto beg = poll_triger_.begin();
    auto end = poll_triger_.end();

    for (auto it = beg; it != end; ++it)
    {
        if ( (*it) == t )
        {
            poll_triger_.erase(it);
            break;
        }
    }
}

void event::notify()
{
    auto size = poll_triger_.size();
    
    for (decltype(size) i = 0; i < size; ++i)
    {
        poll_triger_[i]->exec();
    }
}

size_t event::get_size()
{
    return poll_triger_.size();
}

size_t event::capacity()
{
    return poll_triger_.capacity();
}