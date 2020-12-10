#include <iostream>
#include <fstream>
#include <string>

std::string path = "../../config/tables/";
std::string fname1 = path + "file1.txt";
std::string fname2 = path + "file2.txt";

std::string readf(const std::string& fname);

int main()
{
   auto str1 = readf(fname1);
   auto str2 = readf(fname2);

   std::cout << "str1[\n" << str1 << "\n]\n\n";
   std::cout << "str2[\n " << str2 << "\n]\n";

   if (str1 == str2)
   {
       std::cout << "True\n";
   }
   else
   {
       std::cout << "False\n";
   }
   

    return 0;
}

std::string readf(const std::string& fname)
{
    std::fstream file(fname);
    if (!file.is_open())
    {
        std::cout << "file not found\n";
        exit(-1);
    }
    std::string buffer;
    while (true)
    {
        char s = file.get();
        if (file.eof())
            break;
        buffer += s;
    }
    return buffer;
}