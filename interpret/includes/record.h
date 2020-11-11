#ifndef _RECORD_H_
#define _RECORD_H_

#include <memory>
#include "../../db_kernel/includes/token.h"

struct record;

using record_t              = std::unique_ptr<record>;
using record_ptr            = record*;
using index_t               = size_t;
using controller_transact_t = void (*)(record_ptr );

struct record
{
public:
    record(index_t , token_t&& , controller_transact_t );
    ~record();

    index_t                 get_index() const;
    token_t                 get_value();
    controller_transact_t   get_controller() const;

private:
    index_t                 index_;
    token_t                 value_;
    controller_transact_t   controller_;
};

#endif // !_RECORD_H_
