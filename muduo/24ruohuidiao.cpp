#include <iostream>
#include <memory>
#include <vector>
#include <mutex>
#include <map>
using namespace std;

class Stock{
public:
    Stock(const string& name):_name(name){};
    Stock& operator=(const Stock& other){_name=other._name;return *this;}
    ~Stock(){cout<<"Stock destruct"<<endl;}
    string getname(){return _name;}
private:
    string _name;
};



class StockFactory:public enable_shared_from_this<class StockFactory>{
public:
    shared_ptr<Stock> get(const string& name);
    void eraseItem(const string& name);
    int getsize();
private:
    mutable mutex _mutex;
    map<string,weak_ptr<Stock>> contain;
};

void StockFactory::eraseItem(const string& name){
    cout<<"erase object "<<name<<endl;
    contain.erase(name);
}


int StockFactory::getsize(){
    return contain.size();
}
void DeleteStock(Stock* stock,weak_ptr<class StockFactory> wep){
    shared_ptr<class StockFactory>           shaptr;
    shaptr=wep.lock();
    if(shaptr){
        shaptr->eraseItem(stock->getname());
    }
    else{
        cout << "stockfactory has been destruct"<<endl;
    }
    delete(stock);
}

shared_ptr<class Stock> StockFactory::get(const string& name){
    shared_ptr<Stock> pStock;
    lock_guard<mutex> lock(_mutex);
    weak_ptr<Stock>& wptrStock=contain[name];
    pStock=wptrStock.lock();
    if(!pStock){
        pStock.reset(new Stock(name),std::bind(&DeleteStock,std::placeholders::_1, weak_ptr<class StockFactory>(shared_from_this())));
        wptrStock=pStock;
    }
    return pStock;
}


int main(){
    shared_ptr<class Stock> stock1;
    {
        shared_ptr<class StockFactory> factory(new StockFactory);
        stock1=factory->get("wayne");
        {
            shared_ptr<class Stock> stock2(factory->get("UESTC"));
            cout<<factory->getsize()<<endl;
        }
        cout<<factory->getsize()<<endl;
    }
}