#ifndef _SYS_ERROR_H_
#define _SYS_ERROR_H_

#include <string>

using errmsg_t = std::string;

enum class error_type 
{ 
    FILE_NOT_FOUND,
    TABLE_NOT_FOUND,
    TRIGGER_NOT_FOUND,
    OUT_OF_RANGE,
    BAD_ALLOC,
    UNDEFINE_OPERATION,
    UNDEFINE_FUNCTION,
    UNDEFINE_PARAM_TYPE,
    MULTI_DEFINITION,
    UNDEFINE_TOKEN,
    RUNTIME_ERROR
};

struct sys_error
{
public:
    sys_error(const error_type& , errmsg_t&& );
    ~sys_error();

    void        rolback_records();
    void        write_log();
    void        print_log();
    errmsg_t    what();

private:
    errmsg_t    get_type_err(const error_type& );

private:
    error_type  type_error_;
    errmsg_t    errmsg_;
};

#endif // !_SYS_ERROR_H_
