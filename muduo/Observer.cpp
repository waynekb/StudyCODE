#include <iostream>
#include <vector>
#include <memory>
#include <mutex>

using namespace std;
class Observer{
public:
    Observer(){};
    virtual ~Observer(){};
    virtual void update()=0;
};

class Observable{
public:
    void register_(weak_ptr<Observer> x);
    // void unregister(Observer* x);
    void notifyObservers();      
private:
    mutable mutex _mutex;
    vector<weak_ptr<Observer>> _observers;
    typedef vector<weak_ptr<Observer>>::iterator Iterator;
};  


void Observable::notifyObservers(){
        lock_guard<mutex> lock(_mutex);
        Iterator cur=_observers.begin();
        Iterator end=_observers.end();
        while(cur!=end){
            shared_ptr<Observer> obj(cur->lock());
            if(obj){
                obj->update();
                cur++;
            }
            else{
                cout<<"object has been destruct"<<endl;
                cur=_observers.erase(cur);
            }
        }
    }