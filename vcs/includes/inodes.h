#ifndef _VCS_INDES_H_
#define _VCS_INDES_H_
#define _MAX_SIZE_POLL_INODE_ 10000

#include <array>
#include <memory>
#include "inode.h"

struct inodes;
using inodes_ptr    = inodes*;

inodes_ptr get_inodes();

struct inodes
{
    using msg_t     = inode::inode_msg_t;
    using indx_t    = inode::inode_indx_t;
    using inode_t   = std::unique_ptr<inode>;
    using inode_ptr = inode*;
    using inodes_t  = std::array<inode_t, _MAX_SIZE_POLL_INODE_>;

public:
    inodes();
    ~inodes();

    inode_ptr       add_inode(msg_t&& , db_kernel_ptr );
    inode_ptr       get_inode(indx_t );
    inode_ptr       get_inode(msg_t&& );
    size_t          get_size();
    indx_t          get_index();

private:
    inode_t         make_inode(msg_t&& , db_kernel_ptr );
    indx_t          gen_new_index(db_kernel_ptr );
private:
    inodes_t        poll_inode_;
    size_t          capacity_;
    size_t          size_;
    indx_t          indx_;
    bool            is_reused_mem_;
};


#endif // !_VCS_INDES_H_
