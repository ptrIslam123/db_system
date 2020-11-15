#ifndef _SHELL_H_
#define _SHELL_H_

#include <iostream>
#include <string>
#include <memory>

#include "lexer.h"
#include "base_parse_api.h"
#include "parser.h"

class shell
{
public:
    shell();
    shell(std::string&&);
    shell(const std::string& );
    ~shell();

    void run();

private:
    void init_shell();
private:
    std::string user_name_;
};

#endif // !_SHELL_H_
