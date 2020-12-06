#include "includes/sys_error.h"
#include "includes/memento.h"
#include "../tools/includes/loger.h"

#include <iostream>

#define ERRFILE_NOT_FOUND       word_t("sys_error: Can`t to find or access the file")
#define ERRTABLE_NOT_FOUND      word_t("sys_error: Can`t to find or access the table")
#define ERRBAD_ALLOC            word_t("sys_error: Memory exhausted, impossible to allocate")
#define ERROUT_OF_RANGE         word_t("sys_error: Out of bounds of a table or record, trying to access an unavailable record")
#define ERRUNDEFINE_OPERATION   word_t("sys_error: Attempt to perform an unknown or invalid operation")
#define UNDEFINE_ERROR_TYPE     word_t("sys_error: Undefine type error")
#define ERRTRIGGER_NOT_FOUND    word_t("sys_error: Trigger not found")
#define ERRUNDEFINE_FUNCTION    word_t("sys_error: Undefine function")
#define ERRUNDEFINE_PARAM_TYPE  word_t("sys_error: Undefine funcion param type")
#define ERRMULTI_DEFINITION     word_t("sys_error: Multiple chatacter definition")
#define ERRUNDEFINE_TOKEN       word_t("sys_error: Undefine token")
#define ERRRUNTIME_ERROR        word_t("sys_erorr: Runtime error")

sys_error::sys_error(const error_type& type_error, errmsg_t&& errmsg):
    type_error_(type_error),
    errmsg_(std::move(errmsg))
{}

sys_error::~sys_error()
{}

void sys_error::rolback_records()
{
    memento_t::instance().rolback();
}

word_t sys_error::get_type_err(const error_type& terr)
{   
    switch (terr)
    {
        case error_type::FILE_NOT_FOUND         : return ERRFILE_NOT_FOUND;
        case error_type::TABLE_NOT_FOUND        : return ERRTABLE_NOT_FOUND;
        case error_type::TRIGGER_NOT_FOUND      : return ERRTRIGGER_NOT_FOUND;
        case error_type::OUT_OF_RANGE           : return ERROUT_OF_RANGE;
        case error_type::BAD_ALLOC              : return ERRBAD_ALLOC;
        case error_type::UNDEFINE_OPERATION     : return ERRUNDEFINE_OPERATION;
        case error_type::UNDEFINE_FUNCTION      : return ERRUNDEFINE_FUNCTION;
        case error_type::UNDEFINE_PARAM_TYPE    : return ERRUNDEFINE_PARAM_TYPE;
        case error_type::MULTI_DEFINITION       : return ERRMULTI_DEFINITION;
        case error_type::UNDEFINE_TOKEN         : return ERRUNDEFINE_TOKEN;
        case error_type::RUNTIME_ERROR          : return ERRRUNTIME_ERROR;
        default :
            return UNDEFINE_ERROR_TYPE; 

    }
}

errmsg_t sys_error::what()
{
    return get_type_err(type_error_) +  " : "  + errmsg_;
}

void sys_error::write_log()
{
    log::loger& log = get_loger();
    log.log(get_type_err(type_error_), std::move(errmsg_));
}

void sys_error::print_log()
{
    auto t_err = get_type_err(type_error_);
    printf("%s\t\t%s\n", 
            t_err.c_str(), errmsg_.c_str()); 
}




