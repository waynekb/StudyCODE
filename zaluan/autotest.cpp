#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;

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
        if(pointer!=NULL){
            cout<<*pointer<<endl;
        }
        printf("%p\n",pointer);
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

int main(){
    {
        //  mystl::myauto_ptr<int> d(new int(5));
         mystl::myauto_ptr<int> d;
    }
    mystl::myauto_ptr<int> a(new int(4));
    mystl::myauto_ptr<string> b(new string("i love cl"));
    mystl::myauto_ptr<string> c;
    // cout<<*a<<endl;
    // cout<<*b<<endl;
    c=b;
    cout << " "<<endl;
    // cout<<*a<<endl;
}


// #include <iostream>
// #include <string>
// #include <memory>

// using namespace std;

// int main(){
//     auto_ptr<int> a(new int (4));
//     auto_ptr<string> b(new string ("i love cl"));
//     auto_ptr<string> c;
//     cout<<*a<<endl;
//     cout<<*b<<endl;
//     a=b;
//     cout<<*a<<endl;
//     return 0;
// }