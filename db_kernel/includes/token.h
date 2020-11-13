#ifndef _TOKEN_H_
#define _TOKEN_H_
#define MAX_LEN_DESCRIPT 15
#define _OLD_API_DESCRIPTION_
#define _B_SIZE_DATE_T_ 10
#define _B_SIZE_TIME_T_ 8
#define _B_SIZE_DESCRIPT_T_ 300

#include <string>
#include <array>
#include <memory>

struct token;
using date_t_           = std::string;
using time_t_           = std::string;
using type_t_           = std::string;
using word_t            = std::string;

using descript_t_       = word_t;
using descript_ptr_     = descript_t_*;
using token_t           = std::unique_ptr<token>;
#ifndef _OLD_API_DESCRIPTION_
using descript_len      = size_t;
using descript_val      = std::array<word_t, MAX_LEN_DESCRIPT>;
using descript_val_ptr  = descript_val*;
using descript_t_       = std::pair<descript_len, descript_val>;
#endif // _OLD_API_DESCRIPTION_

struct token
{
public:
   token();
   token(date_t_&& , time_t_&&, type_t_,  descript_t_&& );
   ~token();

   date_t_&     get_date();
   time_t_&     get_time();
   type_t_      get_type();
   descript_t_& get_descript();

   void         set_date(const date_t_& );
   void         set_time(const time_t_& );
   void         set_type(type_t_ );
   void         set_descript(const descript_t_& );
   token_t      clone();

private:
    date_t_     date_;
    time_t_     time_;
    type_t_     type_;
    descript_t_ descript_;
};

template<typename ... Args>
token_t make_token(Args&& ... args)
{
    return std::make_unique<token>(std::forward<Args>(args) ... );
}

bool const is_eq_ds(const descript_ptr_ , const descript_ptr_  );

#endif // !_TOKEN_H_
