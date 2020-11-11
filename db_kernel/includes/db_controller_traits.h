#ifndef _DB_CONTROLLER_TRAITS_H_
#define _DB_CONTROLLER_TRAITS_H_
#define _STD_INCLUDE_DB_

#ifdef _STD_INCLUDE_DB_
#include <vector>
#include <memory>

#include "token.h"
#include "tokenize_grammar.h"
#include "file_stream.h"
#endif // _STD_INCLUDE_DB_


using std_token_t       = std::unique_ptr<token>;
using std_file_stream_t = file_stream;
using std_tok_grammar_t = tokenize_grammar;
using std_container_t   = std::vector<token_t>;

template<typename F = std_file_stream_t,
         typename T = std_tok_grammar_t,
         typename C = std_container_t>
struct db_controller_traits
{
    using token_type        = std_token_t;
    using container_type    = C;
    using file_stream_type  = F;
    using tok_grammar_type  = T;
}; 


#endif // !_DB_CONTROLLER_TRAITS_H_
