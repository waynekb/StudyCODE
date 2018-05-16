#ifndef _JJALLOC_
#define _JJALLOC_

#include <iostream>
namespace JJ
{

template <class T>
inline  T* __allocate(ptrdiff_t size,T*){
    set_new_handler(0);
    T* temp=(T*)::operator new((size_t)(size*sizeof(T)));
    if(temp==0){
        cer<<"out of memory"<<endl;
        exit(1);
    }
    return temp;
}


template <class T>
inline void _deallocate(T* buffer){
    ::operator delete(buffer);
}

}
#endif