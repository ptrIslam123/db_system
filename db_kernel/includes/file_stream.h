#ifndef _FILE_STREAM_H_
#define _FILE_STREAM_H_

#include <fstream>
#include <string>

#include "token.h"

class file_stream
{
public:
    file_stream(std::string&& );
    ~file_stream();

    word_t      get_file() const;
    word_ptr    get_file_ptr();
    void        open(std::string&& );
    void        open();
    bool        is_open();
    bool        is_eof();

    char        getchar();
    void        seekchar(int );

private:
    word_t        file_name_;
    std::fstream  file;
};

#endif // !_FILE_STREAM_H_
