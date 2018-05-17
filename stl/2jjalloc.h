#ifndef _JJALLOC_
#define _JJALLOC_

#include <iostream>
#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
namespace JJ
{

template <class T>
inline  T* _allocate(ptrdiff_t size,T*){
    // set_new_handler(0);

    T* temp=(T*)::operator new((size_t)(size*sizeof(T)));
    if(temp==0){
        std::cerr<<"out of memory"<<std::endl;
        exit(1);
    }
    std::cout<<"use self operator new"<<std::endl;
    return temp;
}


template <class T>
inline void _deallocate(T* buffer){
    ::operator delete(buffer);
    std::cout<<"use self operator delete"<<std::endl;
}

template <class T1,class T2>
inline void _construct(T1 *p,const T2& value){
    new (p) T1(value);
    std::cout<<"use self __construct"<<std::endl;
}


template<class T>
inline void _destroy(T* ptr){
    ptr->~T();
    std::cout<<"use self __desconstruct"<<std::endl;
}

template <class T>
class allocator{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    template <class U>
    struct rebind{
        typedef allocator<U> other;
    };

    pointer allocate(size_type n,const void* hint =0){
        return _allocate((difference_type)n,(pointer)0);
    }

    void deallocate(pointer p, size_type n){ _deallocate(p);}

    void construct(pointer p,const T& value){
        _construct(p,value);
    }

    void destroy(pointer p){_destroy(p);}

    pointer address(reference x){
        std::cout<<"use self address"<<std::endl;
        return (pointer)&x;
        }

    const_pointer const_address(const reference x){return (const_pointer)&x;}

    size_type max_size() const{
        return size_type(UINT_MAX/sizeof(T));
    }

};

}
#endif