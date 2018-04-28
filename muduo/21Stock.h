#ifndef _STOCK_H
#define _STOCK_H

#include <string>
#include <map>
#include "21StockFactory.h"
#include <mutex>
using namespace std;

class Stock{
public:
    Stock(const string& name, shared_ptr<class StockFactory> factory):_name(name),ptr(factory){};
    ~Stock();
    
private:
    string _name;
    shared_ptr<class StockFactory> ptr; 
};



#endif