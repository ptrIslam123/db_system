#ifndef _TRIGER_DROP_TABLE_H_
#define _TRIGER_DROP_TABLE_H_

#include "triger.h"

class triger_drop_table : public triger
{
public:
            triger_drop_table();
    virtual ~triger_drop_table();

    virtual void exec() override;


private:

};

#endif // !_TRIGER_DROP_TABLE_H_
