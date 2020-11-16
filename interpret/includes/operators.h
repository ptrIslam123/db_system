#ifndef _OPERATORS_H_
#define _OPERATORS_H_

#include <string>
#include <map>

#include "args_data_operator.h"
#include "args_data.h"
#include "command.h"

class operators : public command
{
    using oprt_table_t = std::map<oprt_name_t, oprt_type>;
public:
    operators(base_parse_api_ptr );
    virtual ~operators();
    virtual void    execute() override;
    virtual bool    is_it_commat() const override; 

private:
    args_oprt_t     make_args_oprt();
    bool            is_has_args_oprt() const;
    lexeme_ptr      get(size_t ) const;
    void            next(size_t );
    void            is_eq_lex(const LEXEME_TYPE& , 
                              const LEXEME_TYPE& , 
                              std::string&&     );
private:
    oprt_table_t    optr_table_;
};

/* REAUESTES */

void  __get_operator(args_oprt_buf_t&& );
void  __add_operator(args_oprt_buf_t&& );
void  __insert_operator(args_oprt_buf_t&& );
void  __update_operator(args_oprt_buf_t&& );
void  __remove_operator(args_oprt_buf_t&& );
void  __create_table_operator(args_oprt_buf_t&& );
void  __drop_table_operator(args_oprt_buf_t&& );
void  __set_table_operator(args_oprt_buf_t&& );
void  __print_table__operator(args_oprt_buf_t&& );
void  __print_operator(args_oprt_buf_t&& );
void  __count_operator(args_oprt_buf_t&& );
void  __clear_operator(args_oprt_buf_t&& );

static void     init_data(data_ptr , args_oprt_buf_t&& );
static data_ptr get_data_ptr();


#endif // !_OPERATORS_H_
