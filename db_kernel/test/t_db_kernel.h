#ifndef _T_DB_KERNEL_H_
#define _T_DB_KERNEL_H_

#include <iostream>
#include "../includes/token.h"
#include "../includes/db_kernel.h"

using token_ptr = token*;

void print_tok(token_ptr );
void print_heder(word_t );


auto print_db_table = [](auto db)
{
    for (size_t i = 0; i < db->size_table(); ++i)
    {
        std::cout << "===============================\n";
        print_tok(db->get(i));
        std::cout << "===============================\n";
    }
};

#endif // !_T_DB_KERNEL_H_
