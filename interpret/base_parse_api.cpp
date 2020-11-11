#include "includes/base_parse_api.h"

base_parse_api::base_parse_api(base_parse_api::conatiner_t&& container):
    container_(std::move(container)),
    size_(container_.size()),
    pos_(0)
{}

base_parse_api::~base_parse_api()
{}

lexeme_ptr base_parse_api::get_lexeme(size_t pos) const
{
    auto position = pos_ + pos;
    auto iter = container_.begin();
    std::advance(iter, position);
    return (*iter).get();
}

void base_parse_api::next_lexeme(size_t offset)
{
    pos_ += offset;
}

 void base_parse_api::is_eq_lexeme(const LEXEME_TYPE& ltype, 
                                   const LEXEME_TYPE& rtype,
                                   std::string&& emsg) const
 {
     ////////
 }

 size_t base_parse_api::get_size() const
 {
     return size_;
 }

 size_t base_parse_api::get_pos() const
 {
     return pos_;
 }



