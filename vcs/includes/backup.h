#ifndef _VCS_BACKUP_H_
#define _VCS_BACKUP_H_

#include <fstream>
#include <string>

#include "inode.h"
#include "../../db_kernel/includes/db_kernel.h"

struct backup;
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

    void            write_db(inode_ptr );
    void            read_db(inode_ptr , db_kernel_ptr );

    void            write(record_t , const size_record_t );
    void            read(record_t , const size_record_t );
    fname_t&        get_fname();

private:
    std::fstream    file_;
    fname_t         fname_;
    size_record_t   size_rt_;
    size_t          indx_;
};


#endif // !_VCS_BACKUP_H_
