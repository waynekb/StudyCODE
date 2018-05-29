#ifndef HWSTL_HASHTABLE_H
#define HWSTL_HASHTABLE_H

namespace hwstl{

template<calss value>
struct hw_hashtable_node{
    hw_hashtable_bode* next;
    value val;
};

template<class value, class key, class hashfcn, class extractkey, class equalkey, class Alloc>
struct hw_hashtable_iterator{
    typedef hashtable<value, key, hashfcn, extractkey, equalkey, Alloc> hashtable_iterator;
    typedef hw_hashtable_node<value> node;

    typedef forward_iterator_tag iterator_category;
    typedef value value_type;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef value& reference;
    typedef value* pointer;

    node* cur;
    hashtable* ht;

    hw_hashtable_iterator(){}
    hw_hashtable_iterator(node* n, hashtable* tab):cur(n), ht(tab){}

    reference operator*() const{return cur->val;}
    pointer operator->() const{return &(operator*());}
    iterator& operator++();
    iterator operator++(int);
    bool operator==(const iterator& it) const{return cur==it.cur;}
    bool operator!=(const iterator& it) const{return cur!=it.cur;}
};

template <class v, class k, class hf, class exk, class eqk, class a>
hw_hashtable_iterator<v, k, hf, exk, eqk, a>& 
hw_hashtable_iterator<v,k, hf, exk, eqk, a>::operator++(){
    const node* old=cur;
    cur=old->next;
    if(!cur){
        size_type bucket =ht->bkt_num(old->val);
        while(!cur && ++bucket < ht->bucket.size())
            cur=ht->buckets[bucket];
    }
    return *this;
}

hw_hashtable_iterator<v, k, hf, exk, eqk, a>& 
hw_hashtable_iterator<v,k, hf, exk, eqk, a>::operator++(int){
    iterator tmp=*this;
    ++*this;
    return tmp;  
}

template <class value, class key, class hashfcn, class extractkey, class equalkey, class Alloc>
class hashtable{
public:
    typedef hashfcn hasher;
    typedef equalkey key_equal;
    typedef size_t size_type;

private:
    hasher hash;
    key_equal equals;
    extractkey get_key;

    typedef hw_hashtable_node<value> node;
    typedef simple_alloc<node, Alloc> node_allocator;

    vector<node*, Alloc> buckets;
    size_type num_elements;

public:
    size_type bucket_coount() const{return buckets.size();}

    hashtable(size_type n, const hashfcn& hf, const equalkey& eql)
    :hash(hf), equals(eql), get_key(extractkey(), num_enements(0)){initialize_buckets(n);}

    void initialize_buckets(size_type n){
        const size_type n_buckets = next_size(n);
        buckets.reserve(n_buckets);
        buckets.insert(bucket.end(), n_buckets, (node*)0);
        num_elements=0;
    }

    pair<iterator,bool> insert_unique(const value_type& obj){
        resize(num_elements+1);
        return insert_unique_noresize(obj);
    }

    template 

};

}

#endif