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

    std::string fn = "/home/islam/CppProgram/db_sysytem_for_it_company/interpret/test/tdata/tdata.txt";
    std::string tn = "table1";
    std::string dt = "18.07.2020";
    std::string ti = "6:52:59";
    std::string sz = "10";

    std::string create_t = "create_t( tn: '" + tn + "' fn: '" + fn + "' sz: '" + sz +"')";
    std::string set_t = "set_t(tn : '" + tn + "')";
    std::string get = "get(dt: '" + dt + "')";

    std::string code  = create_t + "\n" + set_t + "\n" + get;
    std::string trigger_blcok = "  log(ds : '\t\t***||TRIGGER_EVENT||***\n') print_t(tn : 'table1' ) ";
    std::string triggerc = "trigger t1 {  log(ds : '\t\t***||TRIGGER_EVENT||***\n') print_t(tn : 'table1' ) }";
int main()
{



   
   
    exec(std::move(create_t));
   exec(std::move(set_t));
   
   exec("trigger test {log(ds : '\t\t==TRIGGER_EVENT_ADD==\n')  }");
   exec("bef_attach(nm: 'test' op : 'ADD|' )");
   exec("log(ds : 'create trigger and chek in!!\n\n')");

   exec("add(dt : '11.11.11' ti : '11:11' ds : 'description1')"); 
    

    
    /*
        std::string tn = "test";
    lexer<> lex;
    lex.set_code(std::move(trigger_blcok));
    lex.run();

    auto tokens = lex.get_result();
    //printLexer(&tokens);
    list_triggers_t::instance().add("test", std::move(tokens));
    auto t = list_triggers_t::instance().get_trigger_ptr(&tn);

    t->exec();
     */
     

   return 0;
}