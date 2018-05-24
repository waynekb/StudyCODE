#ifndef HWSTL_PRIORITY_QUEUE_H
#define HWSTL_PRIORITY_QUEUE_H


namespace hwstl{

template <class T, class sequence = vector<T>,class compare = less<typename sequence::value_type> >
class priority_queue{
public:
    typedef typename sequence::value_type value_type;
    typedef typename sequence::size_type size_type;
    typedef typename sequence::reference reference;
    typedef typename sequence::const_reference const_reference;

protected:
    priority_queue():c(){}
    explicit priority_queue(const compare& x):c(),comp(x){}

    template <class InputIterator>
    priority_queue(InputIterator first, InputIterator last,const compare& x)
    :c(first,last),comp(x){make_heap(c.begin(), c.end(), comp);}

    template<class InputIterator>
    priority_queue(InputIterator first, InputIterator last)
    :c(first,last){make_heap(c.begin(), c.end(), comp);}

    bool empty()const{return c.empty();}
    size_type size()const{return c.size();}

    const_reference top()const {return c.front();}

    void push(const value_type& x){
        c.push_back(x);
        push_heap(c.begin(), c.end());
    }

    void pop(){
        pop_heap(c.begin(), c.end(),comp);
        c.pop_back();
    }
};


}

#endif