#ifndef _PARSER_H_
#define _PARSER_H_
#define SIZE_SET_COMMAND 3

#include <array>
#include <memory>
#include "command.h"

class parser 
{
    using base_p_api_ptr        = base_parse_api*;
    using command_t             = command;
    using command_ptr           = command_t*;
    using command_uptr          = std::unique_ptr<command_t>;
    using commands_t            = std::array<command_uptr, SIZE_SET_COMMAND>;
public:
    parser(base_p_api_ptr );
    ~parser();
    void run();

private:
     command_ptr find_cmd() const;
     template<typename T, typename ... Args>
     command_ptr make_command(base_parse_api_ptr , Args&& ... args);

private:
    commands_t      cmds_;
    base_p_api_ptr  base_p_api_;
};

#endif // !_PARSER_H_
