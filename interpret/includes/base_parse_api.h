#ifndef _BASE_PARSE_API_H_
#define _BASE_PARSE_API_H_
//#define _SINGLETON_BASE_PARSE_API_

#ifndef _SINGLETON_BASE_PARSE_API_
#include "../../tools/includes/singleton.h"

class base_parse_api;
using base_parse_api_t = singleton_classic<base_parse_api>;

#define ACCESS_B_AIP(CONTAINER)                                 \
                        base_parse_api_t::instance(CONTAINER)   \

#endif // !_SINGLETON_BASE_PARSE_API_

#include "lexer.h"
using base_parse_api_ptr = base_parse_api*;

class base_parse_api
{
    using conatiner_t  = std_container_type;
public:
    base_parse_api();
    base_parse_api(conatiner_t&& );
    ~base_parse_api();

    lexem_ptr   get_lexeme(size_t ) const;
    lexeme_uptr get_lexeme_uptr(size_t pos);
    void        next_lexeme(size_t );
    void        is_eq_lexeme(const LEXEME_TYPE& ,
                             const LEXEME_TYPE& , std::string&& ) const;
    
    void        set_container(conatiner_t&& );
    bool        is_end() const;
    size_t      get_size() const;
    size_t      get_pos() const;

private:
    conatiner_t container_;
    size_t      pos_;
    size_t      size_;
};


#endif // !_BASE_PARSE_API_H_
