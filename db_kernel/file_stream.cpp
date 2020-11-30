#include "includes/file_stream.h"
#include "includes/methods.h"
//#define _MALLOC_DEB_INF_F_ 

file_stream::file_stream(std::string&& file_name)
{
    file_name_ = std::move(file_name);
    file.open(file_name_);

#ifndef _MALLOC_DEB_INF_F_
    malloc_deb_inf("file_stream()\n");
#endif // _MALLOC_DEB_INF_F_
}


file_stream::~file_stream()
{
    file.close();
    
#ifndef _MALLOC_DEB_INF_F_
    malloc_deb_inf("~file_stream()\n");
#endif // _MALLOC_DEB_INF_F_
}

void file_stream::open(std::string&& file_name)
{
    file_name_ = std::move(file_name);
    file.open(file_name_);
}

void file_stream::open()
{
    file.open(file_name_);
}

bool file_stream::is_open()
{
    return file.is_open();
}

bool file_stream::is_eof()
{
    return file.eof();
}

char file_stream::getchar()
{
    return file.get();
}

void file_stream::seekchar(int offset)
{
    file.seekg(offset, std::ios::cur);
}


word_t file_stream::get_file() const
{
    return file_name_;
}

word_ptr file_stream::get_file_ptr()
{
    return &file_name_;
}
