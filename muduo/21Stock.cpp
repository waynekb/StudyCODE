#include "21Stock.h"
#include <iostream>


using namespace std;
Stock::~Stock(){
    cout<<"Stock destruct"<<endl;
    ptr->eraseItem(_name);
}