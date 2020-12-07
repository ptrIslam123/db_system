#ifndef _LOGER_H_
#define _LOGER_H_
#define _B_BUF_SIZE_ 4096
#define _SIZE_DATE_TIME_T   30
#define _SIZE_ERR_TYPE_T_   30
#define _SIZE_DESCRIPT_T_   30
#define _STD_LOGER_FILE_PATH_ "../config/log/error_log.txt"

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

struct loger
{
    using buffer_t          = std::array<char, _B_BUF_SIZE_>;
public:
    loger(file_name_t&& );
    loger(const file_name_t& );
    ~loger();

    void log(str_t&& ,str_t&& );
    void print_log();
    void flush();
    
private:
    void write(data_t&& );
    void file_open();
    str_t get_date_time();

private:
    
    file_name_t     fname_;
    buf_size_t      size_;
    buf_size_t      capacity_;
    std::fstream    fstream_;
    buffer_t        buffer_;
};


} // namespace log

log::loger& get_loger();


#endif // !_LOGER_H_
