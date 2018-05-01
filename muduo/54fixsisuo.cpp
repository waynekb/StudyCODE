#include <iostream>
#include <mutex>
#include <set>
#include <unistd.h>
#include <cstdio>
#include <thread>
using namespace std;


/***
 * 方法一：复制request_副本 通过副本来访问request
 * **/

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

void Inventory::printall()const{
    set<class Request*> tmp;
    {
        lock_guard<mutex> lock(_mutex);
        tmp=register_;
    }
    for(set<class Request*>::const_iterator it=requests_.begin();it!=requests_.end();it++){
        (*it)->print();
    }
    printf("Inventory::printall() unlock\n");
}

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



/**
 * 方法二 使用shared_ptr管理std set
 * ***/


 class Inventory{
public:
    void add(class Request* req){
        lock_guard<mutex> lock(_mutex);
        if(!requests_.unique()){
            requests_.reset(new set<class Request*>(*register_));
        }
        cout<<"add func"<<endl;
        assert(requests_.unique());
        requests_.insert(req);
    }
    void remove(class Request* req){
        lock_guard<mutex> lock(_mutex);
        if(!requests_.unique()){
            requests_.reset(new set<class Request*>(*register_));
        }
        assert(requests_.unique());
        cout<<"remove func"<<endl;
        requests_.erase(req);
    }
    
    void printall() const;
    
private:
    mutable mutex _mutex;
    shared_ptr<set<class Request*>> requests_;
};

void Inventory::printall()const{
    shared_ptr<set<class Request*>> tmp;
    {
        lock_guard<mutex> lock(_mutex);
        tmp=requests_;
    }
    for(set<class Request*>::const_iterator it=tmp->requests_.begin();it!=tmp->requests_.end();it++){
        (*it)->print();
    }
    printf("Inventory::printall() unlock\n");
}

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
