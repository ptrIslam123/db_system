#ifndef _T_LEXER_H_
#define _T_LEXER_H_

#include <iostream>
#include "../includes/lexeme.h"
#include "../includes/lexer.h"
#include "../includes/base_parse_api.h"
#include "../includes/parser.h"

auto printLexer = [](std_container_type* container)
{
    lexeme_ptr lex = nullptr;
    const auto size = container->size();
    for (auto i = 0; i < size; ++i)
    {
        lex = container->at(i).get();
        std::cout << "value : " << lex->get_value() << "\n";
    }
};


void exec(std::string&& code)
{
    auto ccode = code;
    try
    {
        lexer<> lex(std::move(code), 200);
        lex.run();

        base_parse_api base(std::move(lex.get_result()));

        parser p(&base);
        p.run();
        //std::cout << "\t\t***|| execute command ||***\n";
        std::cout << "\n";
    }
    catch(const char* e)
    {
        std::cerr << "\t\t***||error execute: " << ccode << " | " << e << " ||***\n";
    }  
}

#endif // !_T_LEXER_H_
