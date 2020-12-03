#include "includes/trigger_node.h"

trigger_node::trigger_node(name_t&& name, block_t&& block):
    name_(std::move(name)),
    block_(std::move(block))
{}

trigger_node::~trigger_node()
{}



void trigger_node::exec()
{
    base_parse_api base_(&block_);
    parser parser_(&base_);
    
    while (!base_.is_end())
    {
        parser_.run();
    }
}

name_ptr trigger_node::get_name_ptr()
{
    return &name_;
}

trigger_node::block_ptr trigger_node::get_block_ptr()
{
    return &block_;
}

bool trigger_node::is_eq(const name_ptr name) const
{
    return (name_) == (*name);
}