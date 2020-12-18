#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main()
{
   
    std::map<std::string, int> m = 
        {{"ivan", 10}, {"ivar", 20}, {"jon", 30}};

    auto m_p = &m;

    for (auto &i : *m_p)
    {
        std::cout << i.second << "\n";
        std::cout << i.first << "\n";
    }

    return 0;
}

