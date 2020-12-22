#include "includes/backup.h"
#include "../interpret/includes/sys_error.h"
#include "../tools/includes/utils.h"

backup::backup(fname_t&& fname):
    fname_(fname),
    size_rt_(0)
{
    file_.open(fname_,  std::ios::binary    |
                        std::ios::in        | 
                        std::ios::out);
    
    if (!file_.is_open())
    {
        throw sys_error(error_type::FILE_NOT_FOUND,
            "method : backup::backup| file => " + fname_);
    }
}

backup::backup(const fname_t& fname):
    fname_(std::move(fname)),
    size_rt_(0)
{
    file_.open(fname_,  std::ios::binary    |
                        std::ios::in        | 
                        std::ios::out);

    if (!file_.is_open())
    {
        throw sys_error(error_type::FILE_NOT_FOUND,
            "method : backup::backup| file => " + fname_);
    }
}

backup::~backup()
{
    file_.close();
}



void backup::write_db(inode_ptr in_p)
{
    auto db_p       = in_p->get_db_ptr();
    auto size_db    = db_p->size_table();

    for(decltype(size_db) i = 0; i < size_db; ++i)
    {
        write(db_p->get(i), size_rt_);
    } 
}

void backup::read_db(inode_ptr in_p, db_kernel_ptr db_p)
{
    auto offset             = in_p->get_index();
    auto size_db            = in_p->get_size_record();
    auto size_db_old_table  = db_p->size_table();
    
    decltype(size_db) i     = 0;
    record_t r              = nullptr;

    file_.seekg(offset);

    for (i = 0; i < size_db; ++i)
    {
        read(r, size_rt_);
        db_p->update(i, make_token(r));
    }
    
    try
    {
        for ( ; i < size_db_old_table; ++i)
        {
            db_p->remove(i);
        }
    }
    catch(const std::out_of_range& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
            "method : backup::read_db | index => " + cast_i_str(i));
    }
    
}


void backup::write(record_t r, const size_record_t size_r)
{
    file_.write((char*)r, size_r);
}

void backup::read(record_t r, const size_record_t size_r)
{
    file_.read((char*)r, size_r);
}

backup::fname_t& backup::get_fname()
{
    return fname_;
}
