#ifndef _ARGS_DATA_OPERATOR_H_
#define _ARGS_DATA_OPERATOR_H_

#include "lexeme.h"
#include <iostream>
#include <vector>


using oprt_name_t  = lexeme_v;
using args_oprt_type = lexeme*;
using args_oprt_value = lexeme*;
using args_oprt_t = std::pair<args_oprt_type, args_oprt_value>;

using args_oprt_buf_t = std::vector<args_oprt_t>;

using oprt_type = void (*)(args_oprt_buf_t&& );
using oprt_t = std::pair<oprt_type, args_oprt_buf_t&&>;


#endif // !_ARGS_DATA_OPERATOR_H_
