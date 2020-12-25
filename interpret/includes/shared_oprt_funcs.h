#ifndef _SHARED_OPRT_FUNCS_H_
#define _SHARED_OPRT_FUNCS_H_

#include "args_data_operator.h" 
#include "args_data.h"

void  __get_operator(args_oprt_buf_t&& );
void  __print_table__operator(args_oprt_buf_t&& );
void  __print_operator(args_oprt_buf_t&& );
void  __count_operator(args_oprt_buf_t&& );
void  __clear_operator(args_oprt_buf_t&& );
void  __log_operator(args_oprt_buf_t&& );
void  __rolback_operator(args_oprt_buf_t&& );
void  __list_tables_operator(args_oprt_buf_t&& );
void  __list_triggers_operator(args_oprt_buf_t&& );
void  __list_error_log_operator(args_oprt_buf_t&& );
void  __bef_attach_operator(args_oprt_buf_t&& );
void  __bef_detach_operator(args_oprt_buf_t&& );
void  __aft_attach_operator(args_oprt_buf_t&& );
void  __aft_detach_operator(args_oprt_buf_t&& );
void  __write_table_operator(args_oprt_buf_t&& );
void  __size_table_operator(args_oprt_buf_t&& );
void  __sort_records_operator(args_oprt_buf_t&& );
void  __statistics_operator(args_oprt_buf_t&& );
void  __backup_operators(args_oprt_buf_t&& );
void  __list_inodes_operators(args_oprt_buf_t&& );
void  __roll_back_operators(args_oprt_buf_t&& );
void  __echo_operators(args_oprt_buf_t&& );

void     init_data(data_ptr , args_oprt_buf_t&& );
data_ptr get_data_ptr();


#endif // !_SHARED_OPRT_FUNCS_H_
