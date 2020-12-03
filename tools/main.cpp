#include <iostream>
#include <fstream>



struct node
{
    node():
        a_(0), b_(0)
    {};

    node(int a, int b):
        a_(a), b_(b)
        {}
    int a_;
    int b_;
};

void write(node n, const std::string& fname)
{
    auto size_node = sizeof(node);

    std::fstream file("../bindata.txt", std::ios::binary | std::ios::app);

    file.write((char*)&n, size_node);

    file.close();
}

void read()
{
    auto size_node = sizeof(node);

    std::fstream file("../bindata.txt", std::ios::binary);

    file.read();

    file.close();
}

int main()
{

    


    return 0;
}