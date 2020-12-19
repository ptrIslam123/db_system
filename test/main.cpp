#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main()
{

    using namespace std;
    
    auto fname = "../test.txt";

    std::fstream file(fname);
    char s = 0;
    std::string buffer;
    std::string type_;
    

    if (file.is_open())
    {
        while (true)
        {
            s = file.get();
            if (file.eof())
            {
                break;
            }

            if (isspace(s))
            {
                if (buffer == "Отладочная")
                {
                    buffer += '_';
                    buffer += file.get();
                    continue;
                }
                else if (buffer == "Тревожное")
                {
                    buffer += '_';
                    buffer += file.get();
                    continue;
                }
                else
                {
                    break;
                }
            }

            buffer += s;
        }

        std::cout << "[" << buffer << "]\n";
        
    }
    else 
    {
        std::cout << "file is not open\n";
    }
   
    return 0;
}

/*

    auto fname = "../test.txt";
    std::fstream file(fname);
    char s = 0, n_s = 0;
    std::string buffer;
    std::string type_;
    

    if (file.is_open())
    {
         while (true)
        {
            s = file.get();

            if (file.eof())
            {
                break;
            }
            

            buffer += s;
        }
        std::cout << "buffer = " << buffer << "\n";
        
    }
    else 
    {
        std::cout << "file is not open\n";
    }
   
 */
