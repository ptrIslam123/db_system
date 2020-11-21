#include "includes/event.h"

event::event():
    poll_triger_(_SIZE_TRIGERS_)
{}

event::~event()
{}

void event::attach(const triger_ptr t)
{
    poll_triger_.push_back(t); 
}

void event::detach(const triger_ptr t)
{
    auto beg = poll_triger_.begin();
    auto end = poll_triger_.end();

    for (auto it = beg; it != end; ++it)
    {
        if ( (*it) == t )
        {
            poll_triger_.erase(it);
        }
    }
}

void event::notify()
{
    for (auto &i : poll_triger_)
    {
        i->exec();
    }
}