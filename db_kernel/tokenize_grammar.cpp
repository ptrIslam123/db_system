#include "includes/tokenize_grammar.h"
#include "includes/methods.h"
#include <iostream>
//#define _MALLOC_DEB_INF_F_

tokenize_grammar::tokenize_grammar(fstream_t&& fstream):
    fstream_(std::move(fstream))
{
#ifndef _MALLOC_DEB_INF_F_
    malloc_deb_inf("tokenize_grammar()\n");
#endif // _MALLOC_DEB_INF_F_
}

tokenize_grammar::~tokenize_grammar()
{
#ifndef _MALLOC_DEB_INF_F_
    malloc_deb_inf("~tokenize_grammar()\n");
#endif // _MALLOC_DEB_INF_F_
}


token_t tokenize_grammar::tokenize()
{
    auto date = tokenize_date();
    auto time = tokenize_time();
    auto type= tokenize_type();
    auto descript = tokenize_description();


    return make_token(
        std::move(date),
        std::move(time),
        type,
        std::move(descript)
    );
}


time_t_ tokenize_grammar::tokenize_time()
{
    return std::move(tokenize_word());
}


date_t_ tokenize_grammar::tokenize_date()
{
    return std::move(tokenize_word());
}


type_t_ tokenize_grammar::tokenize_type()
{
    return std::move(tokenize_word());
}


#ifndef _OLD_API_DESCRIPTION_
descript_t_ tokenize_grammar::tokenize_description()
{
    descript_t_ buffer;
    int indx = 0;
    char cur_s = 0;
    try
    {
         while (true)
        {
            cur_s = get();
            if (is_eof() || cur_s == '\n')break;
            if (cur_s == '\"')
            {
                indx++;
                //buffer.at(indx) = std::move(tokenize_data());
                (buffer.second).at(indx) = std::move(tokenize_data());
                indx++;
                continue;
            }
            (buffer.second).at(indx) += cur_s; 
        }
    }
    catch(std::out_of_range& e)
    {
        //log error
        error_report(
            F_PATH_DB_KERNEL_DEGUB_INF,
            "\n\n#~ tokenize_grammar::tokenize_description()\n\n"
        );
        error_report(
            F_PATH_DB_KERNEL_DEGUB_INF, 
            "std::out_of_range whit std::array\n"
        );
        error_report(F_PATH_DB_KERNEL_DEGUB_INF, indx);
        throw -1;
    }
    buffer.first = indx;
    return std::move(buffer);
}
#endif // !_OLD_API_DESCRIPTION_


descript_t_ tokenize_grammar::tokenize_description()
{
    descript_t_ buffer;
    buffer.reserve(_B_SIZE_DESCRIPT_T_);
    char cur_s = 0;
    while (true)
    {
        cur_s = get();
        if (is_eof() || cur_s == '\n')
            break;
        buffer += cur_s;
    }
    return std::move(buffer);
}

word_t tokenize_grammar::tokenize_word()
{
    word_t buffer;
    char cur_s = 0;
    while (true)
    {
        cur_s = get();
        if (is_eof() || isspace(cur_s))break;
        buffer += cur_s;
    }
    skip_nul_scpace();
    return std::move(buffer);
}


word_t tokenize_grammar::tokenize_heder()
{
    word_t heder = "Дата и время	Тип события	Описание";
    char cur_s = 0;
    while (true)
    {
        cur_s = get();
        if (cur_s == '\n')
        {
            break;
        }
    }
    return std::move(heder);
}


word_t tokenize_grammar::tokenize_data()
{
    word_t buffer;
    buffer += '\"';
    char cur_s = 0;
    while (true)
    {
        cur_s = get();
        if (cur_s == '\"')
        {
            buffer += cur_s;
            break;
        }
        buffer += cur_s;
    }
    return std::move(buffer);
}


void tokenize_grammar::skip_nul_scpace()
{
    char cur_s  = 0;
    while (true)
    {
        cur_s = get();
        if (is_eof())break;
        if (!isspace(cur_s))
        {
            seek(-1);
            break;
        }
    }
}


token_t tokenize_grammar::make_token
(date_t_&& date, time_t_&& time, type_t_ type, descript_t_&& descript)
{
    return std::make_unique<token>(
        std::move(date),
        std::move(time),
        type,
        std::move(descript)
    );
}


fstream_t tokenize_grammar::get_fsretam() 
{
    return std::move(fstream_);
}

char tokenize_grammar::get() const
{
    return fstream_->getchar();
}


void tokenize_grammar::seek(int offset) const
{
    fstream_->seekchar(offset);
}


bool tokenize_grammar::is_eof() const
{
    return fstream_->is_eof();
}


bool tokenize_grammar::is_open_file() const
{
    return fstream_->is_open();
}


std::string tokenize_grammar::get_file() const
{
    return fstream_->get_file();
}

descript_t_   make_description(const word_t& word)
{
    descript_t_   descript;
    return std::move(descript);
}