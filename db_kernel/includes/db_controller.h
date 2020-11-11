#ifndef _DB_CONTROLLER_H_
#define _DB_CONTROLLER_H_

#include <map>
#include "db_kernel.h"
#include "../../tools/includes/singleton.h"

class db_controller;
using db_controller_t         = singleton_classic<db_controller>;

class db_controller
{
public:
    using fname_t             = std::string;
    using db_t                = std::unique_ptr<db_kernel>;
    using table_name_t        = std::string;
    using table_t             = db_kernel;
    using table_ptr           = table_t*; 
    using tables_t            = std::map<table_name_t, db_t>;
    using table_iter_t        = typename tables_t::iterator;
    using table_revers_iter_t = typename tables_t::reverse_iterator;

    db_controller();
    db_controller(size_t );
    ~db_controller();

    /* API DB_CONTROLLER */
    void        add_table(table_name_t&& , fname_t&& , size_t );
    table_ptr   get_table(table_name_t&& );
    table_ptr   get_table(const table_name_t& );

    /* API DB_KERNEL */
    void        reserve();
    void        reserve(size_t );
    void        init_table();
    void        clear_table();

    token_ptr   get(size_t );
    void        add(token_t&& );
    void        insert(size_t , token_t&& );
    void        remove(size_t );
    void        update(size_t , token_t&& );
    size_t      size_table();
    bool        is_open_table() const;

private:
    void is_exist_table(table_iter_t );

private:
  tables_t  tables_;
  table_ptr cur_table_;
  size_t    size_tables_;
};



#endif // !_DB_CONTROLLER_H_
