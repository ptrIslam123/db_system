#include "includes/parser.h"
#include "includes/operators.h"
#include "includes/transaction.h"
#include "includes/trigger_opeators.h"

parser::parser()
{}

parser::parser(parser::base_p_api_ptr base_p_api)
{
  base_p_api_ = base_p_api;

/* it is bad code !!! */
  cmds_[0] = new operators(base_p_api);
  cmds_[1] = new transaction (base_p_api);
  cmds_[2] = new trigger_operators(base_p_api);
}

parser::~parser()
{}

 void parser::set_base_parse_api(base_parse_api_ptr base_p_api)
 {
   base_p_api_ = base_p_api;
 }


void parser::run()
{
  auto cmd = find_cmd();
  if (cmd != nullptr)
  {
      cmd->execute();
  }
  else
  {
      throw "undeine commnd";
  }
}

parser::command_ptr parser::find_cmd() const
{
    command_ptr cmd = nullptr;
    for (size_t i = 0; i < SIZE_SET_COMMAND; ++i)
    {
       cmd = cmds_.at(i);
       if (cmd->is_it_command())
       {
           return cmd;
       }
    }
    return cmd;
}