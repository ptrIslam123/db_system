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
    using commands_t            = std::array<command_ptr, SIZE_SET_COMMAND>;
    using cmd_uptr              = command*;
public:
    parser();
    parser(base_p_api_ptr );
    ~parser();
    void run();
    void set_base_parse_api(base_parse_api_ptr );

private:
     command_ptr find_cmd() const;
     template<typename T, typename ... Args>
     command_ptr make_command(base_parse_api_ptr , Args&& ... args);

private:
    commands_t      cmds_;
    base_p_api_ptr  base_p_api_;
    cmd_uptr        oprts_;
    cmd_uptr        transact_;
    cmd_uptr        trigg_oprts_;
};

#endif // !_PARSER_H_
