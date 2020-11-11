#include "includes/sys_functions.h"
#include "includes/transact_error.h"
#include "includes/memento.h"
#include "../db_kernel/includes/db_controller.h"


/* comparators */

bool comparator_dt(const token_ptr tok, const data_ptr data)
{
    return (tok->get_date() == *(data->get_date_ptr()));
}

bool comparator_ti(const token_ptr tok, const data_ptr data)
{
    return (tok->get_time() == *(data->get_time_ptr()));
}

bool comparator_ds(const token_ptr tok, const data_ptr data)
{
  return (tok->get_descript() == *(data->get_descript_ptr()));
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



/* for_each */


void for_each(cmprt_t cmprt, req_method_t req_method, data_ptr data, token_t&& val)
{
    const size_t size = _get_size_table();
    for (size_t i = 0; i < size; ++i)
    {
        req_method(cmprt, _get_token(i), data, i, std::move(val));
    } 
}

void for_each(cmprt_t cmprt, rm_method_t rm_req_method, data_ptr data, token_t&& val)
{
    const size_t size = _get_size_table();
    for (size_t i = 0; i < size; ++i)
    {
        rm_req_method(cmprt, _get_token(i), data, i);
    } 
}


response_d for_each_select(cmprt_t cmprt, select_t select, data_ptr data)
{
    const size_t size = _get_size_table();
    for (size_t i = 0; i < size; ++i)
    {
        select(cmprt, _get_token(i), data, i);
    } 
    return _get_response();
}



/* request functions */

void create_table(table_name_t&& tname, file_name_t&& fname, size_t size_table)
{
    /////
}

void drop_table(table_name_t&& tname)
{
    /////
}

void get_req(cmprt_t comparator,
             token_ptr tok,
             data_ptr data, 
             size_t pos)
{
    if (comparator(tok, data))
    {
        response_data_t::instance().add(pos);
    }
}


void insert_req(cmprt_t comparator,
                token_ptr tok, 
                data_ptr data, 
                size_t pos, 
                token_t&& val)
{
    if (comparator(tok, data))
    {
        _insert_token(pos, std::move(val));
    }
}

void update_req(cmprt_t comparator,
                token_ptr tok,
                data_ptr data,
                size_t pos,
                token_t&& val)
{
    if(comparator(tok, data))
    {
        _update_token(pos, std::move(val));
    }
}

void remove_req(cmprt_t comparator,
                token_ptr tok,
                data_ptr data,
                size_t pos)
{
    if (comparator(tok, data))
    {
        _remove_token(pos);
    }
}



/* API transaction  */

void create_table_atomic(table_name_t&& tname, file_name_t&& fname, size_t size_table)
{
   /*
    db_controller_t::instance().clear_table(
        std::move(tname),std::move(fname), size_table
    );
    */
}

void drop_table_atomic(table_name_t&& tname)
{
    ///////
}

void insert_req_atomic(cmprt_t comparator,
                token_ptr tok, 
                data_ptr data, 
                size_t pos, 
                token_t&& val)
{
    if (comparator(tok, data))
    {
        _save_state_record(pos, tok, _rolback_insert_r);
        _insert_token(pos, std::move(val));  
    }
}

void update_req_atomic(cmprt_t comparator,
                token_ptr tok,
                data_ptr data,
                size_t pos,
                token_t&& val)
{
    if(comparator(tok, data))
    {
        _save_state_record(pos, tok, _rolback_update_r);
        _update_token(pos, std::move(val));   
    }
}

void remove_req_atomic(cmprt_t comparator,
                token_ptr tok,
                data_ptr data,
                size_t pos)
{
    if (comparator(tok, data))
    {
         
        _save_state_record(pos, tok, _rolback_remove_r);
        _remove_token(pos);   
    }
}


void rolback_records()
{
    memento_t::instance().rolback();
}



/* rolback_request functions */

static
void _rolback_insert_r(record_ptr record)
{
    auto indx = record->get_index();
    _remove_token(indx);
}

static
void _rolback_update_r(record_ptr record)
{
    auto indx = record->get_index();
    _update_token(indx, record->get_value());
}

static
void _rolback_remove_r(record_ptr record)
{
    auto indx = record->get_index();
    _insert_token(indx, record->get_value());
}






/* supporting functional */

static
size_t const _get_size_table()
{
    return db_controller_t::instance().size_table();
}

static
token_ptr const _get_token(size_t pos)
{
    return db_controller_t::instance().get(pos);
}

static
response_d const _get_response()
{
    return response_data_t::instance().get_response();
}

static
void _insert_token(size_t pos, token_t&& val)
{
    db_controller_t::instance().insert(pos, std::move(val));
}

static
void _update_token(size_t pos, token_t&& val)
{
    db_controller_t::instance().update(pos, std::move(val));
}

static
void _remove_token(size_t pos)
{
    db_controller_t::instance().remove(pos);
}

static
void _save_state_record(index_t indx, token_ptr tok, controller_transact_t controll)
{
    memento_t::instance().set_state(indx, tok->clone(), controll);
}

