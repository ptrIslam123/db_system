#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_


#include "operators.h"
#include "atomic_operators.h"
#include "command.h"

class transaction : public command
{
public:
    transaction(base_parse_api_ptr );
    virtual ~transaction();
    virtual void execute() override;
    virtual bool is_it_command() const override;

private:
    bool         is_end_transact_block() const;
    void         close_transact_contecste();
    lexeme_ptr   get(size_t ) const;
    void         next(size_t );

private:
    atomic_operators oprt_;
};

#endif // !_TRANSACTION_H_
