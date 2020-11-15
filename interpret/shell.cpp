#include "includes/shell.h"
//#define _LEXER_F_ENBL
//#define  _PARSER_F_ENBL 

shell::shell():
    user_name_("root")
{}

shell::shell(const std::string& user_name):
    user_name_(std::move(user_name))
{}

shell::shell(std::string&& user_name):
    user_name_(std::move(user_name))
{}

shell::~shell()
{}

void shell::run()
{
    init_shell();

    std::string script;
    script.reserve(500);
    
    lexer<> lexer_;

    while (true)
    {
        std::cout << user_name_ << "~#\t";
        std::getline(std::cin, script);

        if (script == "exit")
            break;
        lexer_.set_code(std::move(script));
        lexer_.run();

        base_parse_api base(std::move(lexer_.get_result()));
        parser p(&base);
        p.run();
    }
}

void shell::init_shell()
{
    std::cout << "\t\t\t****|| db_system ||****" << "\n"; 
}