#ifndef _LEXER_H_
#define _LEXER_H_

#include <string>
#include <iostream>
#include <memory>
#include <vector>

#include "lexeme.h"

using lexeme_uptr   = std::unique_ptr<lexeme>;
using lexem_ptr     = lexeme*;
using code_t        = std::string;
using word_t        = std::string;
using operator_t    = char;
using std_container_type = std::vector<lexeme_uptr>;

class lexer
{
    using container_t = std_container_type;
public:
    lexer();
    lexer(code_t&& ,size_t );
    ~lexer();
    
    void        set_code(const std::string& );
    void        set_code(std::string&& );
    void        run();
    container_t get_result();

private:
    lexeme_uptr    tokenize_operator(char );
    lexeme_uptr    tokenize_word();
    lexeme_uptr    tokenize_data();
    void           tokenize_comment();
    lexeme_uptr    make_lexeme(lexeme_v&& ,lexeme_t&& );
    void           push_back(lexeme_uptr&& );
    void           skip_null_space();

    std::string    to_string(char );
    bool           is_word(char ) const;
    bool           is_data(char ) const;
    bool           is_end(char ) const;
    bool           is_commnet(char ) const;
    bool           is_oprt(char ) const;
    void           error_lexeme(char );

    char           get(size_t );
    void           next(size_t ); 

private:

    code_t      code_;
    size_t      size_code_;
    size_t      pos_;
    container_t container_;
};


#endif // !_LEXER_H_
