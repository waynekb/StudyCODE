#ifndef _HWAUTO_PTR_H
#define _HWAUTO_PTR_H



namespace hwstl{
    
template<class T>
class hwauto_ptr{
public:
    explicit hwauto_ptr(T *p=0):pointer(p){}
    T& operator*()const {return *pointer;}
    T* operator->()const {return pointer;}
    T* get() const {return pointer;}

    template<class U>
    hwauto_ptr(const hwauto_ptr<U>& rhs):pointer(rhs.release()){}

    template<class U>
    hwauto_ptr<T>& operator=(hwauto_ptr<U>& rhs){
        if(this !=&rhs) reset(rhs.release());
        return *this;
    }
    ~hwauto_ptr(){
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