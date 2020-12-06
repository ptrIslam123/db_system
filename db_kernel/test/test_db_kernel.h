#ifndef _TEST__TEST_DB_KERNEL_H
#define _TEST__TEST_DB_KERNEL_H

#include "../includes/db_kernel.h"
#include <string>

namespace test_db_kerenel
{

using db_ptr   = db_kernel_ptr;


void        test_remove(db_ptr ,size_t );
void        test_add(db_ptr , token_t&& val);
void        test_insert(db_ptr , size_t , token_t&& );
void        test_update(db_ptr );
token_ptr   test_get(db_ptr , size_t );
void        test_create_table(db_ptr );
void        test_drop_table(db_ptr );
void        test_open_file(db_ptr );
void        test_print_table(db_ptr );


void        printRed(const std::string& );
void        printBlue(const std::string& );

}



#endif // !_TEST__TEST_DB_KERNEL_H