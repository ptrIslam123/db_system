#ifndef _DB_KERNEL_H_
#define _DB_KERNEL_H_
//#define _ENABLE_DB_CONTROLLER_OPRTIONS_
#define _BAD_ALLOC_DB_KERNEL_T_

#include <iostream> //for size_t 
#include <memory>
#include <string>

#ifndef _ENABLE_DB_CONTROLLER_OPRTIONS_
#include <vector>
#include <list>
#include <map>

#include "token.h"
#include "tokenize_grammar.h"
#include "file_stream.h"
#include "methods.h"
#include "event.h"
#endif // !_ENABLE_DB_CONTROLLER_OPRTIONS_

class db_kernel;
#ifndef _ENABLE_DB_CONTROLLER_OPRTIONS_
using token_t           = std::unique_ptr<token>;
using token_ptr         = token*;
using file_stream_t     = file_stream;
using file_stream_ptr   = file_stream_t*;
using tok_gramm_t       = std::unique_ptr<tokenize_grammar>;
using tok_gramm_ptr     = tokenize_grammar*;

using container_t       = std::vector<token_t>;
using container_iter_t  = typename container_t::iterator;
using db_kernel_t       = std::unique_ptr<db_kernel>; 
using db_kernel_ptr     = db_kernel*;

using index_t           = container_t::size_type;
using count_t           = index_t;
using statist_value_t   = std::list<index_t>;
using statist_value_ptr = statist_value_t*;
using statist_key_t     = word_t; 
using statist_t         = std::map<word_t, std::unique_ptr<statist_value_t>>;
using statist_ptr       = statist_t*;
using sort_method_t     = void (*)(word_t&& , statist_value_ptr);
#endif // !_ENABLE_DB_CONTROLLER_OPRTIONS_

class db_kernel
{
public:
    db_kernel(tok_gramm_t&& , size_t beg_cont_size = 0);
    ~db_kernel();

    void        reserve();
    void        reserve(size_t );
    void        create_table();
    void        drop_table();
    void        print_table();
    void        write_table_to_file(word_t&& );

    token_ptr   get(size_t );
    void        add(token_t&& );
    void        push_token(token_t&& );
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

    /* SORT RECORDS API */
    void        add_sort_record(statist_key_t&& , index_t );
    statist_ptr get_sortRecords();
    void        clear_sortRecords();
    void        for_each_sortRec(sort_method_t );
    

    word_t&     get_heder();
    word_ptr    get_heder_ptr();
    word_ptr    get_file_name_ptr();

    size_t      size_table();
    bool        is_open_file() const;
    tok_gramm_t get_tok_gramm();
    void        open_file();

    
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
    void        print_token(const token_ptr , const size_t );
    token_ptr   get_token(size_t );
    
private:

    tok_gramm_t      tok_gramm_;
    size_t           beg_cont_size_;
    container_t      container_;
    container_iter_t iter_, beg_iter_;
    word_t           heder_;
    statist_t        sortRecords_;

    /*  TRIGERS API */

    event           befEventAdd_;
    event           befEventRemove_;
    event           befEventInsert_;

    event           aftEventAdd_;
    event           aftEventRemove_;
    event           aftEventInsert_;
};


db_kernel_t make_db_kernel(std::string&& , size_t );

#ifndef _BAD_ALLOC_DB_KERNEL_T_
db_kernel_ptr alloc_db_kernel(std::string&& , size_t );
#endif // !_BAD_ALLOC_DB_KERNEL_T_

#endif // !_DB_KERNEL_H_
