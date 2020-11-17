#ifndef _SHARED_OPRT_FUNCS_H_
#define _SHARED_OPRT_FUNCS_H_

#include "args_data_operator.h" 
#include "args_data.h"

void  __get_operator(args_oprt_buf_t&& );
void  __print_table__operator(args_oprt_buf_t&& );
void  __print_operator(args_oprt_buf_t&& );
void  __count_operator(args_oprt_buf_t&& );
void  __clear_operator(args_oprt_buf_t&& );

void     init_data(data_ptr , args_oprt_buf_t&& );
data_ptr get_data_ptr();


#endif // !_SHARED_OPRT_FUNCS_H_
