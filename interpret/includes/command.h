#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "base_parse_api.h"

class command
{
public:
    command(base_parse_api_ptr );
    virtual ~command();

    virtual void execute() = 0;
    virtual bool is_it_command() const;

protected:
    bool        is_end() const;
    lexeme_ptr  get_lexeme(size_t ) const;
    lexeme_uptr get_lexeme_uptr(size_t pos);
    void        next_lexeme(size_t );

private:
    base_parse_api_ptr base_p_api_;
};

#endif // !_COMMAND_H_
