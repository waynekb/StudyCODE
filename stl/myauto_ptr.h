#ifndef _MYAUTO_PTR_H
#define _MYAUTO_PTR_H



namespace mystl{
    
template<class T>
class myauto_ptr{
public:
    explicit myauto_ptr(T *p=0):pointer(p){}
    T& operator*()const {return *pointer;}
    T* operator->()const {return pointer;}
    T* get() const {return pointer;}

    template<class U>
    myauto_ptr(const myauto_ptr<U>& rhs):pointer(rhs.release()){}

    template<class U>
    myauto_ptr<T>& operator=(myauto_ptr<U>& rhs){
        if(this !=&rhs) reset(rhs.release());
        return *this;
    }
    ~myauto_ptr(){
        delete pointer;
    }

private:
    T* pointer;
    
    T* release(){
        T* tmp=pointer;
        pointer=0;
        return tmp;
    }

    void reset(T* rhs){
        delete pointer;
        pointer=rhs;
    }

};

}

#endif