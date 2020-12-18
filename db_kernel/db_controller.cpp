#include "includes/db_controller.h"
#include "../tools/includes/loger.h"
#include "../interpret/includes/sys_error.h"

#define _EXCEPTION_REQ_
#define _LOGER_BUF_SIZE__   2550
#define _LOGER_FILE_PATH_   "../config/log/error_log.txt"
#define _INIT_FILE_PATH_    "../config/tables/init.txt"
#define _INIT_TABLE_NAME_   "init"

using fname_t             = db_controller::fname_t;
using db_t                = db_controller::db_t;
using table_name_t        = db_controller::table_name_t;
using table_t             = db_controller::table_t;
using table_ptr           = db_controller::table_ptr; 
using tables_t            = db_controller::tables_t;
using table_iter_t        = typename db_controller::table_iter_t;
using table_revers_iter_t = typename db_controller::table_revers_iter_t;

db_controller::db_controller()
{
    try
    {
        init_table(_INIT_TABLE_NAME_,_INIT_FILE_PATH_, 0);
        cur_table_ = get_table(_INIT_TABLE_NAME_);
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::FILE_NOT_FOUND,
            "db_controller::__init__ : can`t create and init table { init }");
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::__init__ ");
    }
}



db_controller::~db_controller()
{}


/* API DB_CONTROLLER */

void db_controller::write_table_to_table(word_t&& tname)
{
    try
    {
        auto table_ptr  = get_table(std::move(tname));
        auto size       = table_ptr->size_table();
        
        for (decltype(size) i = 0; i < size; ++i)
        {
            cur_table_->push_token(
                table_ptr->get(i)->clone()
            );
        }
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
                        "db_controller::write_table_to_table");
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::write_table_to_table");
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::__init__ ");
    }
}

void db_controller::write_table_to_file(word_t&& fname)
{
    try
    {
        cur_table_->write_table_to_file(std::move(fname));   
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
                        "db_controller::write_table_to_table");
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::FILE_NOT_FOUND,
                        "db_controller::write_table_to_table => " + fname);
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::write_table_to_file ");
    }
}



void db_controller::add_table(table_name_t&& dbname, fname_t&& fname, size_t size_table)
{
    try
    {
        auto new_db = make_db_kernel(std::move(fname), size_table);
        tables_[dbname] = std::move(new_db);
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
                        "db_controller::add_table");
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::add_table");
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::FILE_NOT_FOUND,
                        "db_controller::add_table = > " + fname);
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::add_table ");
    }
    
}


table_ptr db_controller::get_table(const table_name_t& tname)
{
    auto table_iter = tables_.find(tname);
    try
    {
        is_exist_table(table_iter);  
    }
    catch(const std::runtime_error& e)
    {
       throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::get_table = > " + tname);
    }
    return table_iter->second.get();
}


void db_controller::set_table(table_name_t&& tname)
{
    try
    {
        cur_table_ = get_table(std::move(tname));  
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::set_table = > " + tname);
    }
}

void db_controller::print_tables()
{
    for (auto &i : tables_)
    {
        auto table = i.second.get();
        printf("%-30s|\t\t%-50s|\t\t%d\n",
                i.first.c_str(), 
                ( (*table->get_file_name_ptr()).c_str() ), 
                table->size_table());
    }
}

void db_controller::print_table(word_t&& tname)
{
    try
    {
        auto table_ptr = get_table(std::move(tname));
        table_ptr->print_table();
    }
    catch(const std::runtime_error e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::print_table = > " + tname);
    }
    
}


table_ptr db_controller::get_table(table_name_t&& tname)
{
    auto table_iter = tables_.find(std::move(tname));
    try
    {
        is_exist_table(table_iter);
    }
    catch(const std::runtime_error& e)
    {;
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::get_table = > " + tname);   
    }
    return table_iter->second.get();
}

db_controller::tables_ptr db_controller::get_tables_ptr() 
{
    return &tables_;
}


void db_controller::is_exist_table(table_iter_t iter)
{
    if (iter == tables_.cend())
    {
        throw std::runtime_error("db_controller: undefine table");
    }
}


void db_controller::log_error(word_t&& type_err, word_t&& descript_err)
{
    log::loger& log = get_loger();
    log.log(std::move(type_err), std::move(descript_err));
}

 /* API DB_KERNEL */

void db_controller::reserve()
{
    cur_table_->reserve();
}

void db_controller::reserve(size_t size)
{
    cur_table_->reserve(size);
}

void db_controller::init_table(table_name_t&& tname, file_name_t&& fname, size_t size_table)
{
    try
    {
        table_name_t table_name = tname;
        add_table(std::move(tname), std::move(fname), size_table);
            
        auto table = get_table(std::move(table_name));
        table->create_table();
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
                        "db_controller::init_table = > " + tname);
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::init_table = > " + tname);
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::init_table ");
    }
}

void db_controller::clear_table(table_name_t&& tname)
{
    try
    {
        table_name_t table_name = tname;
        auto table_ptr = get_table(std::move(tname));
        
        table_ptr->drop_table();
        delete_table(std::move(table_name));
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::clear_table = > " + tname);
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::clear_table ");
    }
}


void db_controller::delete_table(table_name_t&& tname)
{
    try
    {
        auto iter = tables_.find(std::move(tname));
        is_exist_table(iter);
        tables_.erase(iter);
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::delete_table = > " + tname);
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::delete_table = > " + tname);
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::delete_table ");
    }
}

token_ptr db_controller::get(size_t pos)
{
    token_ptr val = nullptr;
    try
    {
        val = cur_table_->get(pos);
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::get");
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::get");
    }
    catch(const std::exception& e)
    {   
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::get");
    }
    return val;
}

void db_controller::add(token_t&& val)
{
    try
    {
        cur_table_->add(std::move(val));
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
                        "db_controller::add");
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::add");
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::add");
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::add ");
    }   
}

void db_controller::insert(size_t pos, token_t&& val)
{
    try
    {
        cur_table_->insert(pos, std::move(val));
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
                        "db_controller::insert");
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::insert");
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::insert");
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::insert");
    }   
}

void db_controller::remove(size_t pos)
{
    try
    {
        cur_table_->remove(pos);
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
                        "db_controller::remove");
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::remove");
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::remove");
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::remove");
    }   
}



void db_controller::update(size_t pos, token_t&& val)
{
    try
    {
        cur_table_->update(pos, std::move(val));
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
                        "db_controller::update");
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::update");
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::update");
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::update ");
    }   
}


void db_controller::update_dt(size_t pos, date_t_&& date)
{
    try
    {
        cur_table_->update_dt(pos, std::move(date));
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
                        "db_controller::update");
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::update");
    }   
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::update");
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::update");
    }   
}

void db_controller::update_ti(size_t pos, time_t_&& time)
{
    try
    {
        cur_table_->update_ti(pos, std::move(time));
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
                        "db_controller::update");
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::update");
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::update");
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::update ");
    }   
}

void db_controller::update_ds(size_t pos, descript_t_&& descript)
{
    try
    {
        cur_table_->update_ds(pos, std::move(descript));
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
                        "db_controller::update");
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::update");
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::update");
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::update");
    }   
}

void db_controller::update_dt_ti(size_t pos, date_t_&& date, time_t_&& time)
{   
    try
    {
        cur_table_->update_dt_ti(pos, std::move(date), std::move(time));
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
                        "db_controller::update");
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::update");
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::update");
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::update ");
    }   
}

void db_controller::update_dt_ds(size_t pos, date_t_&& date, descript_t_&& descript)
{
    try
    {
        cur_table_->update_dt_ds(pos, std::move(date), std::move(descript));
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
                        "db_controller::update");
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::update");
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::update");
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::update ");
    }  
}

void db_controller::update_ti_ds(size_t pos, time_t_&& time, descript_t_&& descript)
{
    try
    {
        cur_table_->update_ti_ds(pos, std::move(time),
                                 std::move(descript));
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
                        "db_controller::update");
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::update");
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::update");
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::update ");
    }   
}

void db_controller::update_dt_ti_ds(size_t pos, 
                                    date_t_&& date, 
                                    time_t_&& time, 
                                    descript_t_&& descript)
{
    try
    {
        cur_table_->update_dt_ti_ds(pos,
                                std::move(date), 
                                std::move(time), 
                                std::move(descript));
    }
    catch(const std::bad_alloc& e)
    {
        throw sys_error(error_type::BAD_ALLOC,
                        "db_controller::update");
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::TABLE_NOT_FOUND,
                        "db_controller::update");
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "db_controller::update");
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::update ");
    }   
}


void db_controller::add_sort_record(statict_key_t&& key, index_t indx)
{
    cur_table_->add_sort_record(std::move(key), indx);
}

statist_ptr db_controller::get_sortRecords()
{
    return cur_table_->get_sortRecords();
}


void db_controller::clear_sortRecords()
{
    cur_table_->clear_sortRecords();
}


void db_controller::for_each_sortRec(sort_method_t method)
{
    cur_table_->for_each_sortRec(method);
}


heder_t db_controller::get_heder_table()
{
    return cur_table_->get_heder();
}

size_t db_controller::size_table()
{
    return cur_table_->size_table();
}

bool db_controller::is_open_table() const
{
    return cur_table_->is_open_file();
}



/*  TRIGERS API */

void db_controller::bef_attach_triger_add(const trigger_ptr t)
{
    try
    {
        cur_table_->bef_attach_triger_add(t);
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::bef_attach_triger_add");
    }
}


void db_controller::bef_attach_triger_remove(const trigger_ptr t)
{
    try
    {
        cur_table_->bef_attach_triger_remove(t);
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::bef_attach_triger_remove");
    }
}

void db_controller::bef_attach_triger_insert(const trigger_ptr t)
{
    try
    {
        cur_table_->bef_attach_triger_insert(t);
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::bef_attach_triger_insert");
    }
}

  


void db_controller::aft_attach_triger_add(const trigger_ptr t)
{
    try
    {
        cur_table_->aft_attach_triger_add(t);
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::aft_attach_triger_add");
    }
}

void db_controller::aft_attach_triger_remove(const trigger_ptr t)
{
    try
    {
        cur_table_->aft_attach_triger_remove(t);
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::aft_attach_triger_remove");
    }
}

void db_controller::aft_attach_triger_insert(const trigger_ptr t)
{
    try
    {
        cur_table_->aft_attach_triger_insert(t);
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::aft_attach_triger_insert");
    }
}


void db_controller::bef_detach_trigger(const trigger_ptr t)
{
    try
    {
        cur_table_->bef_detach_trigger(t);
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::bef_detach_trigger");
    }
}

void db_controller::aft_detach_trigger(const trigger_ptr t)
{
    try
    {
        cur_table_->aft_detach_trigger(t);
    }
    catch(const std::runtime_error& e)
    {
        throw sys_error(error_type::RUNTIME_ERROR,
                        "db_controller::aft_detach_trigger");
    }
}



