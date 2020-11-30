#ifndef _FILES_H_
#define _FILES_H_

#include <string>
#include <fstream>

struct files
{
public:
    files();
    files(std::string&&);
    files(const std::string& );
    files(files&& ) = delete;
    files(const files& ) = delete;
    ~files();

   

    void write(std::string&& );
    void write(const std::string& );

    std::string read();

private:
    bool is_open() const;

private:
    std::string fname_;
    std::fstream file_;
};

#endif // !_FILES_H_
