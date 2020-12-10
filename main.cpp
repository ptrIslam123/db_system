#include <iostream>
#include <fstream>
#include "interpret/includes/shell.h"
#include "interpret/test/t_lexer.h"
#include "interpret/includes/sys_error.h"

#define DEBUG

int main(int argc, char **argv)
{
#ifdef DEBUG
     if (argc > 2)
    {
        exit(-1);
    }
    else if (argc == 2)
    {
        auto fname = *(argv + 1);
        shell sh(fname);
        sh.run();
    }
#endif // DEBUG

    
    /*
    exec("create_t(tn : 'table' fn : '../config/tables/big_init.txt' sz : '25000')");
    exec("set_t(tn : 'table')");
    exec("get(ds : 'Просмотр камеры \"132.Общ. №10-Центральный вход\" пользователем \"Оператор\"/\"Murat\" с IP-адреса \"192.168.1.69\"')");
    exec("count()");
    */
    
    return 0;
}