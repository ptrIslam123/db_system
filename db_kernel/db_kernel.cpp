#include "includes/db_kernel.h"
//#define _MALLOC_DEB_INF_F_

 
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
    open_file();
    heder_ = std::move(tok_gramm_->tokenize_heder());
    while (!tok_gramm_->is_eof())
    {
        add(
            std::move(tok_gramm_->tokenize())
        );
    }
}


void db_kernel::drop_table()
{
    /* delete table */
   container_.clear();
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


void db_kernel::add(token_t&& val)
{
    container_.push_back(std::move(val));
}


void db_kernel::insert(size_t pos, token_t&& val)
{
    iter_ = container_.begin();
    std::advance(iter_, pos);
    container_.insert(iter_, std::move(val));
}


void db_kernel::remove(size_t pos)
{
    iter_ = container_.begin();
    std::advance(iter_, pos);
    container_.erase(iter_);
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

bool db_kernel::is_open_file() const
{
    return tok_gramm_->is_open_file();
}

void db_kernel::open_file()
{
    bool is_open_f = tok_gramm_->is_open_file();
    if(!is_open_f)
    {
        /* 
        error_report(
            F_PATH_DB_KERNEL_DEGUB_INF,
            "\n\n#~ db_kernel::open_file()\n\n"
        );
        error_report(
            F_PATH_DB_KERNEL_DEGUB_INF,
            std::string("file not found: " + tok_gramm_->get_file() + "\n")
        );
        */
        throw "db_kernel : method : open_file | file not found";
    }
}
