#ifndef _TRIGGER_NODE_H_
#define _TRIGGER_NODE_H_

#include <memory>
#include "trigger_opeators.h"
#include "base_parse_api.h"
#include "parser.h"

struct trigger_node;
using trigger_node_ptr  = trigger_node*;
using trigger_node_uptr = std::unique_ptr<trigger_node>;

struct trigger_node
{
    using name_t        = trigger_name_t;
    using name_ptr      = name_t*;
    using block_t       = trigger_block_t;
    using block_ptr     = block_t*;
public:
    //trigger_node(name_t&& , block_t&& );
    trigger_node(name_t&& , block_t&& );
    ~trigger_node();

    void            exec();
    name_ptr        get_name_ptr();
    block_ptr       get_block_ptr();
    bool            is_eq(const name_ptr ) const;

private:
    name_t          name_;
    block_t         block_;
};

#endif // !_TRIGGER_NODE_H_
