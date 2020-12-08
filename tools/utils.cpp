#include "includes/utils.h"


void printRed(const std::string& msg)
{
    auto m = msg.c_str();
    printf("\033[31m%s\033[0m\n", m);
}

void printBlue(const std::string& msg)
{
    auto m = msg.c_str();
    printf("\033[34m%s\033[0m\n", m);
}

size_t cast_str_i(std::string&& str)
{
    return std::stoi(std::move(str));
}

string_t cast_i_str(int_t val)
{
    return std::to_string(val);
}