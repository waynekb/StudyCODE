#include <iostream>
#include <mutex>
#include <set>
#include <unistd.h>
#include <cstdio>
#include <thread>
using namespace std;


class Inventory{
public:
    void add(class Request* req){
        lock_guard<mutex> lock(_mutex);
        cout<<"add func"<<endl;
        requests_.insert(req);
    }
    void remove(class Request* req){
        lock_guard<mutex> lock(_mutex);
        cout<<"remove func"<<endl;
        requests_.erase(req);
    }

    void printall() const;

private:
    mutable mutex _mutex;
    set<class Request*> requests_;
};

Inventory g_inventory;

class Request{
public:
    Request(){cout<<"request construct"<<endl;}
        
    void process(){
        lock_guard<mutex> lock(_mutex);
        cout<<"process start"<<endl;
        g_inventory.add(this);
    }
    ~Request(){
        lock_guard<mutex> lock(_mutex);
        sleep(5);
        cout<<"request destruct "<<endl;
        g_inventory.remove(this);
    }
    void print(){
        lock_guard<mutex> lock(_mutex);
        cout<<"hello world"<<endl;
    }
private:
    mutable mutex _mutex;
};


void Inventory::printall()const{
    lock_guard<mutex> lock(_mutex);
    sleep(1);
    for(set<class Request*>::const_iterator it=requests_.begin();it!=requests_.end();it++){
        (*it)->print();
    }
    printf("Inventory::printall() unlock\n");
}


void threadFunc(){
    Request* req=new Request;
    req->process();
    delete req;
    cout<<"threadFunc end"<<endl;
}
int main(){
    cout<<getpid()<<endl;
    thread thread1(threadFunc);
    // thread1.start();
    sleep(1);
    g_inventory.printall();
    thread1.join();
}