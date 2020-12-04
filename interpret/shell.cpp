#include "includes/shell.h"
#include "../tools/includes/files.h"
#include "includes/sys_error.h"


shell::shell(const std::string& file_name):
    file_name_(file_name)
{}

shell::~shell()
{}


void shell::run()
{
    files file(file_name_);
    auto code =  file.read();

    exec(std::move(code));
}

void shell::exec(std::string&& code)
{
    try
    {
        lexer_.set_code(std::move(code));
        lexer_.run();

        auto lexemes = lexer_.get_result();
        base_parse_api base_p_api(&lexemes);
        
        parser p(&base_p_api);
        
        while (!base_p_api.is_end())
            p.run();
    }
    catch(const std::runtime_error& e)
    {
        std::cout << e.what() << "\n";
        exit(-1);
    }
    catch(sys_error& e)
    {
        e.write_log();
        e.what();
        exit(-1);
    }
    catch(const char* e)
    {
        std::cerr << e << "\n";
        exit(1);
    }  
}
