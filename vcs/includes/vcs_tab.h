#ifndef _VCS_VCS_TAB_H_
#define _VCS_VCS_TAB_H_

#include "inode.h"
#include "inodes.h"
#include "backup.h"
#include "../../db_kernel/includes/db_kernel.h"

namespace vcs
{

using msg_t     = inode::inode_msg_t;
using indx_t    = inode::inode_indx_t;
using table_ptr = db_kernel_ptr;

inodes_ptr      get_inodes();
backup_ptr      get_backup();

void            backup_table(msg_t&& , table_ptr );

inodes_ptr      init_inodes_sys();
backup_ptr      init_backup_sys();

void            reinit_inodes_sys();
void            reinit_backup_sys();

} // namespace vcs

#endif // !_VCS_VCS_TAB_H_
