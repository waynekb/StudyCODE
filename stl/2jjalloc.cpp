#include "2jjalloc.h"
#include <string.h>
#include <vector>
#include <iostream>

using namespace std;

int main(){
    int ia[5] ={0,1,2,3,4};
    unsigned int i;

    vector<int,JJ::allocator<int> > iv(ia,ia+5);

    for(i=0;i<iv.size();i++){
        cout <<iv[i]<<' ';
    }
    cout<<endl;

    char * ptr=JJ::_allocate((ptrdiff_t)10,(char*)0);
    strcpy(ptr,"hello");
    JJ::_construct(ptr+5,'w');
    cout<<ptr<<endl;

}

// g++ 2jjalloc.cpp -o 2jja -std=c++11