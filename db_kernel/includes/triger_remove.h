#ifndef _TRIGER_REMOVE_H_
#define _TRIGER_REMOVE_H_ 

#include "triger.h"

class triger_remove : public triger
{
public:
            triger_remove();
    virtual ~triger_remove();

    virtual void exec() override;

private:

};

#endif // !_TRIGER_REMOVE_H_