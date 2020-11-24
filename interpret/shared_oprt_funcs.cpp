#include "includes/shared_oprt_funcs.h"
#include "includes/sys_functions.h"
#include "includes/option_parse.h"

#include <iostream>


void __get_operator(args_oprt_buf_t&& args)
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
            for_each(comparator_dt, get_req, data);
            break;
        }
        case _TIME_ : {
            for_each(comparator_ti, get_req, data);
            break;
        }
        case _DESCRIPT_ : {
            for_each(comparator_ds, get_req, data);
            break;
        }
        case _DATE_TIME_ : {
            for_each(comparator_dt_ti, get_req, data);
            break;
        }
        case _DATE_DESCRIPT : {
            for_each(comparator_dt_ds, get_req, data);
            break;
        }
        case _TIME_DESCRIPT_ : {
            for_each(comparator_ti_ds, get_req, data);
            break;
        }
        case _DATE_TIME_DESCRIPT_ : {
            for_each(comparator_dt_ti_ds, get_req, data);
            break;
        }
        default:
            throw "method : __get_operator | undefine param type";
    }
}

void __print_table__operator(args_oprt_buf_t&& args)
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
    
    if (type == _TABLE_NAME_)
    {
        print_table_req(data);
    }
    else
    {
        throw "method : __print_table__operator | undefine param";
    }
    
}

void __print_operator(args_oprt_buf_t&& args)
{
    const auto size = args.size();
    if (size > 0 )
    {
        throw "method : __print_operator | undefine param";
    }
    for_each(_print_token);
}

void  __count_operator(args_oprt_buf_t&& args)
{
    const auto size = args.size();
    if (size > 0 )
    {
        throw "method : __print_operator | undefine param";
    }
    std::cout << _get_size_pesronse_buf() << "\n";
}

void __clear_operator(args_oprt_buf_t&& args)
{
    const auto size = args.size();
    if (size > 0 )
    {
        throw "method : __clear_operator | undefine param";
    }
    clear_req();
}


void __log_operator(args_oprt_buf_t&& args)
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
        case _DESCRIPT_ : {
            std::cout << "LOG: " << (*data->get_descript_ptr()) << "\n";
            break;
        }
        default:
            throw "method : __get_operator | undefine param type";
    }
}

void __list_tables_operator(args_oprt_buf_t&& args)
{
    const auto size = args.size();
    if (size > 0 )
    {
        throw "method : __list_tables_operator | undefine param";
    }
    print_tables_req();
}

void __list_triggers_operator(args_oprt_buf_t&& args)
{
    const auto size = args.size();
    if (size > 0 )
    {
        throw "method : __list_triggers_operator | undefine param";
    }
}

void __rolback_operator(args_oprt_buf_t&& )
{
    rolback_records();
}

data_ptr get_data_ptr()
{
    static args_data data;
    data.set_null_type();
    return &data;
}



void  __bef_attach_operator(args_oprt_buf_t&& args)
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
        case _TG_NAME_OP_ : {
            bef_attach_req(data);
            break;
        }
        default:
            throw "method : __bef_attach_operator | undefine param type";
    }
}

void  __bef_detach_operator(args_oprt_buf_t&& args)
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
        case _NAME_ : {
            bef_detach_req(data);
            break;
        }
        default:
            throw "method :__bef_detach_operator | undefine param type";
    }
}

void  __aft_attach_operator(args_oprt_buf_t&& args)
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
        case _TG_NAME_OP_ : {
            aft_attach_req(data);
            break;
        }
        default:
            throw "method : __aft_attach_operator | undefine param type";
    }
}

void  __aft_detach_operator(args_oprt_buf_t&& args)
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
        case _TG_TNAME_NAME_ : {
            aft_detach_req(data);
            break;
        }
        default:
            throw "method :__aft_detach_operator | undefine param type";
    }
}





void init_data(data_ptr data, args_oprt_buf_t&& args)
{
    static option_parse opt_parse_; 
    auto size = args.size();
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
            i++;
            continue;
        }
        if (args_type == "ti")
        {
            data->set_args_type(_TIME_);
            auto time_ptr = (args.at(i).second)->get_ptr_value();
            data->set_time_ptr(time_ptr);
            i++;
            continue;
        }
        if (args_type == "ds")
        {
            data->set_args_type(_DESCRIPT_);
            auto descr_ptr = (args.at(i).second)->get_ptr_value();
            data->set_descript_ptr(descr_ptr);
            i++;
            continue;
        }
        if (args_type == "tn")
        {
            data->set_args_type(_TABLE_NAME_);
            auto table_name_ptr = (args.at(i).second)->get_ptr_value();
            data->set_table_name_ptr(table_name_ptr);
            i++;
            continue;
        }
        if (args_type == "fn")
        {
            data->set_args_type(_FILE_NAME_);
            auto file_name_ptr = (args.at(i).second)->get_ptr_value();
            data->set_file_name_ptr(file_name_ptr);
            i++;
            continue;
        }
        if (args_type == "sz")
        {
            data->set_args_type(_SIZE_TABLE_);
            auto size_ptr = (args.at(i).second)->get_ptr_value();
            data->set_size_ptr(size_ptr);
            i++;
            continue;
        }
        if (args_type == "nm")
        {
            data->set_args_type(_NAME_);
            auto name_ptr = (args.at(i).second)->get_ptr_value();
            data->set_name_ptr(name_ptr);
            i++;
            continue;
        }
        if (args_type == "op")
        {
            data->set_args_type(_OPTION_);
            auto opt_val_ptr = (args.at(i).second)->get_ptr_value();
            opt_parse_.parse(data, opt_val_ptr);
            i++;
            continue;
        }
        else
        {
            throw "method: init_data | undefine token";
        }
    }
}

