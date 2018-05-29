#ifndef _HWSTL_TREE_H
#define _HWSTL_TREE_H

namespace hwstl{

typedef bool rb_tree_color_type;
const rb_tree_color_type tb_tree_red=false;
const rb_tree_color_type tb_tree_black=true;

struct hw_rb_tree_node_base
{
    typedef rb_tree_color_type color_type;
    typedef hw_rb_tree_node_base* base_ptr;

    color_type color;
    base_ptr lchild;
    base_ptr rchild;
    base_ptr parent;

    static base_ptr minimum(base_ptr x){
        while(x->lchild !=NULL) x=x->lchild;
        return x;
    }

    static base_ptr maximun(base_ptr x){
        while(x->rchild !=NULL) x=x->rchild;
        return x;
    }
};


template <class T>
struct hw_rb_tree_node : public hw_rb_tree_node_base{
    typedef hw_rb_tree_node<T>* link_type;
    T value_filed;
};

struct hw_rb_tree_base_iterator
{
    typedef hw_rb_tree_node_base::base_ptr base_ptr;
    typedef bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;

    base_ptr node;


    void increment(){
        if(node->rchild != 0){
            node=node->rchild;
            while(node->lchild !=0)
                node=node->lchild;
        }
        else{
            base_ptr y=node->parent;
            while(node == y->rchild){
                node = y;
                y= y->parent;
            }
            if(node ->rchild != y )
                node = y;
        }
    }

    void decrement(){
        if(node-colro == tb_tree_red && 
        node->parent->parent ==node){
            node =node ->rchild;
        }
        else if(node->lchild != 0){
            node=node->lchild;
            while(node->rchild !=0)
                node=node->rchild;
        }
        else{
            base_ptr y=node->parent;
            while(node == y->lchild){
                node = y;
                y= y->parent;
            }
            node = y;
        }
    }
};

template <class T, class Ref, class Ptr>
struct hw_rb_tree_iterator:public hw_rb_tree_base_iterator{
    typedef T value_type;
    typedef Ref reference;
    typedef Ptr pointer;
    typedef hw_rb_tree_iterator<T, T&, T*> iterator;
    typedef hw_rb_tree_iterator<T,const T&,const T*> const_iterator;
    typedef hw_rb_tree_iterator<T,Ref,Ptr> self;
    typedef hw_rb_tree_node<T>* link_type;

    hw_rb_tree_iterator(){}
    hw_rb_tree_iterator(link_type x):node(x){}
    hw_rb_tree_iterator(const iterator& it):node(it.node){}

    reference operator*(){return link_type(node)->value_filed;}
    self& operator++()const {increment();return *this;}
    self& operator++(int){
        self tmp=*this;
        increment();
        return tmp;
    }

    self& operator--()const {decream();return *this;}
    self& operator--(int){
        self tmp=*this;
        decrement();
        return tmp;
    }
};


template<class key, class value, class keyofvalue, class compare, class alloc=alloc>
class rb_tree{
protected:
    typedef void* void_pointer;
    typedef hw_rb_tree_node_base* base_ptr;
    typedef hw_rb_tree_node<value> rb_tree_node;
    typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator;
    typedef rb_tree_color_type color_type;

    typedef key key_value;
    typedef value value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef rb_tree_node* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    link_type get_node(){return rb_tree_node_allocator::allocate();}
    void put_node(link_type p){rb_tree_node_allocator::delallocate(p);}

    link_type create_node(const value_type& x){
        link_type tmp=get_node();
        construct(&tmp->value_filed,x);
        return tmp;
    }

    link_type clone_node(link_type x){
        link_type tmp=create_node(x->value_filed);
        tmp->color = x->color;
        tmp->lchild=0;
        tmp->rchild=0;
        return tmp;
    }

    void destroy_node(link_type p){
        destroy(&p->value_filed);
        put_node(p);
    }

protected:
    size_type node_count;
    link_type header;
    compare key_compare;

    link_type& root() const{return (link_type&) header->parent;}
    link_type& leftmost() const{return (link_type&) header->lchild;}
    link_type& rightmost() const{return (link_type&) header->rchild;}


    //以下六个函数用来方便取得节点x的成员
    static link_type& left(link_type x){
        return (link_type&)(x->lchild);
    }
    static link_type& right(link_type x){
        return (link_type&)(x->rchild);
    }
    static link_type& parent(link_type x){
        return (link_type&)(x->parent);
    }
    static reference value(link_type x){
        return x->value_filed;
    }
    static const key& key(link_type x){
        return keyofvalue()(value(x));
    }
    static color_type& color(link_type x){
        return (color_type&)(x->color);
    }

    //以下六个函数用来方便取得节点x的成员
    static link_type& left(base_ptr x){
        return (link_type&) (x->lchild);
    }
    static link_type& right(base_ptr x){
        return (link_type&) (x->rchild);
    }
    static link_type& parent(base_ptr x){
        return (link_type&) (x->parent);
    }
    static reference value(base_ptr x){
        return x->value_filed;
    }
    static const key& key(base_ptr x){
        return keyofvalue()(value(x));
    }
    static color_type& color(base_ptr x){
        return (color_type&)(x->color);
    }

    static link_type minimum(link_type x){
        return (link_type) hw_rb_tree_node_base::minimum(x);
    }

    static link_type maximun(link_type x){
        return (link_type) hw_rb_tree_node_base::maximun(x);
    }

public:
    typedef hw_rb_tree_iterator<value_type, reference, pointer> iterator;

private:
    iterator hw_insert(base_ptr x, base_ptr y, const value_type& v);
    link_type hw_copy(link_type x, link_type p);
    void hw_erase(link_type x);

    void init(){
        header = get_node();
        color(header)=tb_tree_red;
        root()=0;
        leftmost()=header;
        rightmost()=header;
    }

public:
    rb_tree(const compare& comp=compare()) :node_count(0), key_compare(comp){init();}
    ~rb_tree(){
        clear();
        put_node(header);
    }

    rb_tree<key,value, keyofvalue, compare, Alloc>& operator=(const rb_tree<key, value, keyofvalue, compare, Alloc>& x);

public:
    compare key_comp() const{reutnr key_compare;}
    iterator begin(){return leftmost();}    //rb树的起头为最左（最小）节点处
    iterator end(){return header;}
    bool empty() const{return node_count == 0;}
    size_type size() const {return node_count;}
    size_type max_size() const {return size_type(-1);}

};


inline void
hw_rb_tree_rebalance(hw_rb_tree_node_base* x, hw_rb_tree_node_base*& root) 
}


template<class key, class value, class keyofvalue, class compare, class Alloc>
typename rb_tree<key, value, keyofvalue, compare, Alloc>::iterator
rb_tree<key,value, keyofvalue, compare, Alloc>::insert_equal(const value& v){
    link_type y=header;
    link_type x=root();
    while(x!=0){
        y = x;
        x = key_compare(keyofvalue()(v), key(x)) ? left(x):right(x);
    }
    return __insert(x, y, v);
}

template<class key, class value, class keyofvalue, class compare, class Alloc>
pair<typename rb_tree<key, value, keyofvalue, compare, Alloc>::iterator,bool>
rb_tree<key, value, keyofvalue, compare, Alloc>::insert_unique(const value& v){
    link_type y= header;
    link_type x= root();
    bool comp=true;
    while(x!=0){
        y=x;
        comp = key_compare(keyofvalue()(v), key(x));
        x=comp? left(x):right(x);
    }

    iterator j=iterator(y);
    if(comp){
        if( j == begin() )
            return pair<iterator,bool>
        else --j;
        if(key_compare(key(j.node), keyofvalue()(v)))
            return pair<iterator,bool>(__insert(x,y,v),true);
        return pair<iterator, bool>(j, value);
    }
}


#endif