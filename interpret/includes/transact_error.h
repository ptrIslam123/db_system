#ifndef _TRANSACT_ERROR_H_
#define _TRANSACT_ERROR_H_

struct transact_error
{
public:
    transact_error();
    ~transact_error();

    void rolback_records();

private:

};

#endif // !_TRANSACT_ERROR_H_
