#ifndef _EVENT_H_
#define _EVENT_H_
#define _SIZE_TRIGERS_ 30

#include "triger.h"
#include <vector>

class event
{
    using trigers_t = std::vector<triger_ptr>; 
public:
    event();
    ~event();

    void attach(const triger_ptr );
    void detach(const triger_ptr );
    void notify();

    size_t get_size();
    size_t capacity();


private:
    trigers_t   poll_triger_;
};

#endif // !_EVENT_H_