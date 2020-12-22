#include "includes/vcs_tab.h"
#include "../interpret/includes/sys_error.h"

#define _BACKUP_COPY_FILE_PATH_ "../config/backup/backup.copy"
#define _INODES_CNF__FILE_PATH_ "../config/backup/inodes.cnf"
#define _SIZE_INODES_ (sizeof(inodes))
#define _SIZE_BACKUP_ (sizeof(backup))

namespace vcs{


void backup_table(msg_t&& msg, table_ptr table_p)
{
    auto inodes_ = get_inodes();
    auto backup_ = get_backup();

    auto new_inode = std::make_unique<inode>(
                        std::move(msg),
                        table_p
                    );

    inodes_->add_inode(
        std::move(new_inode)
    );

    backup_->write_db(new_inode.get());
}



inodes_ptr  get_inodes()
{
    static inodes_ptr inodes_   = nullptr;
    static bool is_init         = false;

    if (!is_init)
    {
        inodes_ = init_inodes_sys();
        is_init = true;
    }
    return inodes_;
}

backup_ptr  get_backup()
{
    static backup_ptr backup_   = nullptr;
    static bool is_init         = false;

    if (!is_init)
    {
        backup_ = init_backup_sys();
        is_init = true;
    }
    return backup_;
}


void  init_inodes_sys(inodes_ptr in_p)
{
    std::ifstream ifs(_INODES_CNF__FILE_PATH_);
    if (ifs.is_open())
    {
        ifs.read((char*)in_p, _SIZE_INODES_);
        return;
    }
    throw sys_error(error_type::FILE_NOT_FOUND,
        "method : init_inodes_sys | file => " + std::string(_INODES_CNF__FILE_PATH_));
}

void  init_backup_sys(inodes_ptr bk_p)
{
    std::ifstream ifs(_BACKUP_COPY_FILE_PATH_);
    if (ifs.is_open())
    {
        ifs.read((char*)in_p, _SIZE_BACKUP_);
        return;
    }
    throw sys_error(error_type::FILE_NOT_FOUND,
        "method : init_backup_sys | file => " + std::string(_BACKUP_COPY_FILE_PATH_));
}



} // namespace vcs