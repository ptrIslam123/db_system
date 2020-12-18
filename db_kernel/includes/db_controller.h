#ifndef _DB_CONTROLLER_H_
#define _DB_CONTROLLER_H_

#include <map>
#include "db_kernel.h"
#include "../../tools/includes/singleton.h"

class db_controller;
using db_controller_t         = singleton_classic<db_controller>;
using heder_t                 = word_t&;

class db_controller
{
public:
    using statict_key_t       = word_t;
    using fname_t             = std::string;
    using file_name_t         = fname_t;
    using db_t                = std::unique_ptr<db_kernel>;
    using table_name_t        = std::string;
    using table_name_ptr      = table_name_t*;
    using table_t             = db_kernel;
    using table_ptr           = table_t*; 
    using tables_t            = std::map<table_name_t, db_t>;
    using tables_ptr          = tables_t*;
    using table_iter_t        = typename tables_t::iterator;
    using table_revers_iter_t = typename tables_t::reverse_iterator;
    
    db_controller();
    ~db_controller();

    /* API DB_CONTROLLER */
    void        add_table(table_name_t&& , fname_t&& , size_t );
    void        set_table(table_name_t&& );
    void        delete_table(table_name_t&& );
    void        print_tables();
    void        print_table(word_t&& );
    
    table_ptr   get_table(table_name_t&& );
    table_ptr   get_table(const table_name_t& );
    tables_ptr  get_tables_ptr();

    /* API DB_KERNEL */
    void        write_table_to_table(word_t&& );
    void        write_table_to_file(word_t&& );
    void        reserve();
    void        reserve(size_t );
    void        init_table(table_name_t&& , file_name_t&& , size_t);
    void        clear_table(table_name_t&& );

    token_ptr   get(size_t );
    void        add(token_t&& );
    void        insert(size_t , token_t&& );
    void        remove(size_t );
    
    void        update(size_t , token_t&& );
    void        update_dt(size_t , date_t_&& );
    void        update_ti(size_t, time_t_&& );
    void        update_ds(size_t, descript_t_&& );
    void        update_dt_ti(size_t, date_t_&& , time_t_&& );
    void        update_dt_ds(size_t, date_t_&& , descript_t_&& );
    void        update_ti_ds(size_t , time_t_&& , descript_t_&& );
    void        update_dt_ti_ds(size_t, date_t_&& , time_t_&& , descript_t_&&);
    

    void        add_sort_record(statict_key_t&& , index_t );
    statist_ptr get_sortRecords();
    void        clear_sortRecords();
    void        for_each_sortRec(sort_method_t );

    heder_t     get_heder_table();

    size_t      size_table();
    bool        is_open_table() const;


    /*  TRIGERS API */

    void        bef_attach_triger_add(const trigger_ptr );
    void        bef_attach_triger_remove(const trigger_ptr );
    void        bef_attach_triger_insert(const trigger_ptr );
    

    void        aft_attach_triger_add(const trigger_ptr );
    void        aft_attach_triger_remove(const trigger_ptr );
    void        aft_attach_triger_insert(const trigger_ptr );

    void        bef_detach_trigger(const trigger_ptr );
    void        aft_detach_trigger(const trigger_ptr );

private:
    void        is_exist_table(table_iter_t );
    void        log_error(word_t&& , word_t&& );

private:
  tables_t      tables_;
  table_ptr     cur_table_;
  
};



#endif // !_DB_CONTROLLER_H_
