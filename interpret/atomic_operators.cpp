#include "includes/atomic_operators.h"
#include "includes/args_data.h"
#include "includes/sys_functions.h"
#include "includes/base_parse_api.h"

atomic_operators::atomic_operators(base_parse_api_ptr base_p_api):
    command(base_p_api),
    optr_table_{
        {"get",     __get_operator},
        {"add",     __add_operator_atomic},
        {"insert",  __insert_operator_atomic},
        {"update",  __update_operator_atomic},
        {"remove",  __remove_operator_atomic},
        {"create_t",  __create_table_operator_atomic},
        {"drop_t",    __drop_table_operator_atomic},
        {"set_t",     __set_table_operator_atomic},
        {"print_t",   __print_table__operator},
        {"print",     __print_operator},
        {"count",     __count_operator},
        {"clear",     __clear_operator},
        {"log",       __log_operator},
        {"ltables",   __list_tables_operator},
        {"ltriggers", __list_triggers_operator},
        {"rolback",   __rolback_operator},
        {"bef_attach",__bef_attach_operator},
        {"bef_detach",__bef_detach_operator},
        {"aft_attach",__aft_attach_operator},
        {"aft_detach",__aft_detach_operator},
        {"write_to",  __write_table_operator},
        {"llog",      __list_error_log_operator}
    }
{}

atomic_operators::~atomic_operators()
{}

void atomic_operators::execute() 
{
 auto oprt = optr_table_.find(get(0)->get_value());
    
    if (oprt == optr_table_.cend())
    {   
        throw "method: execute | undefine operator";
    }
    next(1);        // oprt_name
    
    auto l_bracet = get(0);
    is_eq_lex(l_bracet->get_type(), LEXEME_TYPE::L_BRACKET, "undefine token" + l_bracet->get_value());
    next(1);        // '('
    
    args_oprt_buf_t args;
    while (is_has_args_oprt())
    {
        args.push_back(
            make_args_oprt()
        );
    }

    next(1);        // ')'

    auto oprt_f = oprt->second;

    oprt_f(std::move(args));
}

bool atomic_operators::is_it_command() const
{
    auto word = get(0)->get_type();     // oprt_name
    auto paraml = get(1)->get_type();   // (param_list)
    if (word == LEXEME_TYPE::WORD && paraml == LEXEME_TYPE::L_BRACKET)
    {
        return true;
    }
    return false;
}


args_oprt_t atomic_operators::make_args_oprt()
{
     auto args_t_ = get(0);
    next(1);    // args_type(example = dt)

    auto two_point = get(0);
    auto two_p_t = two_point->get_type();
    auto two_p_v = two_point->get_value();   
    is_eq_lex(two_p_t, LEXEME_TYPE::TWO_POINT, "undefine token" + two_p_v);
    next(1);    // ':'

    auto args_d_ = get(0);
    next(1);    // args_data(example = '12.34.45')
    return args_oprt_t(args_t_, args_d_);
}

bool atomic_operators::is_has_args_oprt() const
{
    return !( get(0)->get_type() == LEXEME_TYPE::R_BRACKET );
}


lexeme_ptr atomic_operators::get(size_t pos) const
{
    return get_lexeme(pos);
}

void atomic_operators::next(size_t offset)
{
    next_lexeme(offset);
}

 void atomic_operators::is_eq_lex(const LEXEME_TYPE& ltype, 
                              const LEXEME_TYPE& rtype, 
                              std::string&& emsg          )
{
    if (ltype != rtype)
    {
        throw emsg;
    }
}



/* REAUESTES */


void  __add_operator_atomic(args_oprt_buf_t&& args)
{
    args_data arg_data;
    data_ptr data = &arg_data;
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
        case _DATE_TIME_DESCRIPT_ : {
            add_req_atomic(create_token(data));
            break;
        }
        default:
            throw "method : __add_operator_atomic | undefine param type";
    }
}

void  __insert_operator_atomic(args_oprt_buf_t&& args)
{
    //auto data = get_data_ptr();
    args_data arg_data;
    data_ptr data = &arg_data;
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
        case _DATE_TIME_DESCRIPT_ : {
            for_each(insert_req_atomic, create_token(data));
            break;
        }
        default:
            throw "method : __insert_operator_atomic | undefine param type";
    }
}

void  __update_operator_atomic(args_oprt_buf_t&& args)
{
     //auto data = get_data_ptr();
    args_data arg_data;
    data_ptr data = &arg_data;
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
            for_each(update_ds_req_atomic, data);
            break;
        }
        case _TIME_ : {
            for_each(update_ti_req_atomic, data);
            break;
        }
        case _DESCRIPT_ : {
            for_each(update_ds_req_atomic, data);
            break;
        }
        case _DATE_TIME_ : {
            for_each(update_dt_ti_req_atomic, data);
            break;
        }
        case _DATE_DESCRIPT : {
            for_each(update_dt_ds_req_atomic, data);
            break;
        }
        case _TIME_DESCRIPT_ : {
            for_each(update_ti_ds_req_atomic, data);
            break;
        }
        case _DATE_TIME_DESCRIPT_ : {
            for_each(update_dt_ti_ds_req_atomic, data);
            break;
        }
        default:
            throw "method : __update_operator_atomic | undefine param type";
    }
}

void  __remove_operator_atomic(args_oprt_buf_t&& args)
{
    const auto size = args.size();
    if (size > 0 )
    {
        throw "method : __remove_operator_atomic | undefine param";
    }
    for_each(remove_req_atomic);
}

void  __create_table_operator_atomic(args_oprt_buf_t&& args)
{
    //auto data = get_data_ptr();
    args_data arg_data;
    data_ptr data = &arg_data;
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
        case _TABLE_FILE_NAME_SIZE_ : {
            auto tname = *(data->get_table_name_ptr());
            auto fname = *(data->get_file_name_ptr());
            auto size_str = *(data->get_size_ptr());
            auto size =  std::stoi(std::move(size_str));
            
            create_table_req_atomic(std::move(tname), 
                                    std::move(fname) , 
                                    size);
            break;
        }
        default:
            throw "method : __create_table_operator_atomic | undefine param type";
    }
}

void  __drop_table_operator_atomic(args_oprt_buf_t&& args)
{
     //auto data = get_data_ptr();
    args_data arg_data;
    data_ptr data = &arg_data;
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
        case _TABLE_NAME_ : {
            auto tname = *(data->get_table_name_ptr());
            drop_table_req_atomic(std::move(tname));
            break;
        }
        default:
            throw "method : __drop_table_operator_atomic | undefine param type";
    }
}

void  __set_table_operator_atomic(args_oprt_buf_t&& args)
{
    //auto data = get_data_ptr();
    args_data arg_data;
    data_ptr data = &arg_data;
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
        case _TABLE_NAME_ : {
            auto tname = *(data->get_table_name_ptr());
            set_table_req_atomic(std::move(tname));
            break;
        }
        default:
            throw "method : __set_table_operator_atomic | undefine param type";
    }
}