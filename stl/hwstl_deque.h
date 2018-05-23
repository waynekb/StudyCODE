#ifndef _HWSTL_DEQUE_H
#define _HWSTL_DEQUE_H

namespace hwstl{

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag :public input_iterator_tag {};
struct bidirectional_iterator_tag :public forward_iterator_tag {};
struct random_access_iterator_tag :public bidirectional_iterator_tag {};


inline size_t hw_deque_buf_size(size_t n, size_t sz){
    return n!=0 ? :(sz <512? size_t(512/sz) : size_t(1));
}

template<class T, class Ref, class Ptr, size_t Bufsize>
class hw_deque_iterator{
public:
    typedef hw_deque_iterator<T, T&, T*, Bufsize> iterator;
    typedef hw_deque_iterator<T,const T&,const T*, Bufsize> const_iterator;
    static size_t buffer_size(){return hw_deque_buf_size(Bufsize, sizeof(T) );}

    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef size_t size_type;
    typedef ptrdeiff_t difference_type;
    typedef T** map_pointer;

    typedef hw_deque_iterator self;

    T* cur;
    T* first;
    T* last;
    map_pointer node;


    void set_node(map_pointer new_node){
        node=new_node;
        first=*new_node;
        last=first+difference_type(buffer_size);
    }

    reference operator*(){return *cur;}
    pointer operator->(){return &(operator*());}//尽量不要直接对成员变量进行读取

    difference_type operator-(const self& x)const{
        return difference_type(buffer_size()) * (node-x.node-1)+
        (cur - first) + (x.last -x.cur);
    }

    self& operator++(){
        ++cur;
        if(cur==last){
            set_node(node+1);
            cur=first;
        }
        return *this;
    }

    self& operator--(){
        if(cur==first){
            set_node(node-1);
            cur=last;
        }
        --cur;
        return *this;
    }




};


template<class T, class Alloc=alloc,size_t Bufsize=0>
class deque{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef hw_deque_iterator<T, T&, T*, Bufsize> iterator;

    
    iterator begin(){return start;}
    iterator end(){return finish;}

    reference operator[](size_type n){
        return start[difference_type(n)];
    }

    referecne front(){return *start;}

    reference back(){
        iterator tmp=finish;
        --tmp;
        return *tmp;
    }

    size_type size() const{return finish-start;}

    deque(int n, const value_type& value):start(),finish(), map(0), map_size(0){
        fill_initialize(n,value);
    }

protected:
    typedef pointer* map_pointer;
    map_pointer map;
    size_type map_size;

    iterator start;
    iterator finish;

    map_pointer map;
    size_type map_size;
    void fill_initialize(size_type n, value_type& value);
};



template<class T, class Alloc,size_t Bufsize>
void deque<T, Alloc, Bufsize>::fill_initialize(size_type n,value_type& value){
    
}

}

#endif