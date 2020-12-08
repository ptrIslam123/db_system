#ifndef _RESPONSE_DATA_H_
#define _RESPONSE_DATA_H_

#include <vector>
#include <iostream> // for size_t
#include "../../tools/includes/singleton.h"

struct response_data;
using response_data_t   = singleton_classic<response_data>;

struct response_data
{
public:
    using index_t       = size_t;
    using container_t   = std::vector<index_t>;

    response_data();
    ~response_data();

    void        reserve(size_t );
    void        add(size_t );
    void        clear_buf();
    index_t     get_index(size_t ) const;
    size_t      size() const;
    size_t      capacity() const;
    container_t get_response();

private:
    size_t      size_;
    container_t poll_indx_;
};

#endif // !_RESPONSE_DATA_H_
