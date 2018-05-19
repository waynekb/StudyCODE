template<class T>
class auto_ptr{
public:
    explicit auto_ptr(T *p):pointer=p{}
    T& operator*()const {return *pointer;}
    T* operator->()const {return pointer;}
    T* get() const {return pointer;}

    template<class U>
    auto_ptr(const auto_ptr<U>& rhs):pointer:(rhs.release()){}

    template<class U>
    auto_ptr<T>& operator=(auto_ptr<U> rhs){
        if(this !=&rhs) reset(rhs.release());
        return *this;
    }
    ~auto_ptr(){delete pointer;}

private:
    T* pointer;
    
    T* release(){
        T* tmp=pointer;
        pointer=0;
        return tmp;
    }
    void reset()

};



