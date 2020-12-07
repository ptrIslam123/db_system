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
    auto size = container->size();
    
    for (decltype(size) i = 0; i < size; ++i)
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
        lexer lex(std::move(code), 200);
        lex.run();

        auto lexemes = lex.get_result();

        base_parse_api base(&lexemes);

        parser p(&base);
        p.run();
        
        std::cout << "\n";
    }
    catch(const char* e)
    {
        std::cerr << e << "\n";
        exit(1);
    }  
}

#endif // !_T_LEXER_H_
