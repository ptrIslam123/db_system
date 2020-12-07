#include "includes/base_parse_api.h"
#include "includes/sys_error.h"
#include <memory>

base_parse_api::base_parse_api():
    size_(0),
    pos_(0)
{}

base_parse_api::base_parse_api(base_parse_api::container_ptr container):
    container_(container),
    size_(container_->size()),
    pos_(0)
{}

base_parse_api::~base_parse_api()
{}


void base_parse_api::set_pos(size_t pos)
{
    pos_ = pos;
}

lexeme_ptr base_parse_api::get_lexeme(size_t pos) const
{
    auto position = pos_ + pos;
    auto iter = container_->begin();
    std::advance(iter, position);
    try
    {
        auto val = (*iter).get();
        return val;   
    }
    catch(const std::exception& e)
    {
        throw sys_error(error_type::OUT_OF_RANGE,
                        "base_parse_api::get_lexeme : out of range lexemes");
    }
    return nullptr;
}

lexeme_uptr base_parse_api::get_lexeme_uptr(size_t pos)
{
    auto position = pos_ + pos;
    auto iter = container_->begin();
    std::advance(iter, position);

    auto val = std::move((*iter));
    container_->erase(iter);
    size_--;

    return val;      // return std::move(val); // -Wall
}

bool base_parse_api::is_end() const
{
    return (pos_ >= size_);
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



