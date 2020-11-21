#include "includes/triggers.h"

triggers::triggers()
{}

triggers::~triggers()
{}

void triggers::add(trigger_name_t&& tname,trigger_uptr&& t)
{
    triggers_[std::move(tname)] = std::move(t);
}

void triggers::remove(trigger_name_t&& tname)
{
    auto trigger_ptr = triggers_.find(std::move(tname));
    if (trigger_ptr == triggers_.cend())
    {
        throw "method: triggers::remove | undefine triggers";
    }
    triggers_.erase(trigger_ptr);
}

trigger_ptr triggers::get_trigger_ptr(const trigger_name_ptr tname_ptr)
{
    trigger_ptr trigger_ = nullptr;
    // trigger_ = buffer.get_trigger();
    if (trigger_ == nullptr)
    {
        trigger_ = ((triggers_.find((*tname_ptr)))->second).get();
    }
    return trigger_;
}