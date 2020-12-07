#include "includes/lexer.h"
#include "includes/sys_error.h"


lexer::lexer():
    size_code_(0),
    pos_(0)
{}



lexer::lexer(code_t&& code, size_t beg_cont_size):
    code_(std::move(code)),
    size_code_(code_.size()),
    pos_(0)
{}



lexer::~lexer() {}



void lexer::set_code(const std::string& code)
{
    code_ = code;
    size_code_ = code_.size();
}



void lexer::set_code(std::string&& code)
{
    code_ = std::move(code);
    size_code_ = code_.size();
}



void lexer::run()
{
    char cur_s;
    while (true)
    {
        cur_s = get(0);
        if (is_end(cur_s))
        {
            break;
        }
        else if (is_commnet(cur_s))
        {
            tokenize_comment();
            continue;
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


void lexer::push_back(lexeme_uptr&& val)
{
    container_.push_back(
        std::move(val)
    );
}


void lexer::tokenize_comment()
{
    char cur_s;
    while (true)
    {
        cur_s = get(0);
        if (cur_s == '\n' || cur_s == '\0')
        {
            next(1);
            break;
        }
        next(1);
    }
}

lexeme_uptr lexer::tokenize_data()
{
    word_t buffer;
    char cur_s;
    while (true)
    {
        cur_s = get(0);
        if (cur_s == '\0')
        {
            throw sys_error(error_type::UNDEFINE_TOKEN ,
                            "lexer::tokenize_data : undefine token \"\'\"");
        }
        if (cur_s == '\'')
        {
            break;
        }
        buffer += cur_s;
        next(1);
    }
    return make_lexeme(std::move(buffer), lexeme_t::DATA);
}




lexeme_uptr lexer::tokenize_operator(char oprt)
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




lexeme_uptr lexer::tokenize_word()
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

    if (buffer == "trigger")
    {
        return make_lexeme(std::move(buffer), lexeme_t::TRIGGER);
    }
    
    return make_lexeme(std::move(buffer), lexeme_t::WORD);
}



std::string lexer::to_string(char s)
{
    std::string str;
    str += s;
    return str;     // return std::move(str);   // -Wall 
}


lexer::container_t lexer::get_result()
{
    return std::move(container_);
}


lexeme_uptr lexer::make_lexeme(lexeme_v&& value,lexeme_t&& type)
{
    //log
    return std::make_unique<lexeme>(
        std::move(value),
        std::move(type)
    );
}


void lexer::error_lexeme(char s)
{
    auto errmsg = "lexer::tokenize : undefine token => ";
    errmsg += s;
    
    throw sys_error(error_type::UNDEFINE_TOKEN,
                    std::move(errmsg));
}


void lexer::skip_null_space()
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


char lexer::get(size_t rel_pos)
{
   size_t position = pos_ + rel_pos;
   if (position < 0 || position > size_code_)
        return '\0';
   return code_[position];
}


void lexer::next(size_t offset)
{
   pos_ += offset;
}


bool lexer::is_commnet(char s) const
{
    return s == '#';
}

bool lexer::is_word(char s) const
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


bool lexer::is_oprt(char s) const
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


bool lexer::is_data(char s) const
{
    return s == '\'';
}


bool lexer::is_end(char s) const
{
    if (s == '\0')
        return true;
    return false;
}