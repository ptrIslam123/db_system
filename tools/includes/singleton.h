#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <memory>

/* not multithreaded singleton class */
template<class T>
struct singleton_classic : public T
{
public:
    singleton_classic(singleton_classic&& ) = delete;
    singleton_classic(const singleton_classic& ) = delete;
    ~singleton_classic();

    singleton_classic& operator= (const singleton_classic& ) = delete;
    singleton_classic& operator= (singleton_classic&& ) = delete;

    template<typename ... Args>
    static singleton_classic& instance(Args&& ... );

private:
    template<typename ... Args>
    singleton_classic(Args&& ... );
};


template<class T>
template<typename ... Args>         // sysntax_error !
singleton_classic<T>::singleton_classic(Args&& ... args):
    T( std::forward<Args>(args)... )
{}

template<class T>
singleton_classic<T>::~singleton_classic()
{

}

template<class T>
template<typename ... Args>
singleton_classic<T>& singleton_classic<T>::instance(Args&& ... args)
{
    static singleton_classic<T> inst_( std::forward<Args>(args)... );
    return inst_;
}

#endif // !_SINGLETON_H_
