#ifndef _STOCKFACTORY_H
#define _STOCKFACTORY_H


#include <memory>
#include <map>
#include <mutex>
#include "21Stock.h"
using namespace std;

class StockFactory:public enable_shared_from_this<StockFactory>{
public:
    shared_ptr<class Stock> get(const string& name);
    void eraseItem(const string& name);
    int getsize();
private:
    mutable mutex _mutex;
    map<string,weak_ptr<class Stock>> contain;
};

#endif