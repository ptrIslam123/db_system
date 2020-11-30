#include <iostream>
#include "includes/files.h"
#include "includes/loger.h"
#include <fstream>

using loger_t = log::loger<>;

static loger_t& get_loger()
{
    static loger_t log("../data.txt");
    return log;
}

int main()
{

   loger_t log("../data.txt");
   for (int i =0 ;i < 5; i++)
   {
       log.log("undefine token", "null");
   }

    files file("../data.txt");
    std::cout << file.read() << "\n";

    return 0;
}