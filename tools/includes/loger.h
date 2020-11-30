#ifndef _LOGER_H_
#define _LOGER_H_
#define _B_BUF_SIZE_ 255
#define _SIZE_DATE_TIME_T   30
#define _SIZE_ERR_TYPE_T_   30
#define _SIZE_DESCRIPT_T_   30

#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <chrono>

namespace log
{

struct loger_node;

using str_t                 = std::string;
using buf_size_t            = size_t;
using file_name_t           = std::string;
using loger_node_t          = loger_node;
using data_t                = str_t;

template<buf_size_t size    = _B_BUF_SIZE_>
struct loger
{
    using buffer_t          = std::array<char, size>;
public:
    loger(file_name_t&& );
    loger(const file_name_t& );
    ~loger();

    void log(str_t&& ,str_t&& );
    void flush();
    
private:
    void write(data_t&& );
    void file_open();
    str_t get_date_time();

private:
    std::fstream    fstream_;
    file_name_t     fname_;
    buffer_t        buffer_;
    buf_size_t      size_;
    buf_size_t      capacity_;
};





template<buf_size_t size>
loger<size>::loger(file_name_t&& fname):
    fname_(std::move(fname)),
    capacity_(buffer_.size()),
    size_(0)
{
    fstream_.open(fname_,   std::ios::in |
                            std::ios::out|
                            std::ios::app|
                            std::ios::binary);
    file_open();
}

template<buf_size_t size>
loger<size>::loger(const file_name_t& fname):
    fname_(fname),
    capacity_(buffer_.size()),
    size_(0)
{
    fstream_.open(fname_,   std::ios::in |
                            std::ios::out|
                            std::ios::app|
                            std::ios::binary);
    file_open();
}


template<buf_size_t size>
loger<size>::~loger()
{
    flush();
    fstream_.close();
}


template<buf_size_t size>
void loger<size>::log(str_t&& type_err, str_t&& descript)
{
    auto date_time = get_date_time();
    str_t log_format =  "<DATE | TIME>   : " + date_time + 
                        "<TYPE_ERROR >   : " + type_err + "\n" +
                        "<DESCRIPTION>   : " + descript + "\n\n";
    
    const auto size_data = log_format.size();
    write(std::move(log_format));
}



template<buf_size_t size>
void loger<size>::write(data_t&& data)
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

template<buf_size_t size>
void loger<size>::flush()
{
   auto data = buffer_.data();
   const auto size_block_data = sizeof(char)*size_;
   fstream_.write(data, size_block_data);
}


template<buf_size_t size>
inline
void loger<size>::file_open()
{
    if (!fstream_.is_open())
    {
        throw std::runtime_error("loger: file not found:=> " + fname_);
    }
}

template<buf_size_t size>
str_t loger<size>::get_date_time()
{
    auto cur_time = std::chrono::system_clock::now();
    auto cur_time_t = std::chrono::system_clock::to_time_t(cur_time);
    auto str_time = std::move(std::ctime(&cur_time_t));
    return std::move(str_time);
}



} // namespace log





#endif // !_LOGER_H_
