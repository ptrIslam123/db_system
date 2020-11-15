#ifndef _T_LEXER_H_
#define _T_LEXER_H_

#include <iostream>
#include "../includes/lexeme.h"

auto printLexer = [](auto container)
{
    lexeme_ptr lex = nullptr;
    const auto size = container.size();
    for (auto i = 0; i < size; ++i)
    {
        lex = container[i].get();
        std::cout << "value : " << lex->get_value() << "\n";
    }
};

#endif // !_T_LEXER_H_
