#include "includes/vcs_tab.h"

namespace vcs{


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


inodes_ptr  init_inodes_sys()
{
    return nullptr;
}

backup_ptr  init_backup_sys()
{
    return nullptr;
}


void reinit_inodes_sys()
{

}

void reinit_backup_sys()
{

}

} // namespace vcs