#ifndef _LEXEME_H_
#define _LEXEME_H_

#include <string>
#include "lexeme_type.h"

struct lexeme;
using lexeme_v           = std::string;
using lexeme_t           = LEXEME_TYPE;
using lexeme_t_ptr       = lexeme_t*;
using lexeme_v_ptr       = lexeme_v*;
using lexeme_ptr         = lexeme*;

struct lexeme
{
public:
    lexeme(lexeme_v&& , lexeme_t&& );
    ~lexeme();
    
    const lexeme_v&     get_value();
    const lexeme_t&     get_type();
    const lexeme_t_ptr  get_ptr_type();
    const lexeme_v_ptr  get_ptr_value();

private:
    lexeme_v value_;
    lexeme_t type_;
};

#endif // !_LEXEME_H_
