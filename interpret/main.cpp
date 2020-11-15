#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <memory>


#include "includes/lexer.h"
#include "includes/parser.h"
#include "includes/base_parse_api.h"
#include "includes/response_data.h"
#include "test/t_lexer.h"



int main()
{
    std::string fn = "/home/islam/CppProgram/db_sysytem_for_it_company/db_kernel/data/data.txt";
    std::string tn = "table1";
    std::string dt = "18.07.2020";
    std::string sz = "10";

    std::string create_t = "create_t( tn: '" + tn + "' fn: '" + fn + "' sz: '" + sz +"')";
    std::string set_t = "set_t(tn : '" + tn + "')";
    std::string get = "get(dt: '" + dt + "')";
   
    std::string code  = create_t + "\n" + set_t + "\n" + get;

    lexer<> lex(std::move(create_t + set_t), 200);
    lex.run();
    auto tokens = lex.get_result();
    
    auto base = std::make_unique<base_parse_api>(std::move(tokens));
    
    parser p(std::move(base));
    try
    {
        p.run(); 
    }
    catch(const char* emsg)
    {
        std::cerr << emsg << '\n';
    }
    

   

    return 0;
}