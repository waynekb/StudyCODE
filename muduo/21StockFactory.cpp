
#include <iostream>
#include <memory>
#include <vector>
#include <mutex>
#include <map>
#include "21StockFactory.h"
using namespace std;


// class Stock{
// public:
//     Stock(const string& name,StockFactory* factory):_name(name),ptr(factory){};
//     ~Stock();
    
// private:
//     string _name;
//     StockFactory* ptr; 
// };

// Stock::~Stock(){
//     cout<<"Stock destruct"<<endl;
//     ptr->eraseItem(_name);
// }

// class StockFactory{
// public:
//     shared_ptr<Stock> get(const string& name);
//     void eraseItem(const string& name);
//     int getsize();
// private:
//     mutable mutex _mutex;
//     map<string,weak_ptr<Stock>> contain;
// };


void StockFactory::eraseItem(const string& name){
    contain.erase(name);
}

int StockFactory::getsize(){
    return contain.size();
}
shared_ptr<Stock> StockFactory::get(const string& name){
    shared_ptr<Stock> pStock;
    lock_guard<mutex> lock(_mutex);
    weak_ptr<Stock>& wptrStock=contain[name];
    pStock=wptrStock.lock();
    if(!pStock){
        pStock.reset(new Stock(name,shared_from_this()));
        wptrStock=pStock;
    }
    return pStock;
}



int main()
{
    shared_ptr<class StockFactory> contain(new StockFactory);
    {
    shared_ptr<Stock> test1=contain->get("UESTC");
    cout<< contain->getsize()<<endl;
    }
    cout<< contain->getsize()<<endl;

}