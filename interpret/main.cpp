#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <memory>


#include "includes/lexer.h"
#include "includes/parser.h"



int main()
{
    std::string text = "get(dt: '12.34.21' ti:'12:32' ds: 'text descriptions')";
    lexer<> lex(std::move(text), 100);


    lex.run();
    auto tokens = lex.get_result();

    auto base_ptr = std::make_unique<base_parse_api>(std::move(tokens));
   
    parser p(std::move(base_ptr));
    p.run();

    return 0;
}