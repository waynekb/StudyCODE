#include <iostream>
#include <stdlib>
#include <mutex>
#include <vector>
#include <memory>
using namespace std;

class Foo{
public:
    Foo(int a):value(a){}
private:
    int value;
};

typedef vector<Foo> FooList;
typedef shared_ptr<FooList> FooListPtr;
mutex mtx;
FooListPtr g_foos;

void traverse(){
    FooListPtr foos;
    {
        lock_guard lock(mtx);
        foos=g_foos;
        assert(!g_foos.unique());
    }
    for(vector<Foo>::Iterator it=foos->begin();it!=foos->end();it++)
    {
        it->doit();
    }
}

void post(const Foo& f)
{
    printf("post \n");
    lock_guard lock(mtx);
    if(!g_foos.unique()){
        g_foos.reset(new FooList(*g_foos));//*g_foos 是vector动态数组，这里采用了拷贝构造
        printf("copy the whole list\n");
    }
    assert(g_foos.unique());
    g_foos->push_back(f);
}