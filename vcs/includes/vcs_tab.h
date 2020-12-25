#ifndef _VCS_VCS_TAB_H_
#define _VCS_VCS_TAB_H_

#include "inode.h"
#include "inodes.h"
#include "../../db_kernel/includes/db_kernel.h"

/*  НЕОБХОДИМО ПЕРВОНАЧАЛЬНО ЗАПИСАТЬ ОБРАЗ
    INODES НА ФАЙЛ ПЕРЕД ЕГО ИСПОЛЬЗОВАНИЕМ! */

namespace vcs
{

using msg_t     = inode::inode_msg_t;
using indx_t    = inode::inode_indx_t;
using inode_ptr = inodes::inode_ptr;
using table_ptr = db_kernel_ptr;


void            backup_table(msg_t&& , table_ptr );
void            roll_back_db(inode_ptr );
inode_ptr       find_inode(indx_t );
inode_ptr       find_inode(msg_t&& );
inodes_ptr      get_inodes();

} // namespace vcs

#endif // !_VCS_VCS_TAB_H_
