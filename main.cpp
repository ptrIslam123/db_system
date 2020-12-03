#include <iostream>
#include "interpret/includes/shell.h"

std::string path = "../hello.txt";

int main()
{

    shell sh(std::move(path));

    sh.run();    


    return 0;
}