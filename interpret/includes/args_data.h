#ifndef _ARGS_DATA_H_
#define _ARGS_DATA_H_

#include "../../db_kernel/includes/token.h"


#define _DATE_ 1
#define _TIME_ 10
#define _DESCRIPT_ 100
#define _DATE_TIME_ ( _DATE_ + _TIME_ )
#define _TIME_DESCRIPT_ ( _TIME_ + _DESCRIPT_ )
#define _DATE_DESCRIPT  ( _DATE_ + _DESCRIPT_ )
#define _DATE_TIME_DESCRIPT_ ( _DATE_ + _TIME_ + _DESCRIPT_ )
#define _ERROR_TYPE 0

struct args_data;
using data_ptr      = args_data*;
using token_ptr     = token*;
using date_ptr      = date_t_*;
using time_ptr      = time_t_*;
using descript_ptr  = descript_t_*;
using args_type_t   = short;

struct args_data
{
public:
    args_data();

    void         set_args_type(args_type_t );
    void         set_date_ptr(const date_ptr );
    void         set_time_ptr(const time_ptr );
    void         set_descript_ptr(const descript_ptr );

    date_ptr     get_date_ptr() const;
    time_ptr     get_time_ptr() const;
    descript_ptr get_descript_ptr();
    args_type_t  get_args_type();

    
private:
    date_ptr     date_;
    time_ptr     time_;
    descript_ptr descript_;
    args_type_t  type_;
    bool         f_date_;
    bool         f_time_;
    bool         f_descript_;
};

#endif // !_ARGS_DATA_H_
