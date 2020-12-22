#ifndef _VCS_INODE_H_
#define _VCS_INODE_H_

#include <string>
#include "../../db_kernel/includes/db_kernel.h"

struct inode
{
    using inode_msg_t   = std::string;
    using inode_indx_t  = size_t;
    using size_record_t = size_t;  

public:
    inode(inode_msg_t&& , db_kernel_ptr );
    inode(const inode_msg_t& , db_kernel_ptr );
    ~inode();

    inode_indx_t    get_index() const;
    inode_msg_t&    get_message();
    db_kernel_ptr   get_db_ptr() const;
    size_record_t   get_size_record() const;
private:
    inode_msg_t     msg_;
    inode_indx_t    indx_;
    db_kernel_ptr   db_p_;
    size_record_t   size_record_;
};


#endif // !_VCS_INODE_H_
