#include "includes/operators.h"
#include "includes/args_data.h"
#include "includes/sys_functions.h"
#include "includes/base_parse_api.h"

/* API DB */
operators::operators():
    optr_table_{
        {"get",     __get_operator},
        {"insert",  __insert_operator},
        {"update",  __update_operator},
        {"remove",  __remove_operator},
        {"create",  __create_table_operator},
        {"drop",    __drop_table_operator},
        {"set",     __set_table_operator}
    }
{}

operators::~operators()
{}

bool operators::is_it_commat() const
{
    return true;
}

void operators::execute()
{
    auto oprt_p = parse_oprt();
    auto oprt = oprt_p.first;
    auto args = oprt_p.second;
    oprt(std::move(args));
}

oprt_t operators::parse_oprt()
{
    auto oprt_name = get(0);
    auto oprt = optr_table_.find(oprt_name->get_value());
    if (oprt == optr_table_.cend())
    {
        throw "undefine operator";
    }
    next(1);
    auto cur_lex = get(0);
    //is_eq_token(cur_lex->get_type(), LEXEME_TYPE::L_BRACKET, "udefine token" + cur_lex->get_value());
    next(1);        // (
    auto args_oprt_data = parse_args_oprt_data();
    next(1);        // )
    return oprt_t(oprt->second, std::move(args_oprt_data));
}

args_oprt_buf_t operators::parse_args_oprt_data()
{
    args_oprt_buf_t buffer;
    while (is_has_args_oprt())
    {
        buffer.push_back(
            make_args_oprt()
        );
    }
    return std::move(buffer);
}

args_oprt_t operators::make_args_oprt()
{
    auto args_t_ = get(0);
    auto args_d_ = get(3);
    auto cur_lex = get(2);
    //is_eq_token(cur_lex->get_type(), LEXEME_TYPE::TWO_POINT, "undefine token: " + cur_lex->get_value());
    next(3);
    return args_oprt_t(args_t_, args_d_);
}

bool operators::is_has_args_oprt() const
{
    return ( get(0)->get_type() == LEXEME_TYPE::R_BRACKET ); 
    //return !(get(0)->get_type() == LEXEME_TYPE::R_BRACKET);
}

lexeme_ptr operators::get(size_t ) const
{
    return nullptr;
}

void operators::next(size_t )
{

}


/* REAUESTES */

static
data_ptr get_data_ptr()
{
    return nullptr;
}

static
void init_data(data_ptr data, args_oprt_buf_t&& args)
{
    auto size = args.size();
    if (size % 2 != 0)
    {
        throw "";
    }
    auto i = 0;
    while (true)
    {
        if (i >= size)
            break;
        auto args_type = (args.at(i).first)->get_value();
        if (args_type == "dt")
        {
            data->set_args_type(_DATE_);
            auto date_ptr = (args.at(i).second)->get_ptr_value();
            data->set_date_ptr(date_ptr);
            i+=2;
            continue;
        }
        if (args_type == "ti")
        {
            data->set_args_type(_TIME_);
            auto time_ptr = (args.at(i).second)->get_ptr_value();
            data->set_time_ptr(time_ptr);
            i+=2;
            continue;
        }
        if (args_type == "ds")
        {
            data->set_args_type(_DESCRIPT_);
            auto descr_ptr = (args.at(i).second)->get_ptr_value();
            data->set_descript_ptr(descr_ptr);
            i+=2;
            continue;
        }
        else
        {
            throw "undefine token";
        }
    }
}

void __get_operator(args_oprt_buf_t&& args)
{
    auto data = get_data_ptr();
    try
    {
        init_data(data, std::move(args));   
    }
    catch(const std::out_of_range& e)
    {
        //std::cerr << e.what() << '\n';
    }
    auto type = data->get_args_type();
    
    switch (type)
    {
        case _DATE_ : {
            for_each_select(comparator_dt, get_req, data);
            break;
        }
        case _TIME_ : {
            for_each_select(comparator_ti, get_req, data);
            break;
        }
        case _DESCRIPT_ : {
            for_each_select(comparator_ds, get_req, data);
            break;
        }
        case _DATE_TIME_ : {
            for_each_select(comparator_dt_ti, get_req, data);
            break;
        }
        case _DATE_DESCRIPT : {
            for_each_select(comparator_dt_ds, get_req, data);
            break;
        }
        case _TIME_DESCRIPT_ : {
            for_each_select(comparator_ti_ds, get_req, data);
            break;
        }
        case _DATE_TIME_DESCRIPT_ : {
            for_each_select(comparator_dt_ti_ds, get_req, data);
            break;
        }
        default:
            throw "undefine param type";
    }
}

void __insert_operator(args_oprt_buf_t&& args)
{

}

void __update_operator(args_oprt_buf_t&& args)
{

}

void __remove_operator(args_oprt_buf_t&& args)
{
    
}

void __create_table_operator(args_oprt_buf_t&& args)
{

}

void __drop_table_operator(args_oprt_buf_t&& args)
{

}

void __set_table_operator(args_oprt_buf_t&& args)
{

}

