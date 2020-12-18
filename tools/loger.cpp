#include "includes/loger.h"
#include "includes/files.h"
#include "../interpret/includes/sys_error.h"

#include <iostream>

log::loger& get_loger()
{
    static log::loger log(_STD_LOGER_FILE_PATH_);
    return log;
}

namespace log
{


loger::loger(file_name_t&& fname)
{
    fname_ = std::move(fname);
    capacity_ = buffer_.size();
    size_ = 0;
    fstream_.open(fname_,   std::ios::in |
                            std::ios::out|
                            std::ios::app|
                            std::ios::binary);
    file_open();
}


loger::loger(const file_name_t& fname)
{
    fname_ = fname;
    capacity_ = buffer_.size();
    size_ = 0;
    fstream_.open(fname_,   std::ios::in |
                            std::ios::out|
                            std::ios::app|
                            std::ios::binary);
    file_open();
}



loger::~loger()
{
    flush();
    fstream_.close();
}



void loger::log(str_t&& type_err, str_t&& descript)
{
    auto date_time = get_date_time();
    date_time.erase(date_time.size() - 1);

    str_t log_format =   "[" +  date_time   + "] : [" + 
                                type_err    + "] : [" + 
                                descript    + "]\n";
    
    //const auto size_data = log_format.size(); // -Wall : unused 
    write(std::move(log_format));
}


void loger::print_log()
{
   char* data                   = nullptr;
   const auto size_block_data   = sizeof(char)*size_;

   while (true)
   {
       fstream_.read(data, size_block_data);
       std::cout << (*data) << "\n";
   }
}




void loger::write(data_t&& data)
{
    const auto size_data = data.size();
    for (size_t i = 0; i < size_data; ++i, ++size_)
    {
        if (size_ >= capacity_)
        {
            flush();
            size_ = 0;
        }
        buffer_.at(size_) = data[i];
    }
}


void loger::flush()
{
   auto data                    = buffer_.data();
   const auto size_block_data   = sizeof(char)*size_;
   fstream_.write(data, size_block_data);
}



inline
void loger::file_open()
{
    if (!fstream_.is_open())
    {
        throw sys_error(error_type::FILE_NOT_FOUND,
                        "loger: file not found:=> " + fname_);
    }
}


str_t loger::get_date_time()
{
    auto cur_time = std::chrono::system_clock::now();
    auto cur_time_t = std::chrono::system_clock::to_time_t(cur_time);
    auto str_time = std::move(std::ctime(&cur_time_t));
    return std::move(str_time);
}

} // namespace log


