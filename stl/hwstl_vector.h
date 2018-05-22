#ifndef _HWVECTOR_H
#define _HWVECTOR_H

namespace hwstl{}

template <class T, class Alloc =alloc>
class vector{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef T* iterator;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

protected:
    typedef simple_alloc<value_type,Alloc> data_allocator;
    iterator start;         //表示目前使用空间的头
    iterator finish;        //表示目前使用空间的尾
    iterator end_of_storage;    //表示目前可用空间的尾

    void insert_aux(iterator position, const T& x);
    void insert(iterator position, size_type n, const T& x);
    void deallocate(){
        if(start){
            data_allocator::deallocate(start, end_of_storage-start);
        }
    }

    iterator allocate_and_fill(size_type n,const T& x){
        iterator reasult = data_allocator::allocate(n);
        uninitialized_fill_n(result,n,x);
        return result;
    }

    void fill_initialize(size_type n, const T& value){
        start = allocate_and_fill(n, value);
        finish = start + n;
        end_of_storage = finish;
    }



public:
    iterator begin(){return start;}
    iterator end(){return finish;}
    size_type size()const {return size_type(end() - begin());}
    size_type capacity() const{ return size_type(end_of_storage - begin()); }
    bool empty()const {return begin()== end();}
    reference operator[](size_type n) {return *(begin() + n);}


    vector():start(0),end(0),end_of_storage(0){}
    vector(size_type n,const T& value){fill_initialize(n,value);}
    vector(int n,const T& value){fill_initialize(n,value);}
    vector(long n, const T& value){fill_initialize(n,value);}
    explicit vector(size_type n){fill_initialize(n,T());}


    ~vecotr(){
        destroy(start,finish);
        deallocate();
    }

    reference front() {return *begin();}
    reference back(){return *end();}
    void push_back(const T& x){
        if(finish!=end_of_storage){
            construct(finish,x);
            finish++;
        }
        else 
            insert_aux(end(),x);
    }

    void pop_back(){
        --finish;
        destroy(finish);
    }

    iterator erase(iterator position){
        if(position +1 != end())
            copy(position + 1, finish, position);
        --finish;
        destroy(finish);
        return position;
    }

    iterator erase(iterator first, itearator last){
        iterator i = copy(last, finish, first);
        destroy(i,finish);
        finish = finish - (last - first);
        return first;
    }


    void resize(size_type new_size,const T& x){
        if(new_size < size())
            erase( begin() + new_size, end());
        else 
            insert(end(), new_size-size());
    }
    void resize(size_type new_size){resize(new_size, T());}
    void clear(){rease(begin(),end());}

protected:

};


/***
 * 
 * 插入一个元素
 * **/
template<class T, class Alloc>
void vector<T,Alloc>::insert_aux(iterator position, const T&x){
    if(finish != end_of_storage){
        construct(finish, *(finish -1));
        ++finish;
        T x_copy =x;
        copy_backward(position, finish -2 ,finish -1);
        *position = x_copy;
    }
    else{
        const size_type old_size = size();
        const size_Type len = old_size != 0?:2*lod_size:1;

        iterator new_start=data_allocator::allocate(len);
        iterator new_finish = new_start;
        try{
            new_finish = uninitialized_copy (start, position , new_start);
            construct(new_finish, x);
            ++new_finish;
            new_finish = uninitialized_copy(position, finish, new_finish);
        }
        catch(...)
        {
            destroy(new_start, new_finish);
            data_allocator::deallocate(new_start, len);
            throw;
        }

        destroy(begin(), end());
        deallocate();

        start =new_start;
        finish =new_finish;
        end_of_storage =new_start+len;
    }
}


/***
 * 插入多个元素
 * 
 * 
 * **/


 template<class T， class Alloc>
 void vector<T, Alloc>::insert(iterator position, size_type n, const T& x){
     if(n == 0 ) return;
     if(size_type(end_of_storage - finish) >= n){
        T x_copy = x;
        size_type element_count = finish-position;
        iterator old_finish=finish;
        finish=finish+n;
        if(element_count < n){
            uninitialized_fill_n(finish, n - element_count, x_copy);
            finish+=n-element_count;
            uninitialized_copy(position, old_finish, finish);
            finish+=element_count;
            fill(position, old_finish, x_copy);
        }
        else{
            uninitialized_copy(finish-n,finish, finish);
            finish +=n;
            copy_backward(position, old_finish-n, old_finish);
            fill(position, position+n , x_copy);
        }
     }
     else{
        const size_type old_size=size();
        const size_type len = 2*(max(old_size,n));
        iterator new_start = data_allocator::allocate(len);
        iterator new_finish ;
        new_finish=uninitialized_copy(start,position, new_start);
        new_finish=uninitialized_fill_n(new_finish, n , x_copy);
        new_finish=uninitialized_copy(position,finish, new_finish);

        destroy(start,finish);
        deallocate();

        start=new_satrt;
        finish=new_finishl;
        end_of_storage=start+len;
     }
 }

#endif


