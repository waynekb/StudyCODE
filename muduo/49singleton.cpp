#include "mutexlock.h"
#include <string>
#include <iostream>
using namespace std;

template<typename T>
class Singleton:public muduo::noncopyable{
public:
    static T& instance(){
        pthread_once(&ponce_, &Singleton::init);
        return *value_;
    }
private:
    Singleton();
    ~Singleton();
    static void init(){
        value_=new T();
    }

    static pthread_once_t ponce_;
    static T* value_;
};



template<typename T>
pthread_once_t Singleton<T>::ponce_=PTHREAD_ONCE_INIT; 


template<typename T>
T* Singleton<T>::value_=NULL;

class foo{
public:
    foo():value(0),name("wayne"){}
    void print(){
        cout<<"name "<<name<<"  age "<<value<<endl;
    }
    void setfoo(int v,string n){
        value=v;
        name=n;
    }
private:
    int value;
    string name;
};

int main(){
    foo& f=Singleton<foo>::instance();
    f.print();
    foo& t=Singleton<foo>::instance();
    t.print();
    f.setfoo(10,"uestc");
    f.print();
    t.print();
}