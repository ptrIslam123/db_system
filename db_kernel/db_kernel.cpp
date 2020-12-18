#include "includes/db_kernel.h"
#include "../tools/includes/files.h"
#include "../interpret/includes/sys_error.h"
#include "../tools/includes/utils.h"

//#define _MALLOC_DEB_INF_F_
#define _ENBL_API_TRIGERS_
//#define _ENBL_DEBUG_OP_

#ifndef _ENBL_DEBUG_OP_
#define _UNENBL_API_TRIGERS_
#define _UNENBL_DEBUG_ADD_OP_
#define _UNENBL_DEBUG_INSERT_OP_
#define _UNENBL_DEBUG_REMOVE_OP_
#define _UNENBL_DEBUG_UPDATE_OP_
#define _UNENBL_DEBUG_DROP_TABLE_OP_
#define _UNENBL_DEBUG_CREATE_TABLE_OP_ 
#endif // _ENBL_DEBUG_OP_
#define LOG_OP(MSG)  printBlue(MSG)

 
db_kernel_t make_db_kernel(std::string&& fname, size_t beg_cont_size)
{
    auto fstream_ = std::make_unique<file_stream>(std::move(fname));
    auto tok_gramm_ = std::make_unique<tokenize_grammar>(std::move(fstream_));
    return std::make_unique<db_kernel>(
        std::move(tok_gramm_),
        beg_cont_size
    );
}


#ifndef _BAD_ALLOC_DB_KERNEL_T_

db_kernel_ptr alloc_db_kernel(std::string&& fname, size_t beg_cont_size)
{   
    /* пока не работающая верно реализация, 
    надо будет доработать функции создания ядра БД*/
    db_kernel* db = nullptr;
    tokenize_grammar* tok_gramm_ptr = nullptr;
    file_stream* f_stream_ptr = nullptr;

    auto size_db_kernel = sizeof(db_kernel);
    auto size_file_stream = sizeof(file_stream);
    auto size_tok_grammar = sizeof(tokenize_grammar);
    auto total_size = size_db_kernel + size_file_stream + size_tok_grammar;

   
    db = (db_kernel*)malloc(total_size);

    tok_gramm_ptr = (tokenize_grammar*)(db + size_db_kernel);
    f_stream_ptr = (file_stream*)(db + size_db_kernel + size_tok_grammar);

    ::new (f_stream_ptr) file_stream(std::move(fname));
    ::new(tok_gramm_ptr) tokenize_grammar(f_stream_ptr);
    ::new(db) db_kernel(tok_gramm_ptr, beg_cont_size);

    return db;
}

#endif // !_BAD_ALLOC_DB_KERNEL_T_


db_kernel::db_kernel
(tok_gramm_t&& tok_gramm, size_t beg_cont_size):
    tok_gramm_(std::move(tok_gramm)),
    beg_cont_size_(beg_cont_size)
{
#ifndef _MALLOC_DEB_INF_F_
    malloc_deb_inf("db_kernel()\n");
#endif // _MALLOC_DEB_INF_F_
}


db_kernel::~db_kernel()
{
#ifndef _MALLOC_DEB_INF_F_
    malloc_deb_inf("~db_kernel()\n");
#endif // _MALLOC_DEB_INF_F_
}


void db_kernel::reserve()
{
    container_.reserve(beg_cont_size_);
}

void db_kernel::reserve(size_t beg_cont_size)
{
    beg_cont_size_ = beg_cont_size;
    container_.reserve(beg_cont_size_);
}

void db_kernel::create_table()
{
#ifndef _UNENBL_DEBUG_CREATE_TABLE_OP_
    printBlue("CREATE TABLE");
#endif // !_UNENBL_DEBUG_ADD_OP_

    open_file();
    heder_ = tok_gramm_->tokenize_heder();  // -Wall std::move(tokenize_heder())
    while (!tok_gramm_->is_eof())
    {
        push_token(
            tok_gramm_->tokenize()   // -Wall std::move(tok_gramm_->tokenize())
        );
    }
}


void db_kernel::drop_table()
{
#ifndef _UNENBL_DEBUG_DROP_TABLE_OP_
    printBlue("DROP TABLE");
#endif // !_UNENBL_DEBUG_ADD_OP_

    /* delete table */
   container_.clear();
}


void db_kernel::print_table()
{
    auto size = size_table();
    
    for (decltype(size) i = 0; i < size ; ++i)
    {
        print_token(get(i), i + 1);
    }
}

void db_kernel::print_token(const token_ptr tok, const size_t index)
{
    tok->print(index);
}


void db_kernel::write_table_to_file(word_t&& fname)
{
    try
    {
        files file(std::move(fname));
        file.write(get_heder());

        auto size       = size_table();
        token_ptr val   = nullptr;

        for (decltype(size) i = 0; i < size; ++i)
        {
            file.write("\n");

            val = get(i);
            auto record =   val->get_date()     + " " + 
                            val->get_time()     + "\t" +
                            get_type_token()    + "\t\t" +
                            val->get_descript();
                            
            file.write(std::move(record));
        }
    }
    catch(const std::string& e)
    {
        std::cout << e << '\n';
    }
}


tok_gramm_t db_kernel::get_tok_gramm() 
{
    return std::move(tok_gramm_);
}

token_ptr db_kernel::get(size_t pos)
{
    iter_ = container_.begin();
    std::advance(iter_, pos);
    return (*iter_).get();
}

size_t db_kernel::size_table() 
{
    return container_.size();
}

void db_kernel::push_token(token_t&& val)
{
    container_.push_back(std::move(val));
}


void db_kernel::add(token_t&& val)
{
#ifdef _ENBL_API_TRIGERS_
    befEventAdd_.notify();
#endif // !_ENBL_API_TRIGERS_

#ifndef _UNENBL_DEBUG_ADD_OP_
    printBlue("ADD TOKEN");
    val->print();
#endif // !_UNENBL_DEBUG_ADD_OP_

    container_.push_back(std::move(val));

#ifdef _ENBL_API_TRIGERS_
    aftEventAdd_.notify();
#endif // !_ENBL_API_TRIGERS_
}


void db_kernel::insert(size_t pos, token_t&& val)
{
#ifdef _ENBL_API_TRIGERS_
    befEventInsert_.notify();
#endif // !_ENBL_API_TRIGERS_

    iter_ = container_.begin();
    std::advance(iter_, pos);

#ifndef _UNENBL_DEBUG_INSERT_OP_
    printBlue("INSERT TOKEN");
    val->print();
#endif // !_UNENBL_DEBUG_REMOVE_OP_

    container_.insert(iter_, std::move(val));

#ifdef _ENBL_API_TRIGERS_
    aftEventInsert_.notify();
#endif // !_ENBL_API_TRIGERS_
}


void db_kernel::remove(size_t pos)
{
#ifdef _ENBL_API_TRIGERS_
    befEventRemove_.notify();
#endif // !_ENBL_API_TRIGERS_

    iter_ = container_.begin();
    std::advance(iter_, pos);

#ifndef _UNENBL_DEBUG_REMOVE_OP_
    printBlue("REMOVE TOKEN");
    (iter_->get())->print();
#endif // !_UNENBL_DEBUG_REMOVE_OP_

    container_.erase(iter_);

#ifdef _ENBL_API_TRIGERS_
    aftEventRemove_.notify();
#endif // !_ENBL_API_TRIGERS_
}


void db_kernel::update(size_t pos, token_t&& val)
{
    iter_ = container_.begin();
    std::advance(iter_, pos);
    *iter_ = std::move(val);
}


void db_kernel::update_dt(size_t pos, date_t_&& date)
{
    auto tok = get_token(pos);
    tok->set_date(std::move(date));
}

void db_kernel::update_ti(size_t pos, time_t_&& time)
{
    auto tok = get_token(pos);
    tok->set_time(std::move(time));
}

void db_kernel::update_ds(size_t pos, descript_t_&& descript)
{
    auto tok = get_token(pos);
    tok->set_descript(std::move(descript));
}

void db_kernel::update_dt_ti(size_t pos, date_t_&& date, time_t_&& time)
{
    auto tok = get_token(pos);
    tok->set_date(std::move(date));
    tok->set_time(std::move(time));
}

void db_kernel::update_dt_ds(size_t pos, date_t_&& date, descript_t_&& descript)
{
    auto tok = get_token(pos);
    tok->set_date(std::move(date));
    tok->set_descript(std::move(descript));
}

void db_kernel::update_ti_ds(size_t pos, time_t_&& time, descript_t_&& descript)
{
    auto tok = get_token(pos);
    tok->set_time(std::move(time));
    tok->set_descript(std::move(descript));
}

void db_kernel::update_dt_ti_ds(size_t pos, 
                                date_t_&& date, 
                                time_t_&& time, 
                                descript_t_&& descript)
{
    auto tok = get_token(pos);
    tok->set_date(std::move(date));
    tok->set_time(std::move(time));
    tok->set_descript(std::move(descript));
}

 /* SORT RECORDS API */

#define IS_EXISTS(ITER) ITER != sortRecords_.cend()
#define FIRST 1

void db_kernel::add_sort_record(statist_key_t&& key, index_t indx)
{
    auto iter = sortRecords_.find(key);
    
    if (IS_EXISTS(iter))
    {
        auto list_i = iter->second.get();
        list_i->push_back(indx);
        list_i->front()++;
    }
    else
    {
        auto val = std::make_unique<statist_value_t>();
        val->push_back(FIRST);
        val->push_back(indx);

        sortRecords_[std::move(key)] = std::move(val);  
    }
}


statist_ptr db_kernel::get_sortRecords()
{
    return &sortRecords_;
}


void db_kernel::clear_sortRecords()
{
    sortRecords_.clear();
}

void db_kernel::for_each_sortRec(sort_method_t method)
{
    for (auto &i : sortRecords_)
    {
        word_t w = std::move(i.first);
        method(std::move(w), i.second.get());
    }
}

token_ptr db_kernel::get_token(size_t pos)
{
    auto iter = container_.begin();
    std::advance(iter, pos);
    return (*iter).get();
}


word_t& db_kernel::get_heder()
{
    return heder_;
}

word_ptr db_kernel::get_heder_ptr()
{
    return &heder_;
}

word_ptr db_kernel::get_file_name_ptr()
{
    return tok_gramm_->get_file_ptr();
}

bool db_kernel::is_open_file() const
{
    return tok_gramm_->is_open_file();
}

void db_kernel::open_file()
{
    bool is_open_f = tok_gramm_->is_open_file();
    if (!is_open_f)
    {
        auto errmsg = "db_kernel::open_file() : " + *(get_file_name_ptr());
        throw sys_error(error_type::FILE_NOT_FOUND,
            std::move(errmsg));
    }
}


/*  TRIGERS API */

void db_kernel::bef_attach_triger_add(const trigger_ptr t)
{
    befEventAdd_.attach(t);
}

void db_kernel::bef_attach_triger_remove(const trigger_ptr t)
{
    befEventRemove_.attach(t);
}

void db_kernel::bef_attach_triger_insert(const trigger_ptr t)
{
    befEventInsert_.attach(t);
}
 



void db_kernel::aft_attach_triger_add(const trigger_ptr t)
{
    aftEventAdd_.attach(t);
}

void db_kernel::aft_attach_triger_remove(const trigger_ptr t)
{
    aftEventRemove_.attach(t);
}

void db_kernel::aft_attach_triger_insert(const trigger_ptr t)
{
    aftEventInsert_.attach(t);
}


void db_kernel::bef_detach_trigger(const trigger_ptr t)
{
    befEventAdd_.detach(t);
    befEventInsert_.detach(t);
    befEventRemove_.detach(t);
}

void db_kernel::aft_detach_trigger(const trigger_ptr t)
{
    aftEventAdd_.detach(t);
    aftEventInsert_.detach(t);
    aftEventRemove_.detach(t);
}

    
