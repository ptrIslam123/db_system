#ifndef _OPTION_PARSE_H_
#define _OPTION_PARSE_H_
#define _B_BUF_SIZE_OPTION_ 10

#include "args_data.h"
#include "args_data_operator.h" 

constexpr auto BEFORE_OP   = "BEFORE";
constexpr auto AFTER_OP    = "AFTER";
constexpr auto ADD_OP      = "ADD";
constexpr auto INSERT_OP   = "INSERT";
constexpr auto REMOVE_OP   = "REMOVE";

class option_parse
{
public:
    option_parse();
    ~option_parse();

    void            parse(data_ptr, lexeme_v_ptr );

private:
    void            set_option(data_ptr , word_ptr );
    char            get(size_t );
    void            next(size_t );
    bool            is_end() const;

private:
    word_t          buffer_;
    lexeme_v_ptr    value_;
    size_t          size_;
    size_t          pos_;
};

#endif // !_OPTION_PARSE_H_
