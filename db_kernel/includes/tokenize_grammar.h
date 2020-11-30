#ifndef _TOKENIZE_GRAMMAR_H_
#define _TOKENIZE_GRAMMAR_H_
//#define _ENABLE_DB_CONTROLLER_OPRTIONS_
#include <memory>
#include <iostream>

#ifndef _ENABLE_DB_CONTROLLER_OPRTIONS_
#include "file_stream.h"
#endif // !_ENABLE_DB_CONTROLLER_OPRTIONS_
#include "token.h"

#ifndef _ENABLE_DB_CONTROLLER_OPRTIONS_
using fstream_t     = std::unique_ptr<file_stream>;
using fstream_ptr   = file_stream*;
using token_t       = std::unique_ptr<token>;
using token_ptr     = token*;
#endif // !_ENABLE_DB_CONTROLLER_OPRTIONS_


class tokenize_grammar
{
public:
    tokenize_grammar(fstream_t&& );
    ~tokenize_grammar();

    token_t       tokenize();
    word_t        tokenize_word();
    word_t        tokenize_data();
    time_t_       tokenize_time();
    date_t_       tokenize_date();
    type_t_       tokenize_type();
    descript_t_   tokenize_description();
    word_t        tokenize_heder();
    token_t       make_token
    (date_t_&&, time_t_&&, type_t_, descript_t_&& );

    char        get() const;
    void        seek(int ) const;
    bool        is_eof() const;
    bool        is_open_file() const;
    void        skip_nul_scpace();
    word_t      get_file() const;
    word_ptr    get_file_ptr();
    fstream_t   get_fsretam();

private:
    fstream_t fstream_;
};

descript_t_   make_description(const word_t& );


#endif // !_TOKENIZE_GRAMMAR_H_
