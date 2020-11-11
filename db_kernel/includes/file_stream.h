#ifndef _FILE_STREAM_H_
#define _FILE_STREAM_H_

#include <fstream>
#include <string>

class file_stream
{
public:
    file_stream(std::string&& );
    ~file_stream();

    std::string get_file() const;
    void        open(std::string&& );
    void        open();
    bool        is_open();
    bool        is_eof();

    char        getchar();
    void        seekchar(int );

private:
    std::string   file_name_;
    std::fstream  file;
};

#endif // !_FILE_STREAM_H_
