#ifndef _TRIGER_H_
#define _TRIGER_H_

class triger;
using triger_ptr = triger*;

class triger
{
public:
    virtual void exec() = 0;
};

#endif // _TRIGER_H_
