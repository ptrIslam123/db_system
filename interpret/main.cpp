#include <iostream>
#include <memory>
#include <map>
#include <vector>


#include "includes/lexer.h"
#include "includes/parser.h"
#include "includes/base_parse_api.h"
#include "includes/response_data.h"
#include "test/t_lexer.h"
#include "includes/shell.h"

    std::string fn = "/home/islam/CppProgram/db_sysytem_for_it_company/interpret/test/tdata/tdata.txt";
    std::string tn = "table1";
    std::string dt = "18.07.2020";
    std::string ti = "6:52:59";
    std::string sz = "10";

    std::string create_t = "create_t( tn: '" + tn + "' fn: '" + fn + "' sz: '" + sz +"')";
    std::string set_t = "set_t(tn : '" + tn + "')";
    std::string get = "get(dt: '" + dt + "')";

    std::string code  = create_t + "\n" + set_t + "\n" + get;

int main()
{

    exec(std::move(create_t));
    exec(std::move(set_t));

    exec("print_t(tn : '"+ tn +"')");
    exec("log(ds : '\n===============\n')");
    exec("print_t()");
    return 0;
}