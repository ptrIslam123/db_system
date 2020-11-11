#include "includes/parser.h"
#include "includes/operators.h"
#include "includes/transaction.h"


parser::parser()
{
  cmds_[0] = make_command<operators>();
  cmds_[1] = make_command<transaction>();
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
      throw "undeine commnd";
  }
}

parser::command_ptr parser::find_cmd() const
{
    command_ptr cmd = nullptr;
    for (size_t i = 0; i < SIZE_SET_COMMAND; ++i)
    {
       cmd = cmds_.at(i);
       if (cmd->is_it_commat())
       {
           return cmd;
       }
    }
    return cmd;
}