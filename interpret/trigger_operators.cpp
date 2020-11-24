#include "includes/trigger_opeators.h"
#include "includes/list_triggers.h"

trigger_operators::trigger_operators(base_parse_api_ptr base_p_api):
    command(base_p_api)
{}

trigger_operators::~trigger_operators()
{}

bool trigger_operators::is_it_command() const
{
    return (get(0)->get_type() == LEXEME_TYPE::TRIGGER && 
            get(1)->get_type() == LEXEME_TYPE::WORD);
}

void trigger_operators::execute()
{
    container_t poll_cmd_;
    poll_cmd_.reserve(_STD_TRIGG_BLOCK_SIZE_);

    auto tname = get(1)->get_value();
    next(2);        // 'trigger' 'name'

    auto clex = get(0);
    is_eq_lex(clex->get_type(), LEXEME_TYPE::L_SHAPE_BRACKET, "indefine token : " + clex->get_value());
    next(1);        // '{'

    while (is_has_args_oprt())
    {
        poll_cmd_.push_back(
            move_lexeme()
        );
    }
    next(1);    // '}'  
    //poll_cmd_.push_back(move_lexeme());

    list_triggers_t::instance().add(std::move(tname), 
                                    std::move(poll_cmd_)); 
}

lexeme_uptr trigger_operators::move_lexeme()
{
    return get_lexeme_uptr(0);
}

bool trigger_operators::is_has_args_oprt() const
{
    return !( get(0)->get_type() == LEXEME_TYPE::R_SHAPE_BRACKET);
}

lexeme_ptr trigger_operators::get(size_t pos) const
{
    return get_lexeme(pos);
}

void trigger_operators::next(size_t offset)
{
    next_lexeme(offset);
}

void trigger_operators::is_eq_lex(const LEXEME_TYPE& ltype, 
                                  const LEXEME_TYPE& rtype, 
                                  std::string&&     emsg)
{
    if (ltype != rtype)
    {
        throw emsg;
    }
}