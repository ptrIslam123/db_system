#ifndef _TRIGGERS_H_
#define _TRIGGERS_H_
#define _TRIGGER_SIZE_  50
#include <map>
#include <memory>
#include <string>

#include "trigger_opeators.h"

class triggers
{
    using trigger_name_t    = std::string;
    using trigger_name_ptr  = trigger_name_t*;
    using triggers_t        = std::map<trigger_name_t, trigger_uptr>;
public:
    triggers();
    ~triggers();

    void            add(trigger_name_t&& ,trigger_uptr&& );
    void            remove(trigger_name_t&& );
    trigger_ptr     get_trigger_ptr(const trigger_name_ptr );

private:
    triggers_t      triggers_;
    //trigger_buffer buffer_;
};

#endif // !_TRIGGERS_H_
