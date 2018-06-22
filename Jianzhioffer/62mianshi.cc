#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <set>
using namespace std;

int main(){
    set<int> seta;
    vector<int> veca={14,3,8,6,4,17,2};
    for(auto &w:veca){
        seta.insert(w);
    }
    <<endl;
    return 0;
}