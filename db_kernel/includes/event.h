#ifndef _EVENT_H_
#define _EVENT_H_
#define _SIZE_TRIGERS_ 30

#include "../../interpret/includes/trigger_node.h"
#include <vector>

class event;
using trigger_t = trigger_node;
using trigger_ptr = trigger_node*;

class event
{
    using trigers_t = std::vector<trigger_ptr>; 
public:
    event();
    ~event();

    void attach(const trigger_ptr );
    void detach(const trigger_ptr );
    void notify();

    size_t get_size();
    size_t capacity();


private:
    trigers_t   poll_triger_;
};

#endif // !_EVENT_H_
