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


void            backup_table(msg_t&& , table_ptr );

inodes_ptr      get_inodes();
backup_ptr      get_backup();

void            init_inodes_sys(inodes_ptr );
void            init_backup_sys(inodes_ptr );



} // namespace vcs

#endif // !_VCS_VCS_TAB_H_
