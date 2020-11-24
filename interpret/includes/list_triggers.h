#ifndef _LIST_TRIGGERS_H_
#define _LIST_TRIGGERS_H_

#include "../../tools/includes/singleton.h"
//#include "../../tools/includes/buffer.h"
#include "trigger_node.h"
#include "trigger_opeators.h"

#define _LIST_TRIGGERS_T_
//#define _ARRAY_TRIGGERS_T_
using trigger_node_t = trigger_node_uptr;

#ifdef _LIST_TRIGGERS_T_
#include <list>
using list_trigger_container_t = std::list<trigger_node_t>;
#endif // _LIST_TRIGGERS_T_

#ifdef _ARRAY_TRIGGERS_T_
#include <vector>
using list_trigger_container_t = std::vector<trigger_node_t>;
#endif // _ARRAY_TRIGGERS_T_


class list_triggers;
using list_triggers_t = singleton_classic<list_triggers>;

class list_triggers
{
public:
    list_triggers();
    ~list_triggers();

    void                print_triggers();
    void                add(trigger_name_t&& , trigger_block_t&& );
    void                remove(trigger_name_t&& );
    trigger_node_ptr    get_trigger_ptr(const trigger_name_ptr );
    trigger_block_ptr   get_trigger_block_ptr(const trigger_name_ptr );

private:
    list_trigger_container_t triggers_;
    //buffer kech_;
};

#endif // !_LIST_TRIGGERS_H_
