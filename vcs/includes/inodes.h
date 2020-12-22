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
    using inode_t   = std::unique_ptr<inode>;
    using inode_ptr = inode*;
    using inodes_t  = std::array<inode_t, _MAX_SIZE_POLL_INODE_>;

public:
    inodes();
    ~inodes();

    void        add_inode(inode_t&& );
    inode_ptr   get_inode(size_t );
    size_t      get_size();

private:
    inodes_t    poll_inode_;
    size_t      size_;
};


#endif // !_VCS_INDES_H_
