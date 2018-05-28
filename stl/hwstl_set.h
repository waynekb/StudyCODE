#ifndef HWSTL_SET_H
#define HWSTL_SET_H


namespace hwstl{

template<class key, class compare = less<key>, class Alloc=alloc>
class set{
public:
    typedef key key_type;
    typedef key value_type;
    typedef compare key_compare;
    typedef compare value_compare;


private:
    template<class T>
    struct identity:public unary_function<T,T>{
        const T& operator()(const T& x) const{return x;}
    };

    typede rb_tree<key_type, value_type, identity<value_type>, key_compare, Alloc> rep_type;
    rep_type t; 

    set():t(compare()){}
    explicit set(const compare& comp):t(comp){}
    template<class InputIterator>
    set(InputIterator first, InputIterator last)
    :t(compare()){t.insert_unique(first,last);}

    template <class InputIterator>
    set(InputIterator first, InputIterator last, const compare& comp)
    :t(comp){t.insert_unique(first, last);}

    set(const set<key,compare, Alloc>& x) :t(x.t){}
    set<key, compare, Alloc>& operator=(const set<key, compare, Alloc>& x){
        t=x.t;
        return *this;
    }
};
}

#endif