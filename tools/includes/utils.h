#ifndef _TOOLS_UTILS_H_
#define _TOOLS_UTILS_H_ 

#include <string>
#include <iostream>

using string_t      = std::string;
using int_t         = int;

void        printRed(const std::string& );
void        printBlue(const std::string& );
size_t      cast_str_i(std::string&& );
string_t    cast_i_str(int_t );


#endif // !_TOOLS_UTILS_H_