#ifndef _PARSER_H_
#define _PARSER_H_
#define SIZE_SET_COMMAND 2

#include <array>
#include <memory>
#include "command.h"

class parser 
{
    using command_t     = command;
    using command_ptr   = command_t*;
    using commands_t    = std::array<command_ptr, SIZE_SET_COMMAND>;
public:
    parser();
    ~parser();
    void run();

private:
     command_ptr find_cmd() const;
     template<typename T, typename ... Args>
     command_ptr make_command(Args&& ... args);

private:
    commands_t cmds_;
};


template<typename T, typename ... Args>
parser::command_ptr parser::make_command(Args&& ... args)
{
    static T t(std::forward<Args>(args) ... );
    return &t;
}

#endif // !_PARSER_H_
