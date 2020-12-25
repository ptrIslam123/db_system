#include "includes/sys_functions.h"
#include "includes/sys_error.h"
#include "includes/memento.h"
#include "includes/list_triggers.h"
#include "../tools/includes/files.h"
#include "../tools/includes/utils.h"

using size_table_t          = decltype(_get_size_table);
using index_response_buf_t  = decltype(_get_index_response_buf);
using size_response_buf_t   = decltype(_get_size_pesronse_buf);

/* comparators */

bool comparator_dt(const token_ptr tok, const data_ptr data)
{
    return (tok->get_date() == *(data->get_date_ptr()));
}

bool comparator_ti(const token_ptr tok, const data_ptr data)
{
    return (tok->get_time() == *(data->get_time_ptr()));
}

bool comparator_ty(const token_ptr tok, const data_ptr data)
{
    return (tok->get_type() == *(data->get_type_ptr()));
} 

bool comparator_ds(const token_ptr tok, const data_ptr data)
{
    // for Widnows new line = \r\n; 
    auto descript1  =   tok->get_descript();
    auto descript2  =   *(data->get_descript_ptr());
    auto res        =   (descript1 == descript2 + '\r') || 
                        (descript1 == descript2);
  return res;
}

bool comparator_dt_ty(const token_ptr tok, const data_ptr data)
{
    return (comparator_dt(tok, data) && comparator_ty(tok, data));
}

bool comparator_ti_ty(const token_ptr tok, const data_ptr data)
{
    return (comparator_ti(tok, data) && comparator_ty(tok, data));
}

bool comparator_ty_ds(const token_ptr tok, const data_ptr data)
{
    return (comparator_ty(tok, data) && comparator_ds(tok, data));
}


bool comparator_dt_ti(const token_ptr tok, const data_ptr data)
{
    return (comparator_dt(tok, data) && comparator_ti(tok, data));
}

bool comparator_ti_ds(const token_ptr tok, const data_ptr data)
{
    return (comparator_ti(tok, data) && comparator_ds(tok, data));
}

bool comparator_dt_ds(const token_ptr tok, const data_ptr data)
{
    return (comparator_dt(tok, data) && comparator_ds(tok, data));
}

bool comparator_dt_ti_ds(const token_ptr tok, const data_ptr data)
{
    return (comparator_dt(tok, data) 
         && comparator_dt(tok, data)
         && comparator_ds(tok, data)
    );
}


bool comparator_dt_ti_ty_ds(const token_ptr tok, const data_ptr data)
{
    return (comparator_dt(tok, data) &&
            comparator_ti(tok, data) &&
            comparator_ty(tok, data) &&
            comparator_ds(tok, data));
}



statist_key_t make_sort_key_dt(token_ptr tok)
{
    return  tok->get_date();
}


statist_key_t make_sort_key_ti(token_ptr tok)
{
    return  tok->get_time();
}

statist_key_t make_sort_key_ds(token_ptr tok)
{
    return  tok->get_descript();
}

statist_key_t make_sort_key_dt_ti(token_ptr tok)
{
    return  tok->get_date() + " " + 
            tok->get_time();
}

statist_key_t make_sort_key_dt_ds(token_ptr tok)
{
    return  tok->get_date() + " " + 
            tok->get_descript();
}

statist_key_t make_sort_key_ti_ds(token_ptr tok)
{
    return  tok->get_time() + " " +
            tok->get_descript();
}

statist_key_t make_sort_key_dt_ti_ds(token_ptr tok)
{
    return  tok->get_date() + " " + 
            tok->get_time() + " " + 
            tok->get_descript();
}



/* for_each */


void for_each(cmprt_t comparator , select_t select , data_ptr data)
{
    auto size = _get_size_table();

    for (decltype(size) i = 0; i < size; ++i)
    {
        select(comparator, _get_token(i), data, i);
    }
}

void for_each(ins_method_t req , token_t&& val)
{
    auto size = _get_size_pesronse_buf();

    for (decltype(size) i = 0; i < size; ++i)
    {
        req(_get_index_response_buf(i), val->clone());
    }
}

void for_each(upd_method_t update, data_ptr data)
{
    auto size = _get_size_pesronse_buf();
    
    for (decltype(size) i = 0; i < size; ++i)
    {
        update(_get_index_response_buf(i), data);
    }
}

void for_each(rm_method_t rm)
{
    auto size = _get_size_pesronse_buf();
    
    for (decltype(size) i = 0; i < size; ++i)
    {
        rm(_get_index_response_buf(i));
    }
}


void for_each(req_method_t req)
{
    auto size = _get_size_pesronse_buf();
    
    for (decltype(size) i = 0; i < size; ++i)
    {
        req( _get_token( _get_index_response_buf(i) ) );
    }
}


void for_each(statict_key_maker_t s_maker)
{
    auto size = _get_size_table();

    for (decltype(size) i = 0; i < size; ++i)
    {
        add_sortRecord_req(s_maker(_get_token(i)) ,i);
    }
}


/* request functions */

void create_table_req(table_name_t&& tname, file_name_t&& fname, size_t size_table)
{
   db_controller_t::instance().init_table(
       std::move(tname),
       std::move(fname),
       size_table
   );
}

void drop_table_req(table_name_t&& tname)
{
    db_controller_t::instance().clear_table(
        std::move(tname)
    );
}


void set_table_req(table_name_t&& tname)
{
    db_controller_t::instance().set_table(std::move(tname));
}


void get_req(cmprt_t comparator,
             token_ptr tok,
             data_ptr data, 
             index_t index)
{
    if (comparator(tok, data))
    {
        _add_index_response_buf(index);
    }
}

void add_req(token_t&& val)
{
    _add_token(std::move(val));
}

void insert_req(index_t index, token_t&& val)
{
    _insert_token(index, std::move(val));
}



void update_dt_req(index_t index, data_ptr data)
{
    auto date = *(data->get_date_ptr());
    db_controller_t::instance().update_dt(index, std::move(date));
}

void update_ti_req(index_t index, data_ptr data)
{
    auto time = *(data->get_time_ptr());
    db_controller_t::instance().update_ti(index, std::move(time));
}

void update_ds_req(index_t index, data_ptr data)
{
    auto descript = *(data->get_descript_ptr());
    db_controller_t::instance().update_ds(index, std::move(descript));
}

void update_dt_ti_req(index_t index, data_ptr data)
{
    auto date = *(data->get_date_ptr());
    auto time = *(data->get_time_ptr());
    db_controller_t::instance().update_dt_ti(index, 
                                             std::move(date), 
                                             std::move(time));
}

void update_dt_ds_req(index_t index, data_ptr data)
{
    auto date = *(data->get_date_ptr());
    auto descript = *(data->get_descript_ptr());
    db_controller_t::instance().update_dt_ds(index, 
                                          std::move(date),
                                          std::move(descript));
}

void update_ti_ds_req(index_t index, data_ptr data)
{
    auto time = *(data->get_time_ptr());
    auto descript = *(data->get_descript_ptr());
    db_controller_t::instance().update_ti_ds(index, 
                                          std::move(time),
                                          std::move(descript));
}

void update_dt_ti_ds_req(index_t index, data_ptr data)
{
    auto date = *(data->get_date_ptr());
    auto time = *(data->get_time_ptr());
    auto descript = *(data->get_descript_ptr());
    db_controller_t::instance().update_dt_ti_ds(index, 
                                          std::move(date),
                                          std::move(time),
                                          std::move(descript));
}


void remove_req(index_t index)
{
    _remove_token(index);
}


void print_table_req(data_ptr data)
{
   _print_table(data->get_table_name_ptr());
}


void print_tables_req()
{
    _print_tables();
}

void print_triggers_req()
{
    _print_triggers();
}

void print_error_log_req()
{
    _print_log_file();
}

void clear_req()
{
    response_data_t::instance().clear_buf();
}


void write_table_to_file_req(data_ptr data)
{
    auto fname = *(data->get_file_name_ptr());
    db_controller_t::instance().write_table_to_file(
        std::move(fname)
    );
}

void write_table_to_table_req(data_ptr data)
{
    auto tname = *(data->get_table_name_ptr());
    db_controller_t::instance().write_table_to_table(
        std::move(tname)
    );
}


/* SORT RECORDS API */

void add_sortRecord_req(statist_key_t&& key, index_t indx)
{
    db_controller_t::instance().add_sort_record(std::move(key), indx);
}


void clear_sortRecords_req()
{
    db_controller_t::instance().clear_sortRecords();
}

void statistics_req(data_ptr data)
{
    auto ds = *(data->get_descript_ptr());
    if (ds == "count")
    {
        print_count_sortRec_req();
    }
    else if (ds == "index")
    {
        print_indexs_sortRec_req();
    }
    else
    {
        throw sys_error(error_type::UNDEFINE_PARAM_TYPE,
            "method : statistics_req | undefine param => " + ds);
    }
    
}


void print_count_sortRec_req()
{
    db_controller_t::instance().for_each_sortRec(
        _print_count_sortRec
    );
}

void print_indexs_sortRec_req()
{
    db_controller_t::instance().for_each_sortRec(
        _print_index_sortRec
    );
}

/* BACKUP API */

void backup_req(data_ptr data)
{
    auto tname      = *(data->get_table_name_ptr());
    auto msg_inf    = *(data->get_descript_ptr());

    auto table_p    = _get_table_ptr(std::move(tname));

    vcs::backup_table(std::move(msg_inf), table_p);
}


void list_inodes_req()
{
    /* for_each(print_inode_inf) */
}

void list_inodes_req(data_ptr data)
{
    auto msg    = *(data->get_descript_ptr());
    auto in_p   = vcs::find_inode(std::move(msg));

    _print_inode_inf(in_p);
}


void roll_back_req(index_t indx)
{
    auto in_p =  vcs::find_inode(indx);
    vcs::roll_back_db(in_p);
}


/* TRIGGER API */

void bef_attach_req(data_ptr data)
{
    auto name_ptr   = data->get_name_ptr();
    auto option     = data->get_opt_type();
    
    auto t_ptr = list_triggers_t::instance().get_trigger_ptr(name_ptr);

    if (t_ptr == nullptr)
    {
        throw sys_error(error_type::TRIGGER_NOT_FOUND,
            "method : sys_function::bef_attach_req | trigger not found");
    }

    switch (option)
    {
        case _ADD_EV_ :         
        {
            db_controller_t::instance().bef_attach_triger_add(t_ptr);
            break;
        }
        case _REMOVE_EV_ :      
        {
            db_controller_t::instance().bef_attach_triger_remove(t_ptr);
            break;
        }
        case _INSERT_EV_ :      
        {
            db_controller_t::instance().bef_attach_triger_insert(t_ptr);
            break;
        }
        case _ADD_REM_EV_ :     
        {
            db_controller_t::instance().bef_attach_triger_add(t_ptr);
            db_controller_t::instance().bef_attach_triger_remove(t_ptr);
            break;
        }
        case _INS_REM_EV_ :     
        {
            db_controller_t::instance().bef_attach_triger_insert(t_ptr);
            db_controller_t::instance().bef_attach_triger_remove(t_ptr);
            break;
        }
        case _INS_ADD_REM_EV_ : 
        {
            db_controller_t::instance().bef_attach_triger_add(t_ptr);
            db_controller_t::instance().bef_attach_triger_remove(t_ptr);
            db_controller_t::instance().bef_attach_triger_insert(t_ptr);
            break;
        }
        default:
            throw sys_error(error_type::UNDEFINE_PARAM_TYPE,
                "method : sys_function::bef_attach_req");
    }
}

void bef_detach_req(data_ptr data)
{
    auto name_ptr   = data->get_name_ptr();
    auto t_ptr = list_triggers_t::instance().get_trigger_ptr(name_ptr);
    if (t_ptr == nullptr)
    {
        throw sys_error(error_type::TRIGGER_NOT_FOUND,
            "method : sys_function::aft_attach_req | trigger not found");
    }
    db_controller_t::instance().bef_detach_trigger(t_ptr);
}



void aft_attach_req(data_ptr data)
{
    auto name_ptr   = data->get_name_ptr();
    auto option     = data->get_opt_type();
    
    auto t_ptr = list_triggers_t::instance().get_trigger_ptr(name_ptr);
    
    if (t_ptr == nullptr)
    {
        throw sys_error(error_type::TRIGGER_NOT_FOUND,
            "method : sys_function::aft_attach_req | trigger not found");
    }

    switch (option)
    {
        case _ADD_EV_ :         
        {
            db_controller_t::instance().aft_attach_triger_add(t_ptr);
            break;
        }
        case _REMOVE_EV_ :      
        {
            db_controller_t::instance().aft_attach_triger_remove(t_ptr);
            break;
        }
        case _INSERT_EV_ :      
        {
            db_controller_t::instance().aft_attach_triger_insert(t_ptr);
            break;
        }
        case _ADD_REM_EV_ :     
        {
            db_controller_t::instance().aft_attach_triger_add(t_ptr);
            db_controller_t::instance().aft_attach_triger_remove(t_ptr);
            break;
        }
        case _INS_REM_EV_ :     
        {
            db_controller_t::instance().aft_attach_triger_insert(t_ptr);
            db_controller_t::instance().aft_attach_triger_remove(t_ptr);
            break;
        }
        case _INS_ADD_REM_EV_ : 
        {
            db_controller_t::instance().aft_attach_triger_add(t_ptr);
            db_controller_t::instance().aft_attach_triger_remove(t_ptr);
            db_controller_t::instance().aft_attach_triger_insert(t_ptr);
            break;
        }
        default:
            throw sys_error(error_type::UNDEFINE_PARAM_TYPE,
                "method : sys_function::aft_attach_req");
    }
}

void aft_detach_req(data_ptr data)
{
    auto name_ptr   = data->get_name_ptr();
    auto t_ptr = list_triggers_t::instance().get_trigger_ptr(name_ptr);
    if (t_ptr == nullptr)
    {
        throw sys_error(error_type::TRIGGER_NOT_FOUND,
            "method : sys_function::aft_detach_req | trigger not found");
    }
    db_controller_t::instance().bef_detach_trigger(t_ptr);
}


void size_table_req(data_ptr data)
{
    auto arg_type = data->get_args_type();
    
    switch (arg_type)
    {
        case _TABLE_NAME_ : {
            auto tname      = *(data->get_table_name_ptr());
            auto table_ptr  = _get_table_ptr(std::move(tname));
            auto size_table = table_ptr->size_table();
            
            std::cout << size_table << std::endl;
            break;
        }
        case _NULL_TYPE : {
            auto cur_size_t = _get_size_table();
            
            std::cout << cur_size_t << std::endl;
            break;
        }
        default: 
            throw sys_error(error_type::UNDEFINE_PARAM_TYPE,
                "method : sys_function::size_table_req");
    }
}



/* API transaction  */

void create_table_req_atomic(table_name_t&& tname, file_name_t&& fname, size_t size_table)
{
#ifndef _TRANSACT_TEST_LOG_
    _save_state_log(&tname, "add_req");
#endif // !_TRANSACT_TEST_LOG_G_
 
   _save_state_record(0,make_token(), _rolback_create_table);
  db_controller_t::instance().init_table(
       std::move(tname),
       std::move(fname),
       size_table
   );
}

void drop_table_req_atomic(table_name_t&& tname)
{
#ifndef _TRANSACT_TEST_LOG_
    _save_state_log(&tname, "add_req");
#endif // !_TRANSACT_TEST_LOG_

    _save_state_record(0, make_token(), _rolback_drop_table);
   db_controller_t::instance().clear_table(
       std::move(tname)
   );
}


void set_table_req_atomic(table_name_t&& tname)
{
#ifndef _TRANSACT_TEST_LOG_
    _save_state_log(&tname, "set_t_req");
#endif // !_TRANSACT_TEST_LOG_

    _save_state_record(0, make_token(), _rolback_set_table);
    db_controller_t::instance().set_table(std::move(tname));
}


void add_req_atomic(token_t&& val)
{
#ifndef _TRANSACT_TEST_LOG_
    _save_state_log(val.get(), "add_req");
#endif // !_TRANSACT_TEST_LOG_

    auto pos = _get_size_table();
    _save_state_record(pos, val->clone(), _rolback_add_r);
    _add_token(std::move(val));
}

void insert_req_atomic(index_t index, token_t&& val)
{
#ifndef _TRANSACT_TEST_LOG_
    _save_state_log(val.get(), "insert_req");
#endif // !_TRANSACT_TEST_LOG_

    _save_state_record(index, val->clone(), _rolback_insert_r);
    _insert_token(index, std::move(val));
}



void update_dt_req_atomic(index_t index, data_ptr data)
{
    auto tok = _get_token(index);

#ifndef _TRANSACT_TEST_LOG_
    _save_state_log(tok, "update_dt_req");
#endif // !_TRANSACT_TEST_LO

    _save_state_record(index, tok->clone(), _rolback_update_r);
    update_dt_req(index, data);
}

void update_ti_req_atomic(index_t index, data_ptr data)
{
    auto tok = _get_token(index);

#ifndef _TRANSACT_TEST_LOG_
    _save_state_log(tok, "update_ti_req");
#endif // !_TRANSACT_TEST_LOG

    _save_state_record(index, tok->clone(), _rolback_update_r);
    update_ti_req(index,data);
}

void update_ds_req_atomic(index_t index, data_ptr data)
{
    auto tok = _get_token(index);

#ifndef _TRANSACT_TEST_LOG_
    _save_state_log(tok, "update_ds_req");
#endif // !_TRANSACT_TEST_LOG

    _save_state_record(index, tok->clone(), _rolback_update_r);
    update_ds_req(index, data);
}

void update_dt_ti_req_atomic(index_t index, data_ptr data)
{
    auto tok = _get_token(index);

#ifndef _TRANSACT_TEST_LOG_
    _save_state_log(tok, "update_dt_ti_req");
#endif // !_TRANSACT_TEST_LOG_

    _save_state_record(index, tok->clone(), _rolback_update_r);
    update_dt_ti_req(index, data); 
}

void update_dt_ds_req_atomic(index_t index, data_ptr data)
{
    auto tok = _get_token(index);

#ifndef _TRANSACT_TEST_LOG_
    _save_state_log(tok, "update_dt_ds_req");
#endif // !_TRANSACT_TEST_LOG_

    _save_state_record(index, tok->clone(), _rolback_update_r);
    update_dt_ds_req(index, data);
}

void update_ti_ds_req_atomic(index_t index, data_ptr data)
{
    auto tok = _get_token(index);

#ifndef _TRANSACT_TEST_LOG_
    _save_state_log(tok, "update_ti_ds_req");
#endif // !_TRANSACT_TEST_LOG_

    _save_state_record(index, tok->clone(), _rolback_update_r);
    update_ti_ds_req(index, data);
}

void update_dt_ti_ds_req_atomic(index_t index,  data_ptr data)
{
    auto tok = _get_token(index);
    _save_state_record(index, tok->clone(), _rolback_update_r);
    update_dt_ti_ds_req(index, data);
}



void remove_req_atomic(index_t index)
{
#ifndef _TRANSACT_TEST_LOG_
    _save_state_log(_get_token(index), "remove_req");
#endif // !_TRANSACT_TEST_LOG_

    _save_state_record(index, make_token(), _rolback_remove_r);
    _remove_token(index);
}


void rolback_records()
{
    memento_t::instance().rolback();
}

void clear_buf_memento()
{
    memento_t::instance().clear_buf();
}

/* rolback_request functions */


void _rolback_add_r(record_ptr record)
{
    auto indx = record->get_index();
    _remove_token(indx);
}



void _rolback_insert_r(record_ptr record)
{
    auto indx = record->get_index();
    _remove_token(indx);
}


void _rolback_update_r(record_ptr record)
{
    auto indx = record->get_index();
    _update_token(indx, record->get_value());
}


void _rolback_remove_r(record_ptr record)
{
    auto indx = record->get_index();
    _insert_token(indx, record->get_value());
}


void _rolback_create_table(record_ptr )
{
    /* nothing */
}

void _rolback_drop_table(record_ptr )
{
     /* nothing */
}

void _rolback_set_table(record_ptr )
{
     /* nothing */
}



/* supporting functional */

token_t create_token(data_ptr data)
{
    auto dt = *(data->get_date_ptr());
    auto ti = *(data->get_time_ptr());
    auto ty =   get_type_token();
    auto ds = *(data->get_descript_ptr());
   
    auto val = make_token(
        std::move(dt), std::move(ti) ,std::move(ty), std::move(ds)
    );
    return val;  // return std::move(val); // -Wall
}


size_t const _get_size_table()
{
    return db_controller_t::instance().size_table();
}


size_t const _get_size_pesronse_buf()
{
    return response_data_t::instance().size();
}

size_t const _get_index_response_buf(size_t pos)
{
    return response_data_t::instance().get_index(pos);
}


table_ptr _get_table_ptr(table_name_t&& tname)
{
    return db_controller_t::instance().get_table(std::move(tname));
}

statist_ptr _get_sortrecords()
{
    return db_controller_t::instance().get_sortRecords();
}

void _add_index_response_buf(index_t index)
{
    response_data_t::instance().add(index);
}




token_ptr const _get_token(size_t pos)
{
    return db_controller_t::instance().get(pos);
}


response_d const _get_response()
{
    return response_data_t::instance().get_response();
}



void _add_token(token_t&& val)
{
    db_controller_t::instance().add(std::move(val));
}


void _insert_token(size_t pos, token_t&& val)
{
    db_controller_t::instance().insert(pos, std::move(val));
}


void _update_token(size_t pos, token_t&& val)
{
    db_controller_t::instance().update(pos, std::move(val));
}


void _remove_token(size_t pos)
{
    db_controller_t::instance().remove(pos);
}



void _save_state_record(index_t indx, token_t&& tok, controller_transact_t controll)
{
    memento_t::instance().set_state(indx, std::move(tok), controll);
}


void _print_token(token_ptr tok)
{
    if (tok == nullptr)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
            "_print_token : Attempt to access invalid or non-existent data");
    }
    tok->print();
}

void _print_heder(const word_ptr heder)
{
    std::cout << (*heder) << std::endl;
}


void _print_table(const table_name_ptr tname_ptr)
{
    auto tname = *tname_ptr;
    const auto table = db_controller_t::instance().get_table(std::move(tname));
    table->print_table();
}



void _print_tables()
{
    db_controller_t::instance().print_tables();
}


void _print_triggers()
{
    list_triggers_t::instance().print_triggers();
}


void _print_log_file()
{
   static files file(_STD_LOGER_FILE_PATH_);
   std::cout << file.read(); 
}


void _print_inode_inf(vcs::inode_ptr in_p)
{
    auto msg    = in_p->get_message().c_str();
    auto indx   = in_p->get_index();
    auto size   = in_p->get_size_record();

    printf("message : %-250s\tindex : %d\tsize : %d\n",
        msg, indx, size);
}


void _print_count_sortRec(word_t&& name_key, statist_value_ptr list_val)
{
    std::cout << "NAME  : " << name_key             << std::endl;
    std::cout << "COUNT : " << list_val->front()    << std::endl;
    std::cout << std::endl;
}

void _print_index_sortRec(word_t&& name_key, statist_value_ptr list_val)
{
    auto beg = list_val->cbegin();
    auto end = list_val->cend();
    auto it = beg;
    it++;
    
    std::cout << "NAME  : " << name_key << std::endl;
    std::cout << "INDEX : ";

    for (it = beg; it != end; ++it)
    {
        std::cout << *it;
    }
    
    std::cout << std::endl;
}


#ifndef _TRANSACT_TEST_LOG_


void _save_state_log(const token_ptr tok, const std::string& msg)
{
    std::cout << msg << " :=> record{" << std::endl;
    _print_token(tok);
    std::cout << "}" << std::endl;
}



void _save_state_log(const table_name_ptr tname_p,  const std::string& msg)
{
    std::cout << msg << " :=> table{" << std::endl;
    std::cout << (*tname_p) << std::endl;
    std::cout << "}" << std::endl;
}

#endif // !_TRANSACT_TEST_LOG_