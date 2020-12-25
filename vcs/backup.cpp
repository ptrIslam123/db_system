#include "includes/backup.h"
#include "../interpret/includes/sys_error.h"
#include "../tools/includes/utils.h"


backup::backup(fname_t&& fname):
    fname_(fname),
    size_rt_(sizeof(token))
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
    size_rt_(sizeof(token))
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
    set_fseek(in_p->get_index());

    auto db_p       = in_p->get_db_ptr();
    auto size       = in_p->get_size_record();

    for (decltype(size) i = 0; i < size; ++i)
    {
        write(db_p->get(i), size_rt_);
    }
}

void backup::read_db(inode_ptr in_p)
{
   set_fseek(in_p->get_index());

   auto db_p        = in_p->get_db_ptr();
   auto size        = in_p->get_size_record();
   auto size_db     = db_p->size_table();
   decltype(size) i = 0;
   record_t t       = nullptr;

   for ( ; i < size; ++i)
   {
       read(t, size_rt_);
       db_p->update(i, make_token(t));
   }

   try
   {
       for( ; i < size_db; ++i)
       {
           db_p->remove(i);
       }
   }
   catch(const std::out_of_range& e)
   {
       throw sys_error(error_type::OUT_OF_RANGE,
        "method : backup::read_db | indxe => " + cast_i_str(i));
   }
   
}


void backup::set_fseek(index_t indx)
{
    file_.seekg(indx, std::ios::beg);
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
