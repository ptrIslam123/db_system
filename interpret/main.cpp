#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <memory>


#include "includes/lexer.h"
#include "includes/args_data.h"
#include "includes/sys_functions.h"
#include "includes/memento.h"
#include "includes/transact_error.h"
#include "includes/base_parse_api.h"

int main()
{
    std::string text = "get(dt: '*')";
    lexer<> lex(std::move(text), 100);

    lex.run();
    auto tokens = lex.get_result();

   
    return 0;
}