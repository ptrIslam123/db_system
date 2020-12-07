#include "includes/files.h"

files::files()
{}

files::files(std::string&& fname):
    fname_(std::move(fname)),
    file_(fname_)
{
    if (!is_open())
    {
        throw "file not found: " + fname_;
    }
}

files::files(const std::string& fname):
    fname_(fname),
    file_(fname_)
{
    if (!is_open())
    {
        throw "file not found: " + fname_;
    }
}


files::~files()
{
    file_.close();
}




bool files::is_open() const
{
    return file_.is_open();
}


void files::write(std::string&& data)
{
    file_ << std::move(data);
}

void files::write(const std::string& data)
{
    file_ << data;
}

std::string files::read()
{
    std::string buffer;
    char s = 0;
    while (file_.get(s))
    {
        buffer += s;
    }
    return buffer;   // -Wall return std::move(buffer);
}