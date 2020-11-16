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


void for_each(cmprt_t comparator , select_t select , data_ptr data)
{
    const auto size = _get_size_table();
    for (auto i = 0; i < size; ++i)
    {
        select(comparator, _get_token(i), data, i);
    }
}

void for_each(ins_method_t req , token_t&& val)
{
    const auto size = _get_size_pesronse_buf();
    for (auto i = 0; i < size; ++i)
    {
        req(_get_index_response_buf(i), val->clone());
    }
}

void for_each(upd_method_t update, data_ptr data)
{
    const auto size = _get_size_pesronse_buf();
    for (auto i = 0; i < size; ++i)
    {
        update(_get_index_response_buf(i), data);
    }
}

void for_each(rm_method_t rm)
{
    const auto size = _get_size_pesronse_buf();
    for (auto i = 0; i < size; ++i)
    {
        rm(_get_index_response_buf(i));
    }
}


void for_each(req_method_t req)
{
    const auto size = _get_size_pesronse_buf();
    for (auto i = 0; i < size; ++i)
    {
        req( _get_token( _get_index_response_buf(i) ) );
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


void print_table_req()
{
    const auto size = _get_size_table();
    for (auto i = 0; i < size; ++i)
    {
        _print_token(_get_token(i));
    }
}


void clear_req()
{
    response_data_t::instance().clear_buf();
}


/* API transaction  */

void create_table_req_atomic(table_name_t&& tname, file_name_t&& fname, size_t size_table)
{
   _save_state_record(0,make_token(), _rolback_create_table);
  db_controller_t::instance().init_table(
       std::move(tname),
       std::move(fname),
       size_table
   );
}

void drop_table_req_atomic(table_name_t&& tname)
{
    _save_state_record(0, make_token(), _rolback_drop_table);
   db_controller_t::instance().clear_table(
       std::move(tname)
   );
}


void set_table_req_atomic(table_name_t&& tname)
{
    _save_state_record(0, make_token(), _rolback_set_table);
    db_controller_t::instance().set_table(std::move(tname));
}


void add_req_atomic(token_t&& val)
{
    auto pos = _get_size_table();
    _save_state_record(pos, val->clone(), _rolback_add_r);
    _add_token(std::move(val));
}

void insert_req_atomic(index_t index, token_t&& val)
{
    _save_state_record(index, val->clone(), _rolback_insert_r);
    _insert_token(index, std::move(val));
}



void update_dt_req_atomic(index_t index, data_ptr data)
{
    auto tok = _get_token(index);
    _save_state_record(index, tok->clone(), _rolback_update_r);
    update_dt_req(index, data);
}

void update_ti_req_atomic(index_t index, data_ptr data)
{
    auto tok = _get_token(index);
    _save_state_record(index, tok->clone(), _rolback_update_r);
    update_ti_req(index,data);
}

void update_ds_req_atomic(index_t index, data_ptr data)
{
    auto tok = _get_token(index);
    _save_state_record(index, tok->clone(), _rolback_update_r);
    update_ds_req(index, data);
}

void update_dt_ti_req_atomic(index_t index, data_ptr data)
{
    auto tok = _get_token(index);
    _save_state_record(index, tok->clone(), _rolback_update_r);
    update_dt_ti_req(index, data); 
}

void update_dt_ds_req_atomic(index_t index, data_ptr data)
{
    auto tok = _get_token(index);
    _save_state_record(index, tok->clone(), _rolback_update_r);
    update_dt_ds_req(index, data);
}

void update_ti_ds_req_atomic(index_t index, data_ptr data)
{
    auto tok = _get_token(index);
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
    _save_state_record(index, make_token(), _rolback_remove_r);
    _remove_token(index);
}


void rolback_records()
{
    memento_t::instance().rolback();
}



/* rolback_request functions */

static
void _rolback_add_r(record_ptr record)
{
    auto indx = record->get_index();
    _remove_token(indx);
}


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


static void _rolback_create_table(record_ptr )
{
    /* nothing */
}

static void _rolback_drop_table(record_ptr )
{
     /* nothing */
}

static void _rolback_set_table(record_ptr )
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
    return std::move(val);
}


size_t const _get_size_table()
{
    return db_controller_t::instance().size_table();
}


size_t const _get_size_pesronse_buf()
{
    return response_data_t::instance().size();
}

static size_t const _get_index_response_buf(size_t pos)
{
    return response_data_t::instance().get_index(pos);
}

static void _add_index_response_buf(index_t index)
{
    response_data_t::instance().add(index);
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
void _add_token(token_t&& val)
{
    db_controller_t::instance().add(std::move(val));
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
void _save_state_record(index_t indx, token_t&& tok, controller_transact_t controll)
{
    memento_t::instance().set_state(indx, std::move(tok), controll);
}


void _print_token(token_ptr tok)
{
    std::cout << tok->get_date() << "\n";
    std::cout << tok->get_time() << "\n";
    std::cout << tok->get_type() << "\n";
    std::cout << tok->get_descript() << "\n\n"; 
}

void _print_heder()
{
    std::cout << db_controller_t::instance().get_heder_table() << "\n";
}