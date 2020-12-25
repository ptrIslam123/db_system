#include "includes/inodes.h"
#include "../interpret/includes/sys_error.h"
#include "../tools/includes/utils.h"
#include <fstream>

using msg_t     = inodes::msg_t;
using indx_t    = inodes::indx_t;
using inode_t   = inodes::inode_t;
using inode_ptr = inodes::inode_ptr;


inodes::inodes():
    capacity_(_MAX_SIZE_POLL_INODE_),
    size_(0),
    indx_(0)
{}

inodes::~inodes()
{}

inode_ptr inodes::add_inode(msg_t&& msg, db_kernel_ptr db_p)
{
    auto new_in = make_inode(std::move(msg), db_p);

    if (size_ >= capacity_)
    {
        size_ = 0;
        is_reused_mem_ = true;
    }

    auto in_p = new_in.get();
    poll_inode_[size_++] = std::move(new_in);
    return in_p;
}

inodes::inode_ptr inodes::get_inode(indx_t indx)
{
    inode_ptr in_p = nullptr;
    size_t size = 0;

    if (!is_reused_mem_)
    {
        size = size_;
    }
    else
    {
        size = capacity_;
    }
    

    for(size_t i = 0; i < size; ++i)
    {
        in_p = (poll_inode_[i]).get();
        if (in_p->get_index() == indx)
        {
            return in_p;
        }
    }

    throw sys_error(error_type::RUNTIME_ERROR,
        "method : inodes::get_inode | undefine inode index => " + cast_i_str(indx));
}

inodes::inode_ptr inodes::get_inode(msg_t&& msg)
{
    inode_ptr in_p = nullptr;
    size_t size = 0;

    if (!is_reused_mem_)
    {
        size = size_;
    }
    else
    {
        size = capacity_;
    }
    

    for(size_t i = 0; i < size; ++i)
    {
        in_p = (poll_inode_[i]).get();
        if (in_p->get_message() == msg)
        {
            return in_p;
        }
    }

    throw sys_error(error_type::RUNTIME_ERROR,
        "method : inodes::get_inode | undefine inode message => " + msg);
}


inode_t inodes::make_inode(msg_t&& msg, db_kernel_ptr db_p)
{
    return std::make_unique<inode>( std::move(msg),
                                    gen_new_index(db_p),
                                    db_p);
}

indx_t inodes::gen_new_index(db_kernel_ptr db_p)
{
    indx_ += (db_p->size_table() * sizeof(token));
    return indx_;
}

size_t inodes::get_size()
{
    return size_;
}

indx_t inodes::get_index()
{
    return indx_;
}