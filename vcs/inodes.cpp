#include "includes/inodes.h"
#include "../interpret/includes/sys_error.h"
#include "../tools/includes/utils.h"

#include <fstream>

#define _INODES_FILE_PATH_ "../config/backup/"

inodes_ptr get_inodes()
{
    static std::fstream fs(_INODES_FILE_PATH_);
    static inodes_ptr inodes_   = nullptr;
    static bool is_init         = false;

    if (!is_init)
    {
        /* reading object inode from file! */
        is_init = true;        
    }
    
    if (fs.is_open())
    {
        return inodes_;
    }
    else
    {
        throw sys_error(error_type::FILE_NOT_FOUND,
            "method : get_inodes | file => " + std::string(_INODES_FILE_PATH_) );
    }
}

inodes::inodes():
    size_(0)
{}

inodes::~inodes()
{}

void inodes::add_inode(inode_t&& in)
{
    if (size_ >= _MAX_SIZE_POLL_INODE_)
    {
        size_ = 0;
    }
    poll_inode_[size_++] = std::move(in);
}

inodes::inode_ptr inodes::get_inode(size_t pos)
{
    if (pos >= _MAX_SIZE_POLL_INODE_)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
            "method : inodes::get_inode | out of range [position] => " + cast_i_str(pos));
    }
    
    return (poll_inode_[pos]).get();
}

size_t inodes::get_size()
{
    return size_;
}