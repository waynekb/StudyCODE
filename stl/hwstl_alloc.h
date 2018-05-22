#ifndef _HWSTL_ALLOC_H
#define _HWSTL_ALLOC_H

namespace hwstl{
#include <iostream>

#define __THROW_BAD_ALLOC std::cerr<<"out of memory"<<std::endl;exit(1)


/**
 * 一级空间配置器
 * 
 **/

template <int inst>
class __malloc_alloc_template{
private:
    static void* oom_malloc(size_t);
    static void* oom_realloc(void*, size_t);
    static void (* __malloc_alloc_oom_handler)();
public:
    static void* allocate(sizt_t n){
        void* result=malloc(n);
        if(result==0)result = oom_malloc(n);
        return result;
    }
    static void deallocate(void* p,size_t){
        free(p);
    }

    static void* reallocate(void* p,size_t /*old_sz*/,size_t new_sz){
        void* result =realloc(p,new_sz);
        if(result==0) result=oom_realloc(p, new_sz);
        return result;
    }

    static void (* set_malloc_handler(void (*f)() ))(){
        void (* old)() =__malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler=f;
        return (old); 
    }
};

template <int inst>
void (* __malloc_alloc_template<inst>::__malloc_alloc_oom_handler)()=0; //为函数指针 _malloc_alloc_oom_handler设初值

template <int inst>
void* __malloc_alloc_template<inst>::oom_malloc(size_t n){
    void (* hw_malloc_handler)();
    void* result;

    for(;;){
        hw_malloc_handler=__malloc_alloc_oom_handler;
        if(hw_malloc_handler ==0){
            __THROW_BAD_ALLOC;
        }
        (*hw_malloc_handler)();
        result=malloc(n);
        if(result)return result;
    }
}  

template <int inst>
void* __malloc_alloc_template<inst>::oom_realloc(void* p,size_t n){
    void (* hw_malloc_handler)();
    void* result;
    for(;;){
        hw_malloc_handler=__malloc_alloc_oom_handler;
        if(hw_malloc_handler == 0){
            __THROW_BAD_ALLOC;
        }
        (*hw_malloc_handler)();
        result = realloc(p,n);
        if(result)return result;
    }
}

typedef __malloc_alloc_template<0> malloc_alloc;


/**
 * 二级空间配置器
 * 
 **/

enum {__ALING =8};
enum {__MAX_BYTES =128};
enum {__NFREELISTS = __MAX_BYTES/__ALING};

template <bool threads, int inst>
class __default_alloc_template{
private:
    static size_t ROUND_UP(size_t bytes){
        return (((bytes) + __ALING-1) & ~(__ALING-1));
    }
    union obj{
        union obj * free_list_link;
        char client_data[1];
    };

    
    static size_t FREELIST_INDEX(size_t bytes){
        return (((bytes) + __ALING-1)/__ALING-1)
    }
    
    static void* refill(size_t n);    
    static char* chunk_alloc(size_t size,int &nobjs);
    
    static obj * volatile free_list[__NFREELISTS];
    static char* start_free;
    static char* end_free;
    static size_t heap_size;

public:
    static void* allocate(size_t n);
    static void deallocate(void* p,size_t n);
    static void* reallocate(void* p,size_t old_sz,size_t new_sz);
};

template <bool threads,int inst>
char* __default_alloc_template<threads,inst>::start_free = 0;

template <bool threads,int inst>
char* __default_alloc_template<threads,inst>::end_free = 0;

template <bool threads,int inst>
char* __default_alloc_template<threads,inst>::heap_size = 0;


template <bool threads,int inst>
__default_alloc_template<threads,inst>::obj* volatile
__default_alloc_template<threads,inst>::free_list[__NFREELISTS]=
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};


/**
 *  这个声明原来的形式是：obj** hw_free_list，这样的话*hw_free_list（空闲的内存块指针数组中的一个元素）
 * 可能被优化到寄存器中，从而使库代码无法lock住对它的读调用（如果在寄存器中则另一个线程可能会无意中修改该寄存器的值，
 * 而在内存中由于另一个线程没有访问权力所以不能修改）。
 * 要声明变量必须在内存中就要用volatile修饰，这里修饰的是*hw_free_list，是free_list数组中的一个元素，
 * 而不是数组指针，所以volatile放在两个*中间。
*/

template <bool threads,int inst>
void * __default_alloc_template<threads,inst>::allocate(size_t n){
    obj* volatile * hw_free_list;
    obj* result;

    if(n > (size_t)__MAX_BYTES){
        return (malloc_alloc::allocate(n));
    }

    hw_free_list = free_list + FREELIST_INDEX(n);
    result = *hw_free_list;
    if(result==0){
        void *r =refill(ROUND_UP(n));
        return r;
    }

    *hw_free_list=result->free_list_link;
    return (result);
};

template <bool threads,int inst>
void  __default_alloc_template<threads,inst>::deallocate(void* p,size_t n){
    obj* volatile* hw_free_list;
    obj* q=(obj*)p;
    if(n > (size_t)__MAX_BYTES){
        malloc_alloc::deallocate(p);
        return;
    }
    hw_free_list=free_list + FREELIST_INDEX(n);
    q->free_list_link=*hw_free_list;
    *hw_free_list=q;
    
};

template <bool threads,int inst>
void* __default_alloc_template<threads,inst>::reallocate(void* p,size_t old_sz,size_t new_sz){

};

template <bool threads,int inst>
void* __default_alloc_template<threads,inst>::refill(size_t n){
    int nobjs=20;
    char* chunk=chunk_alloc(n, nobjs);
    objs* volatile * hw_free_list;
    objs* result=chunk;
    objs* next_objs, *curren_objs;
    int i=1;
    if(nobjs=1)return chunk;

    hw_free_list = free_list+FREELIST_INDEX(n);
    *hw_free_list= (objs*)(chunk+n);
    next_objs = (objs*)(chunk+n);
    for(;i<nobjs;i++){
        curren_objs=next_objs;
        next_objs=(objs*)((char*)curren_objs+n);
        curren_objs->free_list_link=next_objs;
    }
    curren_objs->free_list_link=NULL;
    return (result);
};





template <bool threads, int inst>
char* __default_alloc_template<threads,inst>::
chunk_alloc(size_t size,int &nobjs){
    char* result;
    size_t total_bytes=size * nobjs;
    size_t bytes_left = end_free-start_free;

    if(bytes_left >= total_bytes){
        result = start_free;
        start_free += total_bytes;
        return (result);
    }
    else if(bytes_left >= size){
        nobjs = bytes_left/size;
        result = start_free;
        start_free += size*nobjs;
        return (result);
    }
    else{

        size_t bytes_to_get = 2* total_bytes + ROUND_UP(heap_size >> 4);
        if(bytes_left > 8){
            objs* volatile * hw_free_list = free_list+FREELIST_INDEX(bytes_left)-1;
            (obj*)start_free->free_list_link = * hw_free_list;
            * hw_free_list = (objs*)start_free;
        }
        start_free = (char*) malloc( bytes_to_get);

        if(start_free == 0){
            int i;
            objs* volatile * hw_free_list;
            for(i=size; i<= __MAX_BYTES; i+=__ALING){
                hw_free_list = free_list + FREELIST_INDEX(i);
                objs* p= *hw_freeList;
                if(hw_free_list != NULL){
                    start_free = (char*)hw_free_list;
                    end_free=(char*)hw_free_list + i;
                    *hw_freeList = p->free_list_link;
                    return (chunk_alloc(size, nobjs));
                }
            }
            end_free = 0;
            start_free = (char*)malloc_alloc::allocate(bytes_to_get);//调用第一级配置器，看看 out_of_memory机制能否尽力
        }
        heap_size = bytes_to_get;
        end_free = start_free + bytes_to_get;
        return (chunk_alloc(size,nobjs));
    }


}



template<class T, class Alloc>
class simple_alloc{
public:
    static T* allocate(size_t n){
        return n==0?:0: (T*) Alloc::allocate( n * sizeof(T) );
    }
    static T* allocate(void){
        return (T*) Alloc::allocate(sizeof(T));
    }
    static void deallocate(T* p,size_t n){
        if( n!=0 ) Alloc::deallocate(p, n* sizeof(T));
    }
    static void deallocate(T* p){
        if( n!=0 ) Alloc::deallocate(p,sizeof(T));
    }
};

}
#endif