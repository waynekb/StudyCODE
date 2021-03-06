#ifndef _HWSTL_CONSTRUCT_H 
#define _HWSTL_CONSTRUCT_H 
 
 
 
#include <new.h> 
#include "hwtype_traits.h" 
 
 
namespace hwstl{ 
 
template <class T1,class T2> 
inline void construct(T1* p,T2 value){ 
    new(p) T1(value); 
} 
 
 
/** 
 *  
 * 析构指针所指的对象 
*/ 
template <class T> 
inline void destroy(T* pointer){ 
    pointer->~T(); 
} 
 
template <class ForwardIterator> 
inline void destroy(ForwardIterator first, ForwardIterator last){ 
    __destroy(first,last,value_type(first));    //根据迭代器存储数据类型判断是否需要调用析构函数 
} 
 
template <class ForwardIterator,class T> 
inline void __destroy(ForwardIterator first,ForwardIterator last, T*){ 
    typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor; 
    __destroy_aux(first,last,trivial_destructor()); 
} 
 
template <class ForwardItertor> 
inline void __destroy_aux(ForwardIterator first,ForwardIterator last, __false_type){ 
    for(;first != last;first++) 
        destroy(&*first); 
} 
 
template <class ForwardIterator> 
inline void __destroy_aux(ForwardIterator first,ForwardIterator last, __true_type){} 
 
inline void destroy(char *,char *){} 
inline void destroy(wchar_t *,wchar_t *){} 
 
} 
 
#endif