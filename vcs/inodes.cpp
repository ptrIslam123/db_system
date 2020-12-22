#include "includes/inodes.h"
#include "../interpret/includes/sys_error.h"
#include "../tools/includes/utils.h"
#include <fstream>


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
    capacity_           += in->get_size_record();
    poll_inode_[size_++] = std::move(in);
}

inodes::inode_ptr inodes::get_inode(size_t indx)
{
    inode_ptr in_p = nullptr;

    for(size_t i = 0; i < size_; ++i)
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

size_t inodes::get_size()
{
    return size_;
}

size_t inodes::get_cur_index()
{
    return capacity_;
}