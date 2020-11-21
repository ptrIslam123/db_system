#ifndef _TRIGER_INSERT_H_
#define _TRIGER_INSERT_H_ 

#include "triger.h"

class triger_insert : public triger
{
public:
            triger_insert();
    virtual ~triger_insert();

    virtual void exec() override;

private:

};

#endif // !_TRIGER_INSERT_H_