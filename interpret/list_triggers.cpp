#include "includes/list_triggers.h"
#include "includes/sys_error.h"

list_triggers::list_triggers()
{}

list_triggers::~list_triggers()
{}


void list_triggers::print_triggers()
{
    auto beg = triggers_.cbegin();
    auto end = triggers_.cend();
    trigger_node_ptr node = nullptr;

    for (auto it = beg; it != end; it++)
    {
        node = (*it).get();
        if (node == nullptr)
        {
            throw sys_error(error_type::OUT_OF_RANGE,
                "An attempt to access non-existint or invalid data");
        }
        std::cout << "\t[TRIGGER_NAME] :=> " << *(node->get_name_ptr()) << std::endl;
    }
}

void list_triggers::add(trigger_name_t&& tname, trigger_block_t&& tblock)
{
    triggers_.push_back(
        std::make_unique<trigger_node>(
            std::move(tname), std::move(tblock)
        )
    );
}

void list_triggers::remove(trigger_name_t&& tname)
{
    trigger_node_ptr node_p = nullptr;
    
    for (auto it = triggers_.begin(); it != triggers_.end(); ++it)
    {
        node_p = (*it).get();
        if (node_p->is_eq(&tname))
        {
            triggers_.erase(it);
        }
    }
}

trigger_node_ptr list_triggers::get_trigger_ptr(const trigger_name_ptr tname_p)
{
    auto beg                = triggers_.begin();
    auto end                = triggers_.end();
    trigger_node_ptr node_p = nullptr;
    
    for (auto it = beg; it != end; ++it)
    {
        node_p = (*it).get();
        if (node_p->is_eq(tname_p))
        {
            return node_p;
        }
    }
    throw sys_error(error_type::TRIGGER_NOT_FOUND,
        "method : list_triggers::get_trigger_block_ptr : undefine triggert = > " + *(tname_p));
}

trigger_block_ptr list_triggers::get_trigger_block_ptr(const trigger_name_ptr tname_p)
{
    auto beg               = triggers_.begin();
    auto end               = triggers_.end();
    trigger_node_ptr node_p = nullptr;
    
    for (auto it = beg; it != end; ++it)
    {
        node_p = (*it).get();
        if (node_p->is_eq(tname_p))
        {
            return node_p->get_block_ptr();
        }
    }
    throw sys_error(error_type::TRIGGER_NOT_FOUND,
        "method : list_triggers::get_trigger_block_ptr : undefine triggert = > " + *(tname_p));
}
