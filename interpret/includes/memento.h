#ifndef _MEMENTO_H_
#define _MEMENTO_H_

#include <vector>
#include "../../db_kernel/includes/token.h"
#include "../../tools/includes/singleton.h"
#include "record.h"

struct memento;
using memento_t                     = singleton_classic<memento>;

struct memento
{
    using container_t               = std::vector<record_t>;
    using container_iter_t          = typename container_t::iterator;
    using container_revers_iter_t   = typename container_t::reverse_iterator;
public:
    memento();
    ~memento();

    void    reserve(size_t );
    void    set_state(index_t index, token_t&& value, controller_transact_t controller);
    void    rolback();
    void    clear_buf();
    
    size_t size_records() const;
    size_t capacity_records() const;

private:
    container_t records_;
    size_t      size_table_records_;
};

#endif // !_MEMENTO_H_
