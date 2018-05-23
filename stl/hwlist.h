#ifndef _HWLIST_H
#define _HWLIST_H

namespace hwstl{

#include "hwstl_iterator.h"
#include "hwstl_alloc.h"

template <class T>
struct hw_list_node{
    typedef hw_list_node<T>* ln_pointer;
    T data;
    ln_pointer next;
    ln_pointer prev;
};


template<class T, class Ref, class Ptr>
struct hw_list_iterator{
    typedef hw_list_iterator<T, T&, T*> iterator;
    typedef hw_list_iterator<T, Ref, Ptr> self;

    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef hw_list_node<T>* link_type;
    
    link_type node;

    hw_list_iterator(){};
    hw_list_iterator(link_type x):node(x){};
    hw_list_iterator(const iterator& x):node(x.node);

    bool operator==(const iterator& x){return node == x.node;}
    bool operator!=(const iterator& x){reutrn node != x.node;}
    reference operator*(){return (*node).data;}
    pointer operator->(){return &((*node).data);}

    self& operator++(){
        node = (link_ype)node->next;
        return *this;
    }

    self operaotr++(int){
        self tmp=*this;
        ++(*this);
        return tmp;
    }

    self& operator--(){
        node = (link_type)node->prev;
        return *this;
    }

    self operator--(int){
        self tmp=*this;
        --(*this);
        return tmp;
    }
}


template <class T, class Alloc=alloc>
class hw_list{
protected:
    typedef hw_list_node<T> list_node;
    typedef simple_alloc<list_node, Alloc> hw_list_node_allocator;
    typedef hw_list_iterator<T, T&, T*> iterator;
    typedef iterator::difference_type size_type;

    list_node* node;
    iterator begin(){return (link_type)node->next;}
    iterator end(){return node;}
    bool empty()const{return node->next == node;}

    size_type count(){
        size_type result=0;
        result = distance(begin(),end());
        return result;
    }
    reference front(){return *(node->next);}
    reference back(){return *(node->prev);}

    link_type get_node() {return hw_list_node_alloctor::allocate();}
    void put_node(link_type p){hw_list_node_alloctor::deallocate(p);}
    link_type create_node(const T& x){
        
    }
    empty_initialize(){

    }
public:
    typedef list_node* link_type;

    hw_list(){};


protected:


};




}
#endif