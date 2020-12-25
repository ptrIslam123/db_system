#ifndef _ARGS_DATA_H_
#define _ARGS_DATA_H_
#define _DEF_T_
#include "../../db_kernel/includes/token.h"

constexpr short _NULL_TYPE              = 0;
constexpr short _DATE_                  = 1;
constexpr short _TIME_                  = 10;
constexpr short _TYPE_                  = 15;
constexpr short _TABLE_NAME_            = 20;
constexpr short _FILE_NAME_             = 25;
constexpr short _SIZE_TABLE_            = 30;
constexpr short _POS_                   = 31;
constexpr short _NAME_                  = 48;

constexpr short _OPTION_                = 40;
constexpr short _BEFORE_OP_             = 66;
constexpr short _AFTER_OP_              = 68;
constexpr short _BEFORE_AFTER_OP_       = ( _BEFORE_OP_ + _AFTER_OP_ );

constexpr short _INSERT_EV_             = 70;
constexpr short _ADD_EV_                = 72;
constexpr short _REMOVE_EV_             = 74;
constexpr short _INS_ADD_EV_            = ( _INSERT_EV_ + _ADD_EV_ );
constexpr short _INS_REM_EV_            = ( _INSERT_EV_ + _REMOVE_EV_ );
constexpr short _ADD_REM_EV_            = ( _ADD_EV_ + _REMOVE_EV_ );
constexpr short _INS_ADD_REM_EV_        = ( _INSERT_EV_ + _ADD_EV_ + _REMOVE_EV_ );

constexpr short _TABLE_FILE_NAME_SIZE_  = ( _TABLE_NAME_ + _FILE_NAME_ + _SIZE_TABLE_ );      
constexpr short _DESCRIPT_              = 100;
constexpr short _DATE_TIME_             = ( _DATE_ + _TIME_ );
constexpr short _TIME_DESCRIPT_         = ( _TIME_ + _DESCRIPT_ );
constexpr short _DATE_DESCRIPT          = ( _DATE_ + _DESCRIPT_ );
constexpr short _DATE_TIME_DESCRIPT_    = ( _DATE_ + _TIME_ + _DESCRIPT_ );
constexpr short _POS_DATE_TIME_DESCRIPT_= ( _POS_ + _DATE_TIME_DESCRIPT_ ); 
constexpr short _TG_NAME_OP_            = ( _NAME_ + _OPTION_ );
constexpr short _NAME_DESCRIPT_         = ( _NAME_ + _DESCRIPT_ );
constexpr short _TG_TNAME_NAME_OP_      = ( _TABLE_NAME_ + _NAME_ + _OPTION_ );
constexpr short _TG_TNAME_NAME_         = ( _TABLE_NAME_ + _NAME_ );
constexpr short _TABLE_FIE_NAME_        = ( _TABLE_NAME_ + _FILE_NAME_ );
constexpr short _TABLE_TABLE_NAME_      = ( _TABLE_NAME_ + _TABLE_NAME_ );
constexpr short _FILE_NAME_DESCRIPT_    = ( _FILE_NAME_  + _DESCRIPT_ ); 

struct args_data;
using data_ptr      = args_data*;
using token_ptr     = token*;
using date_ptr      = date_t_*;
using time_ptr      = time_t_*;
using type_ptr      = word_t*;
using descript_ptr  = descript_t_*;
using table_name_ptr= word_t*;
using file_name_ptr = word_t*;
using size_ptr      = word_t*;
using pos_ptr       = word_t*;
using option_ptr    = word_t*;
using name_ptr      = word_t*;
using opt_type_t    = short;
using args_type_t   = short;

struct args_data
{
public:
    args_data();

    void            set_args_type(args_type_t );
    void            set_opt_type(opt_type_t );
    void            set_date_ptr(const date_ptr );
    void            set_time_ptr(const time_ptr );
    void            set_type(const type_ptr );
    void            set_descript_ptr(const descript_ptr );
    void            set_null_type();
    void            set_table_name_ptr(const table_name_ptr );
    void            set_file_name_ptr(const file_name_ptr );
    void            set_size_ptr(const size_ptr );
    void            set_pos_ptr(const pos_ptr );
    void            set_option_ptr(const option_ptr );
    void            set_name_ptr(const name_ptr );

    date_ptr        get_date_ptr() const;
    time_ptr        get_time_ptr() const;
    descript_ptr    get_descript_ptr();
    type_ptr        get_type_ptr() const;
    args_type_t     get_args_type();
    opt_type_t      get_opt_type();
    table_name_ptr  get_table_name_ptr() const;
    file_name_ptr   get_file_name_ptr() const;
    size_ptr        get_size_ptr() const;
    pos_ptr         get_pos_ptr() const;
    option_ptr      get_option_ptr() const;
    name_ptr        get_name_ptr() const;

private:   
    void            is_f_true(const bool& , std::string&& );

private:

    date_ptr        date_;
    time_ptr        time_;
    descript_ptr    descript_;
    type_ptr        ttype_;
    table_name_ptr  table_name_;
    file_name_ptr   file_name_;
    size_ptr        size_;
    pos_ptr         pos_;
    option_ptr      option_;
    name_ptr        name_;
    args_type_t     type_;
    opt_type_t      opt_;

    bool            f_date_;
    bool            f_time_;
    bool            f_descript_;
    bool            f_ttype_;
    bool            f_table_name_;
    bool            f_file_name_;
    bool            f_size_;
    bool            f_pos_;
    bool            f_option_;
    bool            f_name_;
};

#endif // !_ARGS_DATA_H_
