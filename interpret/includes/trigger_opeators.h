#ifndef _TRIGGER_OPERATORS_H_
#define _TRIGGER_OPERATORS_H_

#include <vector>

#include "lexeme.h"
#include "operators.h"
#include "operators.h"
#include "command.h"

class trigger_operators;
using trigger_uptr          = std::unique_ptr<trigger_operators>;
using trigger_ptr           = trigger_operators*;

class trigger_operators : public command
{
    using lexeme_type       =  lexeme_uptr;
    using container_t       = std::vector<lexeme_type>;
public:
            trigger_operators(base_parse_api_ptr );
    virtual ~trigger_operators();

    virtual void execute() override;
    virtual bool is_it_commat() const override;

private:
    lexeme_uptr     move_lexeme();
    bool            is_has_args_oprt() const;
    lexeme_ptr      get(size_t ) const;
    void            next(size_t );
    void            is_eq_lex(const LEXEME_TYPE& , 
                              const LEXEME_TYPE& , 
                              std::string&&     );

private:
    container_t poll_cmd_;
};

#endif // !_TRIGGER_OPERATORS_H_
