#include "includes/vcs_tab.h"
#include "includes/backup.h"
#include "../interpret/includes/sys_error.h"

#define _BACKUP_COPY_FILE_PATH_ "../config/backup/backup.copy"
#define _INODES_CNF__FILE_PATH_ "../config/backup/inodes.cnf"
#define _SIZE_INODES_ (sizeof(inodes))
#define _SIZE_BACKUP_ (sizeof(backup))


namespace vcs{

void backup_table(msg_t&& msg, table_ptr tbl_p)
{
    auto ins    = vcs::get_inodes();
    auto new_in = ins->add_inode(std::move(msg), tbl_p);

    backup_t::instance(_BACKUP_COPY_FILE_PATH_).write_db(new_in);
}


void roll_back_db(inode_ptr in_p)
{
    backup_t::instance(_BACKUP_COPY_FILE_PATH_).read_db(in_p);
}


inode_ptr find_inode(indx_t indx)
{
    auto ins = vcs::get_inodes();
    return ins->get_inode(indx);
}

inode_ptr find_inode(msg_t&& msg)
{
    auto ins = vcs::get_inodes();
    return ins->get_inode(std::move(msg));
}


inodes_ptr get_inodes()
{
    static inodes_ptr inodes_   = nullptr;
    static bool is_init         = false;

    if (!is_init)
    {
        std::ifstream ifs(_INODES_CNF__FILE_PATH_);

        ifs.read((char*)inodes_, sizeof(inodes));

        ifs.close();
    }
    return inodes_;
}

} // namespace vcs