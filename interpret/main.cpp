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
#include "includes/option_parse.h"
#include "../db_kernel/includes/event.h"
#include "includes/list_triggers.h"

    std::string fn1 = "../test/tdata/tdata1.txt";
    std::string fn2 = "../test/tdata/tdata2.txt";
    std::string fn3 = "../test/tdata/big_data.txt";
    std::string tn1 = "table1";
    std::string tn2 = "table2";
    std::string dt = "18.07.2020";
    std::string ti = "6:52:59";
    std::string sz = "10";

    std::string create_t1 = "create_t( tn: '" + tn1 + "' fn: '" + fn1 + "' sz: '" + sz +"')";
    std::string create_t2 = "create_t( tn: '" + tn2 + "' fn: '" + fn2 + "' sz: '" + sz +"')";
    std::string set_t1 = "set_t(tn : '" + tn1 + "')";
    std::string set_t2 = "set_t(tn : '" + tn2 + "')";
    std::string get = "get(dt: '" + dt + "')";

    std::string code  = create_t1 + "\n" + set_t1 + "\n" + get;
    std::string trigger_blcok = "  log(ds : '\t\t***||TRIGGER_EVENT||***\n') print_t(tn : 'table1' ) ";
    std::string triggerc = "trigger t1 {  log(ds : '\t\t***||TRIGGER_EVENT||***\n') print_t(tn : 'table1' ) }";



int main()
{
   exec("create_t(tn : '" + tn1 + "' fn : '" + fn1 + "' sz : '10')");
   exec("set_t(tn : '" + tn1 + "')");
   exec("print_t(tn : '" + tn1 + "'')");
    
   
   return 0;
}