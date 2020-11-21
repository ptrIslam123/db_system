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
    virtual ~event();

    virtual void attach(const triger_ptr );
    virtual void detach(const triger_ptr );
    virtual void notify();

private:
    trigers_t   poll_triger_;
};

#endif // !_EVENT_H_