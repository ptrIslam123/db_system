#include "includes/db_controller.h"


using fname_t             = db_controller::fname_t;
using db_t                = db_controller::db_t;
using table_name_t        = db_controller::table_name_t;
using table_t             = db_controller::table_t;
using table_ptr           = db_controller::table_ptr; 
using tables_t            = db_controller::tables_t;
using table_iter_t        = typename db_controller::table_iter_t;
using table_revers_iter_t = typename db_controller::table_revers_iter_t;

db_controller::db_controller()
{}

db_controller::db_controller(size_t size_tables):
    size_tables_(size_tables)
{}


db_controller::~db_controller()
{}


/* API DB_CONTROLLER */

void db_controller::add_table(table_name_t&& dbname, fname_t&& fname, size_t size_table)
{
    auto new_db = make_db_kernel(std::move(fname), size_table);
    tables_[dbname] = std::move(new_db);
}


table_ptr db_controller::get_table(const table_name_t& tname)
{
    auto table_iter = tables_.find(tname);
    is_exist_table(table_iter);
    return table_iter->second.get();
}


void db_controller::set_table(table_name_t&& tname)
{
    cur_table_ = get_table(std::move(tname));
}

table_ptr db_controller::get_table(table_name_t&& tname)
{
    auto table_iter = tables_.find(std::move(tname));
    is_exist_table(table_iter);
    return table_iter->second.get();
}


void db_controller::is_exist_table(table_iter_t iter)
{
    if (iter == tables_.cend())
    {
        throw "table not found!";
    }
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
    table_name_t table_name = tname;
    add_table(std::move(tname), std::move(fname), size_table);
    
    auto table = get_table(std::move(table_name));
    table->create_table();
}

void db_controller::clear_table(table_name_t&& tname)
{
    table_name_t table_name = tname;
    auto table_ptr = get_table(std::move(tname));
    
    table_ptr->drop_table();
    delete_table(std::move(table_name));
}


void db_controller::delete_table(table_name_t&& tname)
{
    auto iter = tables_.find(std::move(tname));
    is_exist_table(iter);
    tables_.erase(iter);
}

token_ptr db_controller::get(size_t pos)
{
    return cur_table_->get(pos);
}

void db_controller::add(token_t&& val)
{
    cur_table_->add(std::move(val));
}

void db_controller::insert(size_t pos, token_t&& val)
{
    cur_table_->insert(pos, std::move(val));
}

void db_controller::remove(size_t pos)
{
    cur_table_->remove(pos);
}



void db_controller::update(size_t pos, token_t&& val)
{
    cur_table_->update(pos, std::move(val));
}


void db_controller::update_dt(size_t pos, date_t_&& date)
{
    cur_table_->update_dt(pos, std::move(date));
}

void db_controller::update_ti(size_t pos, time_t_&& time)
{
    cur_table_->update_ti(pos, std::move(time));
}

void db_controller::update_ds(size_t pos, descript_t_&& descript)
{
    cur_table_->update_ds(pos, std::move(descript));
}

void db_controller::update_dt_ti(size_t pos, date_t_&& date, time_t_&& time)
{   
    cur_table_->update_dt_ti(pos, std::move(date), std::move(time));
}

void db_controller::update_dt_ds(size_t pos, date_t_&& date, descript_t_&& descript)
{
    cur_table_->update_dt_ds(pos, std::move(date), std::move(descript));
}

void db_controller::update_ti_ds(size_t pos, time_t_&& time, descript_t_&& descript)
{
    cur_table_->update_ti_ds(pos, std::move(time), std::move(descript));
}

void db_controller::update_dt_ti_ds(size_t pos, 
                                    date_t_&& date, 
                                    time_t_&& time, 
                                    descript_t_&& descript)
{
    cur_table_->update_dt_ti_ds(pos,
                                std::move(date), 
                                std::move(time), 
                                std::move(descript));
}


size_t db_controller::size_table()
{
    return cur_table_->size_table();
}

bool db_controller::is_open_table() const
{
    return cur_table_->is_open_file();
}






