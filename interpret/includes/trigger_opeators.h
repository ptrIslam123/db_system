#ifndef _TRIGGER_OPERATORS_H_
#define _TRIGGER_OPERATORS_H_
#define _STD_TRIGG_BLOCK_SIZE_ 50
#include <vector>

#include "lexeme.h"
#include "operators.h"
#include "operators.h"
#include "command.h"

class trigger_operators;
using trigger_name_t    = word_t;
using trigger_name_ptr  = word_ptr; 
using lexeme_type       = lexeme_uptr;
using trigger_block_t   = std::vector<lexeme_type>;
using trigger_block_ptr = trigger_block_t*;

class trigger_operators : public command
{
    using container_t = trigger_block_t;
public:
            trigger_operators(base_parse_api_ptr );
    virtual ~trigger_operators();

    virtual void execute() override;
    virtual bool is_it_command() const override;

private:
    lexeme_uptr     move_lexeme();
    bool            is_has_args_oprt() const;
    lexeme_ptr      get(size_t ) const;
    void            next(size_t );
    void            is_eq_lex(const LEXEME_TYPE& , 
                              const LEXEME_TYPE& , 
                              std::string&&     );

};

#endif // !_TRIGGER_OPERATORS_H_
