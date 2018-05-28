#ifndef HWSTL_MAP_H
#define HWSTL_MAP_H

namespace hwstl{

template <class key, class T, class compare=less<key>, class Alloc=alloc>
class map{
public:
    typedef key key_type;
    typedef T data_type;
    typedef T mapped_type;
    typedef pair<const key, T> value_type;
    typedef compare key_compare;

    class value_compare:public binaru_function<value_type, value_type, bool>{
        friend class map<key, T, compare, Alloc>;
    protected:
        compare comp;
        value_compare(compare c):comp(c){}
    public:
        bool operator()(const value_type&x, const value_type& y) const{
            return comp(x.first, y.first);
        }
    };
};



}

#endif