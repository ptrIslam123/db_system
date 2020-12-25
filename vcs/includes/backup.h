#ifndef _VCS_BACKUP_H_
#define _VCS_BACKUP_H_

#include <fstream>
#include <string>

#include "inode.h"
#include "../../db_kernel/includes/db_kernel.h"
#include "../../tools/includes/singleton.h"

struct backup;
using backup_t          = singleton_classic<backup>;
using backup_ptr        = backup*; 

struct backup
{
    using inode_t       = inode;
    using inode_ptr     = inode_t*;
    using record_t      = token_ptr;
    using size_record_t = size_t;
    using fname_t       = std::string;

public:
    backup(fname_t&& );
    backup(const fname_t& );
    ~backup();

    void                write_db(inode_ptr );
    void                read_db(inode_ptr );
    fname_t&            get_fname();

private:
    void                set_fseek(index_t );
    void                write(record_t , const size_record_t );
    void                read(record_t , const size_record_t );

private:
    std::fstream        file_;
    fname_t             fname_;
    size_record_t       size_rt_;
};


#endif // !_VCS_BACKUP_H_
