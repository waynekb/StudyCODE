#ifndef _HWLIST_H
#define _HWLIST_H

namespace hwstl{

#include "hwstl_iterator.h"
#include "hwstl_alloc.h"

template <class T>
struct hw_list_node{
    typedef list_node<T>* ln_pointer;
    T data;
    ln_pointer next;
    ln_pointer prev;
};

template <class T, class Alloc=alloc>
struct hw_list{
protected:
    typedef 
private:
    
};




}
#endif