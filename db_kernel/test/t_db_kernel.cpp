#include "t_db_kernel.h"

void print_tok(token_ptr tok)
{
    std::cout << "date : " << tok->get_date() << 
    "\ntime : " << tok->get_time() <<
    "\ntype : " << tok->get_type() <<
    "\ndescript: " << tok->get_descript() << "\n";
    
}

void print_heder(word_t heder)
{
    std::cout << "===============================\n";
    std::cout << "heder : " << heder << "\n";
}