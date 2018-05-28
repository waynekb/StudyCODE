#ifndef HWSTL_PAIR_H
#define HWSTL_PAIR_H

namespace hwstl{

template<class T1, class T2>
struct pair{
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;
    pair() :first(T1()), second(T2()){}
    pair(const T1& x1, const T2& x2): first(x1), second(x2){}
};



}

#endif