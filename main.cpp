#include <iostream>
#include <fstream>
#include "interpret/includes/shell.h"
#include "interpret/test/t_lexer.h"

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

    return 0;
}