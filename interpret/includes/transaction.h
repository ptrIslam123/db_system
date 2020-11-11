#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include "command.h"
#include "operators.h"

class transaction : public command
{
public:
    transaction();
    ~transaction();
    virtual void execute() override;
    virtual bool is_it_commat() const override;

private:
    lexeme_ptr   get(size_t ) const;
    void         next(size_t );
    bool         is_end_transact_block() const;
    void         close_transact_contecste() const;

private:
    operators oprt_;
};

#endif // !_TRANSACTION_H_
