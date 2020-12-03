#include "includes/parser.h"
#include "includes/operators.h"
#include "includes/transaction.h"
#include "includes/trigger_opeators.h"
#include "includes/sys_error.h"


parser::parser(parser::base_p_api_ptr base_p_api)
{
  base_p_api_ = base_p_api;

  cmds_[0] = std::make_unique<operators>(base_p_api);
  cmds_[1] = std::make_unique<transaction>(base_p_api);
  cmds_[2] = std::make_unique<trigger_operators>(base_p_api);
}

parser::~parser()
{}


void parser::run()
{
  auto cmd = find_cmd();
  if (cmd != nullptr)
  {
      cmd->execute();
  }
  else
  {
      throw sys_error(error_type::UNDEFINE_FUNCTION,
                      "parser::run : undefine function");
  }
}

parser::command_ptr parser::find_cmd() const
{
    command_ptr cmd = nullptr;
    for (size_t i = 0; i < SIZE_SET_COMMAND; ++i)
    {
       cmd = cmds_.at(i).get();
       if (cmd->is_it_command())
       {
           return cmd;
       }
    }
    return cmd;
}