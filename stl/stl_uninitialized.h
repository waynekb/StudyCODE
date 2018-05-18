#ifndef _STL_UNINITIALIZED_H
#define _STL_UNINITIALIZED_H

#include <string.h>


/*
* uninitialized_fill_n
*
*/

template <class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator begin,Size n, const T& x){
    return __uninitialized_fill_n(first, n, x, value_type(first));
}

template <class ForwardIterator, class Size, class T, class U>
inline ForwardIterator __uninitialized_fill_n(ForwardIterator begin, Size n, const T& x, U*){
    typedef typename __type_traits<U>::is_POD_type is_POD;
    return __uninitialized_fill_n_aux(first, n, x, is_POD());
}

/**
 * 特化函数模板
 * 
 * **/


template <class ForwardIterator, class Size, class T>
inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator begin, Size n, const T& x, __ture_type){
    return fill_n(firs,n,x);
}

template <class ForwardIterator, class Size, class T>
inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator begin, Size n, const T& x, __false_type){
    ForwardIterator curr =first;
    for(int i; i < n ;i++, curr++){
        construct(&*curr,x);
    }
    return curr;    //返回最后一个迭代器？？？？？？？？？？
}




/*
* uninitialized_copy
*
*/
template <class InputIterator, class ForwardIterator>
inline ForwardIterator uninitialized_copy(InputIterator begin, InputIterator last, ForwardIterator result){
    return __uninitialized_copy(first, last, result, value_type(result));
}

template <class InputIterator, class ForwardIterator,class T>
inline ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T*){
    typedef typename __type_traits<T>::is_POD_type is_POD;
    return __uninitialized_copy_aux(first, last, result, is_POD())；
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __true_type){
    return copy(first,last,result);
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __false_type){
    ForwardIterator cur=result;
    for(;first != last; first++,cur++){
        construct(&*cur, first);
    }
    return cur;
}

inline char* uninitialized_copy(const char* first, const char* last, char* result){
    memmove(result, first, last-first);
    return result+(last-first);
}

inline wchar_t* uninitialized_copy(const wchar_t* first, const wchar_t* last, wchar_t* result){
    memmove(result, first, sizeof(wchar_t)*(last-first));
    return result+(last-first);
}



/**
 * 
 *  uninitialized_fill
 * 
*/


template<class ForwardIterator, class T>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last,const T& x){
    return __uninitialized_fill(first, last, x, value_type(first));
}

template<class ForwardIterator, class T, class U>
inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x, U*){
    typedef typename __type_traits<U>::is_POD_type is_POD;
    return __uninitialized_fill__aux(first, last, x, is_POD());
}

template<class ForwardIterator, class T>
inline void __uninitialized_fill__aux(ForwardIterator first, ForwardIterator last, const T& x, __true_type){
    return fill(first, last, x);
}

template<class ForwardIterator, class T>
inline void __uninitialized_fill__aux(ForwardIterator first, ForwardIterator last, const T& x, __false_type){
    for(;first != last; first++){
        construct(first, x);
    }
}


#endif