#include "includes/shared_oprt_funcs.h"
#include "includes/sys_functions.h"


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
    const auto size = args.size();
    if (size > 0 )
    {
        throw "method : __print_table__operator | undefine param";
    }
    print_table_req();
}

void __print_operator(args_oprt_buf_t&& args)
{
    const auto size = args.size();
    if (size > 0 )
    {
        throw "method : __print_operator | undefine param";
    }
    _print_heder();
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

data_ptr get_data_ptr()
{
    static args_data data;
    data.set_null_type();
    return &data;
}


void init_data(data_ptr data, args_oprt_buf_t&& args)
{
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
        else
        {
            throw "method: init_data | undefine token";
        }
    }
}