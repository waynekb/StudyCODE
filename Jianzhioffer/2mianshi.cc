#include <iostream>
using namespace std;
class Singleton
{
public: 
    static Singleton* getinstance();
    void dosomething();
private:
    Singleton(int x=0);
    Singleton(const Singleton& other);
    Singleton& operator=(const Singleton& other);
    ~Singleton();

    static Singleton* instance;
    int _x;
};

Singleton* Singleton::instance=nullptr;


Singleton::Singleton(int x):_x(x){}
Singleton::Singleton(const Singleton& other){}
Singleton::~Singleton(){}
Singleton& Singleton::operator=(const Singleton& other){}

void Singleton::dosomething()
{
    cout<<"singleton value is "<<_x<<endl;
}

Singleton* Singleton::getinstance()
{
    if(instance == nullptr)
    {
        instance=new Singleton(326);
    }
    return instance;
}

int main()
{
    Singleton* test1= Singleton::getinstance();
    Singleton* test2= Singleton::getinstance();
    test1->dosomething();
    test2->dosomething();

    
    return 0;
}