#ifndef _HWSTL_ITERATOR_H
#define _HWSTL_ITERATOR_H

namespace hwstl{

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag :public input_iterator_tag {};
struct bidirectional_iterator_tag :public forward_iterator_tag {};
struct random_access_iterator_tag :public bidirectional_iterator_tag {};


template <class category, class T, class distance = ptrdiff_t,
        class pointer = T*, class reference = T&>
struct iterator{
    typedef category iterator_category;
    typedef T value_type;
    typedef distance difference_type;
    typedef T* pointer;
    typedef T& reference;
};


/**
 * 泛化类型萃取器
 * **/

template <class Iterator>
struct iterator_traits{
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
};

/**
 * 特化类型萃取器 原生指针
 * **/
template <class T>
struct iterator_traits<T*>{
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
};


/**
 * 特化类型萃取器 const-to-pointer
 * **/
template <class T>
struct iterator_traits<const T*>{
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef const T* pointer;
    typedef const T& reference;
};

template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&){
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return category();
}

template <class Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&){
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}


template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type*
difference_type(const Iterator&){
    return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag){
    typename iterator_traits<InputIterator>::difference_type n=0;
    for(;first!=last;first++){
        n++;
    }
    return n;
}

template <class RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
__distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag){
    return last-first;
}

template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last){
    typedef typename
        iterator_traits<InputIterator>::iterator_category caterator;
    return __distance(first,last,caterator());
}


template <class InputIterator, class Distance>
inline void __advance(InputIterator& i,Distance n,input_iterator_tag){
    while (n--) ++i;
}

template <class BidirectionalIterator, class Distance>
inline void __advance(BidirectionalIterator& i,Distance n,bidirectional_iterator_tag){
    if(n>0){
        while(n--)++i;
    }
    else
        while(n++)--i;
}


template <class RandomAccessIterator,class Distance>
inline void __advance(RandomAccessIterator& i, Distance n, random_access_iterator_tag){
    i+=n;
}

template <class InputIterator,class Distance>
inline void advance(InputIterator& i, Distance n){
    __advance(InputIterator, n, iterator_category(i));
}



}
#endif