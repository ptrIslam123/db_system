#ifndef _BASE_PARSE_API_H_
#define _BASE_PARSE_API_H_
//#define _SINGLETON_BASE_PARSE_API_

#include "../../tools/includes/singleton.h"
#include "lexer.h"

class base_parse_api;
using base_parse_api_ptr    = base_parse_api*;


class base_parse_api
{
    using container_t           = std_container_type;
    using container_ptr         = container_t*;
public:
    base_parse_api();
    base_parse_api(container_ptr );
    ~base_parse_api();

    void        set_pos(size_t );
    lexem_ptr   get_lexeme(size_t ) const;
    lexeme_uptr get_lexeme_uptr(size_t pos);
    void        next_lexeme(size_t );
    void        is_eq_lexeme(const LEXEME_TYPE& ,
                             const LEXEME_TYPE& , std::string&& ) const;

    bool        is_end() const;
    size_t      get_size() const;
    size_t      get_pos() const;

private:

    container_ptr   container_;
    size_t          size_;
    size_t          pos_;
    
};


#endif // !_BASE_PARSE_API_H_
