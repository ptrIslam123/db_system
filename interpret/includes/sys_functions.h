#ifndef _SYS_FUNCTIONS_H_
#define _SYS_FUNCTIONS_H_
#define _LOGER_SIZE_BUF_ 255
#define _TRANSACT_TEST_LOG_
#ifndef _TRANSACT_TEST_LOG_
#include <iostream>
#endif // !_TRANSACT_TEST_LOG_

#include <memory>
#include "record.h"
#include "args_data.h"
#include "response_data.h"
#include "../../tools/includes/loger.h"
#include "../../db_kernel/includes/db_controller.h"
#include "../../vcs/includes/vcs_tab.h"


//using statist_key_t     = statist_key_t;

using token_ptr         = token*;   // token*
using token_t           = std::unique_ptr<token>;
using response_d        = response_data::container_t;

using table_name_t      = std::string;
using file_name_t       = std::string;
using table_ptr         = db_controller::table_ptr;

using inode_ptr         = vcs::inode_ptr;

/* memento API */
using rolback_f_t       = controller_transact_t;
using indext_t          = size_t;
using cmprt_t           = bool (*)(const token_ptr ,const data_ptr ); 
using rm_method_t       = void (*)(index_t );
using ins_method_t      = void (*)(index_t , token_t&& );
using upd_method_t      = void (*)(index_t, data_ptr );
using select_t          = void (*)(cmprt_t, token_ptr , data_ptr , index_t );
using req_method_t      = void (*)(token_ptr );
using statict_key_maker_t   = statist_key_t (*)(token_ptr );




/* comparators */
bool comparator_dt(const token_ptr ,const data_ptr );
bool comparator_ti(const token_ptr, const data_ptr );
bool comparator_ty(const token_ptr , const data_ptr );
bool comparator_ds(const token_ptr, const data_ptr );
bool comparator_dt_ti(const token_ptr, const data_ptr );
bool comparator_dt_ty(const token_ptr , const data_ptr );
bool comparator_ti_ty(const token_ptr , const data_ptr );
bool comparator_ty_ds(const token_ptr , const data_ptr );
bool comparator_dt_ds(const token_ptr, const data_ptr );
bool comparator_ti_ds(const token_ptr, const data_ptr );
bool comparator_dt_ti_ds(const token_ptr, const data_ptr );
bool comparator_dt_ti_ty_ds(const token_ptr, const data_ptr );


statist_key_t make_sort_key_dt(token_ptr );
statist_key_t make_sort_key_ti(token_ptr );
statist_key_t make_sort_key_ds(token_ptr );
statist_key_t make_sort_key_dt_ti(token_ptr );
statist_key_t make_sort_key_dt_ds(token_ptr );
statist_key_t make_sort_key_ti_ds(token_ptr );
statist_key_t make_sort_key_dt_ti_ds(token_ptr );


/* for_each */

void for_each(cmprt_t , select_t , data_ptr );
void for_each(ins_method_t , token_t&& );
void for_each(upd_method_t , data_ptr );
void for_each(rm_method_t );
void for_each(req_method_t );
void for_each(statict_key_maker_t );

/* request functions */

void create_table_req(table_name_t&& , file_name_t&& , size_t );
void drop_table_req(table_name_t&& );
void set_table_req(table_name_t&& );

void get_req(cmprt_t , token_ptr ,  data_ptr , index_t );
void add_req(token_t&& );
void insert_req(index_t, token_t&& );
void update_dt_req(index_t , data_ptr );
void update_ti_req(index_t , data_ptr );
void update_ds_req(index_t , data_ptr );
void update_dt_ti_req(index_t , data_ptr );
void update_dt_ds_req(index_t, data_ptr );
void update_ti_ds_req(index_t , data_ptr );
void update_dt_ti_ds_req(index_t , data_ptr );
void remove_req(index_t );
void print_table_req(data_ptr );
void print_tables_req();
void print_triggers_req();
void print_error_log_req();
void clear_req();
void write_table_to_file_req(data_ptr );
void write_table_to_table_req(data_ptr );
void size_table_req(data_ptr );
void backup_req(data_ptr );
void list_inodes_req();
void list_inodes_req(data_ptr );
void roll_back_req(index_t );

/* SORT RECORDS API */

void            add_sortRecord_req(statist_key_t&& , index_t );
void            clear_sortRecords_req();
void            statistics_req(data_ptr );
void            print_count_sortRec_req();
void            print_indexs_sortRec_req();




/* TRIGGER API */

void bef_attach_req(data_ptr );
void bef_detach_req(data_ptr );

void aft_attach_req(data_ptr );
void aft_detach_req(data_ptr );




/* API transaction  */

void create_table_req_atomic(table_name_t&& , file_name_t&& , size_t );
void drop_table_req_atomic(table_name_t&& );
void set_table_req_atomic(table_name_t&& );

void add_req_atomic(token_t&& );
void insert_req_atomic(index_t, token_t&& );
void update_dt_req_atomic(index_t , data_ptr );
void update_ti_req_atomic(index_t , data_ptr );
void update_ds_req_atomic(index_t , data_ptr );
void update_dt_ti_req_atomic(index_t , data_ptr );
void update_dt_ds_req_atomic(index_t, data_ptr );
void update_ti_ds_req_atomic(index_t , data_ptr );
void update_dt_ti_ds_req_atomic(index_t , data_ptr );
void remove_req_atomic(index_t );



void rolback_records();
void clear_buf_memento();


/* rolback request functions */

void _rolback_add_r(record_ptr );
void _rolback_insert_r(record_ptr );
void _rolback_update_r(record_ptr );
void _rolback_remove_r(record_ptr );
void _rolback_create_table(record_ptr );
void _rolback_drop_table(record_ptr );
void _rolback_set_table(record_ptr );


/* supporting functional */
token_t       create_token(data_ptr );
size_t        const _get_size_table();
size_t        const _get_size_pesronse_buf();
size_t        const _get_index_response_buf(size_t );
table_ptr     _get_table_ptr(table_name_t&& );
statist_ptr   _get_sortrecords();
void          _add_index_response_buf(index_t );
token_ptr     const _get_token(size_t );
response_d    const _get_response();
void         _add_token(token_t&& );
void         _insert_token(size_t , token_t&& );
void         _update_token(size_t , token_t&& );
void         _remove_token(size_t );
void         _save_state_record(index_t , token_t&& , controller_transact_t);

void         _log(word_t&& );
void         _print_token(token_ptr );
void         _print_heder(const word_ptr );
void         _print_table(const table_name_ptr );
void         _print_tables();
void         _print_triggers();
void         _print_log_file();

void         _print_inode_inf(vcs::inode_ptr );

void         _print_count_sortRec(word_t&& , statist_value_ptr );
void         _print_index_sortRec(word_t&& , statist_value_ptr );

#ifndef _TRANSACT_TEST_LOG_
void         _save_state_log(const token_ptr , const std::string& );
void         _save_state_log(const table_name_ptr ,  const std::string& );
#endif // !_TRANSACT_TEST_LOG_


#endif // !_SYS_FUNCTIONS_H_
