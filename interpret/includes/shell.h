#ifndef _SHELL_H_
#define _SHELL_H_

#include <iostream>
#include <string>

#include "lexer.h"
#include "base_parse_api.h"
#include "parser.h"

class shell
{
public:
    shell(const std::string& );
    ~shell();

    void run();

private:
    void exec(std::string&& );

private:
    std::string file_name_;
    lexer lexer_;
};

#endif // !_SHELL_H_
