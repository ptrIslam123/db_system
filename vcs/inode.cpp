#include "includes/inode.h"

using inode_indx_t  = inode::inode_indx_t;
using inode_msg_t   = inode::inode_msg_t;

inode::inode(inode_msg_t&& msg, db_kernel_ptr db_p):
    msg_(std::move(msg)),
    indx_(NULL),
    db_p_(db_p),
    size_record_(db_p->size_table())
{}

inode::inode(const inode_msg_t& msg, db_kernel_ptr db_p):
    msg_(msg),
    indx_(NULL),
    db_p_(db_p),
    size_record_(db_p->size_table())
{}

inode::~inode()
{}

inode_indx_t inode::get_index() const
{
    return indx_;
}

inode_msg_t& inode::get_message()
{
    return msg_;
}

db_kernel_ptr inode::get_db_ptr() const
{
    return db_p_;
}

inode::size_record_t inode::get_size_record() const
{
    return size_record_;
}