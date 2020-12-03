#include "includes/sys_error.h"
#include "includes/memento.h"
#include "../tools/includes/loger.h"

#define ERRFILE_NOT_FOUND       word_t("NULL_ERR")
#define ERRTABLE_NOT_FOUND      word_t("NULL_ERR")
#define ERRBAD_ALLOC            word_t("NULL_ERR")
#define ERROUT_OF_RANGE         word_t("NULL_ERR")
#define ERRUNDEFINE_OPERATION   word_t("NULL_ERR")
#define UNDEFINE_ERROR_TYPE     word_t("undefine type error");

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
        case error_type::FILE_NOT_FOUND     : return ERRFILE_NOT_FOUND;
        case error_type::TABLE_NOT_FOUND    : return ERRTABLE_NOT_FOUND;
        case error_type::OUT_OF_RANGE       : return ERROUT_OF_RANGE;
        case error_type::BAD_ALLOC          : return ERRBAD_ALLOC;
        case error_type::UNDEFINE_OPERATION : return ERRUNDEFINE_OPERATION;
        default :
            return UNDEFINE_ERROR_TYPE; 

    }
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