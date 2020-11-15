#ifndef _SYS_FUNCTIONS_H_
#define _SYS_FUNCTIONS_H_

#include <memory>
#include "record.h"
#include "args_data.h"
#include "response_data.h"

using token_ptr     = token*;   // token*
using token_t       = std::unique_ptr<token>;
using response_d    = response_data::container_t;

using table_name_t  = std::string;
using file_name_t   = std::string;

/* memento API */
using rolback_f_t   = controller_transact_t;
using indext_t      = size_t;
using cmprt_t       = bool (*)(const token_ptr ,const data_ptr ); 
using rm_method_t   = void (*)(index_t );
using req_method_t  = void (*)(index_t , token_t&& );
using select_t      = void (*)(cmprt_t, token_ptr , data_ptr , index_t );
//using comparator_t  = bool (*)(cmprt_t, token_ptr , data_ptr ); 

/* rm_method_t for remove_request */
/* req_method_t for update, insert request */
/* select_t for get request */




/* comparators */
bool comparator_dt(const token_ptr ,const data_ptr );
bool comparator_ti(const token_ptr, const data_ptr );
bool comparator_ds(const token_ptr, const data_ptr );
bool comparator_dt_ti(const token_ptr, const data_ptr );
bool comparator_dt_ds(const token_ptr, const data_ptr );
bool comparator_ti_ds(const token_ptr, const data_ptr );
bool comparator_dt_ti_ds(const token_ptr, const data_ptr );



/* for_each */

void for_each(cmprt_t , select_t , data_ptr );
void for_each(req_method_t , token_t&& );
void for_each(rm_method_t );


/* request functions */

void create_table_req(table_name_t&& , file_name_t&& , size_t );
void drop_table_req(table_name_t&& );
void set_table_req(table_name_t&& );

void get_req(cmprt_t , token_ptr ,  data_ptr , index_t );
void insert_req(index_t, token_t&& );
void update_dt_req(index_t , date_t_&& );
void update_ti_req(index_t , time_t_&& );
void update_ds_req(index_t , descript_t_&& );
void update_dt_ti_req(index_t , date_t_&& , time_t_&& );
void update_dt_ds_req(index_t, date_t_&& , descript_t_&& );
void update_ti_ds_req(index_t , time_t_&& , descript_t_&& );
void update_dt_ti_ds_req(index_t , date_t_&& , time_t_&& , descript_t_&& );
void remove_req(index_t );



/* API transaction  */

void create_table_req_atomic(table_name_t&& , file_name_t&& , size_t );
void drop_table_req_atomic(table_name_t&& );
void set_table_req_atomic(table_name_t&& );

void insert_req_atomic(index_t, token_t&& );
void update_dt_req_atomic(index_t , date_t_&& );
void update_ti_req_atomic(index_t , time_t_&& );
void update_ds_req_atomic(index_t , descript_t_&& );
void update_dt_ti_req_atomic(index_t , date_t_&& , time_t_&& );
void update_dt_ds_req_atomic(index_t, date_t_&& , descript_t_&& );
void update_ti_ds_req_atomic(index_t , time_t_&& , descript_t_&& );
void update_dt_ti_ds_req_atomic(index_t , date_t_&& , time_t_&& , descript_t_&& );
void remove_req_atomic_atomic(index_t );

void rolback_records();

/* rolback request functions */
static void _rolback_insert_r(record_ptr );
static void _rolback_update_r(record_ptr );
static void _rolback_remove_r(record_ptr );
static void _rolback_create_table(record_ptr );
static void _rolback_drop_table(record_ptr );
static void _rolback_set_table(record_ptr );


/* supporting functional */
token_t                   create_token(data_ptr );
static size_t       const _get_size_table();
static size_t       const _get_size_pesronse_buf();
static size_t       const _get_index_response_buf(size_t );
static void               _add_index_response_buf(index_t );
static token_ptr    const _get_token(size_t );
static response_d   const _get_response();
static void         _insert_token(size_t , token_t&& );
static void         _update_token(size_t , token_t&& );
static void         _remove_token(size_t );
static void         _save_state_record(index_t , token_t&& , controller_transact_t);



#endif // !_SYS_FUNCTIONS_H_
