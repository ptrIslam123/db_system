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

template<typename C = std_container_type>
class lexer
{
    using container_t = C;
public:
    lexer(code_t&& ,size_t );
    ~lexer();
    
    void        run();
    auto        get_result();

private:
    lexeme_uptr    tokenize_operator(char );
    lexeme_uptr    tokenize_word();
    lexeme_uptr    tokenize_data();
    lexeme_uptr    make_lexeme(lexeme_v&& ,lexeme_t&& );
    void           push_back(lexeme_uptr&& );
    void           skip_null_space();

    std::string    to_string(char );
    bool           is_word(char ) const;
    bool           is_data(char ) const;
    bool           is_end(char ) const;
    bool           is_oprt(char ) const;
    void           error_lexeme(char );

    char           get(size_t );
    void           next(size_t );
   

private:
    container_t container_;
    code_t      code_;
    size_t      pos_;
    size_t      size_code_;
};

template<typename C>
lexer<C>::lexer(code_t&& code, size_t beg_cont_size):
    code_(std::move(code)),
    size_code_(code_.size()),
    pos_(0)
{}


template<typename C>
lexer<C>::~lexer() {}


template<typename C>
void lexer<C>::run()
{
    char cur_s;
    while (true)
    {
        cur_s = get(0);
        if (is_end(cur_s))
        {
            break;
        }
        else if (is_data(cur_s))
        {
            next(1);
            push_back(tokenize_data());
            next(1);
            continue;    
        }
        if (is_word(cur_s))
        {
            push_back(tokenize_word());
            continue;
        }
        else if (is_oprt(cur_s))
        {
            push_back(tokenize_operator(cur_s));
            next(1);
            continue;
        }
        else if (isspace(cur_s))
        {
            next(1);
            continue;
        }
        else
        {
            error_lexeme(cur_s);
        }   
    }
}

template<typename C>
void lexer<C>::push_back(lexeme_uptr&& val)
{
    container_.push_back(
        std::move(val)
    );
}

template<typename C>
lexeme_uptr lexer<C>::tokenize_data()
{
    word_t buffer;
    char cur_s;
    while (true)
    {
        cur_s = get(0);
        if (cur_s == '\'')
        {
            break;
        }
        buffer += cur_s;
        next(1);
    }
    return make_lexeme(std::move(buffer), lexeme_t::DATA);
}



template<typename C>
lexeme_uptr lexer<C>::tokenize_operator(char oprt)
{
    switch (oprt)
    {
        case ':' : return make_lexeme(to_string(oprt), lexeme_t::TWO_POINT);
        case '<' : return make_lexeme(to_string(oprt), lexeme_t::LESS);
        case '=' : return make_lexeme(to_string(oprt), lexeme_t::EQ);
        case '{' : return make_lexeme(to_string(oprt), lexeme_t::L_SHAPE_BRACKET);
        case '}' : return make_lexeme(to_string(oprt), lexeme_t::R_SHAPE_BRACKET);
        case '(' : return make_lexeme(to_string(oprt), lexeme_t::L_BRACKET);
        case ')' : return make_lexeme(to_string(oprt), lexeme_t::R_BRACKET);
        default:
            error_lexeme(oprt);
            return make_lexeme("", lexeme_t::VOID);
   }  
}



template<typename C>
lexeme_uptr lexer<C>::tokenize_word()
{
    word_t buffer;
    char cur_s;
    while (true)
    {
        cur_s = get(0);
        if (is_end(cur_s))
        {
            break;
        }
        else if (is_word(cur_s) || isdigit(cur_s))
        {
            buffer += cur_s;
            next(1);
            continue;
        }
        else
        {
            break;
        }
    }
    return make_lexeme(std::move(buffer), lexeme_t::WORD);
}


template<typename C>
std::string lexer<C>::to_string(char s)
{
    std::string str;
    str += s;
    return std::move(str);
}

template<typename C>
auto lexer<C>::get_result()
{
    return std::move(container_);
}

template<typename C>
lexeme_uptr lexer<C>::make_lexeme(lexeme_v&& value,lexeme_t&& type)
{
    //log
    return std::make_unique<lexeme>(
        std::move(value),
        std::move(type)
    );
}

template<typename C>
void lexer<C>::error_lexeme(char s)
{
    //log
    throw "#lexer#: undefine token";
}

template<typename C>
void lexer<C>::skip_null_space()
{
    while (true)
    {
        if (!isspace(get(0)))
        {
            break;
        }
        else
        {
            next(1);
        } 
    }
}

template<typename C>
char lexer<C>::get(size_t rel_pos)
{
   size_t position = pos_ + rel_pos;
   if (position < 0 || position > size_code_)
    return '\0';
   return code_[position];
}

template<typename C>
void lexer<C>::next(size_t offset)
{
   pos_ += offset;
}


template<typename C>
bool lexer<C>::is_word(char s) const
{
    if (isalpha(s))
    {
        return true;
    }
    else if (s == '_')
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename C>
bool lexer<C>::is_oprt(char s) const
{
   switch (s)
   {
    case ':' : return true;
    case '<' : return true;
    case '|' : return true;
    case '=' : return true;
    case '{' : return true;
    case '}' : return true;
    case ')' : return true;
    case '(' : return true;
    default:
        return false;
   }
}

template<typename C>
bool lexer<C>::is_data(char s) const
{
    return s == '\'';
}

template<typename C>
bool lexer<C>::is_end(char s) const
{
    if (s == '\0')
        return true;
    return false;
}
#endif // !_LEXER_H_
