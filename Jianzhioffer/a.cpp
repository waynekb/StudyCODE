




#include <iostream>
#include <vector>
#include <map>
using namespace std



int solution(char *str){
    map<char,vector<char> > res;
    for(int i=0;i<10;i++){
        vector<char> tmp;
        res['0'+i]=tmp;
    }
    for(int i=0;i<24;i++){
        vector<char> tmp;
        res['a'+i]=tmp;
    }
    int size=strlen(str);
    for(int i=0;i<size;i++){
        res[str[i]].push_back(i);
    }

    int maxsubstr=0;

    for(i=0;i<10;i++){

    }
    
}


int solution(int n, int num[]){
    
}


int main(){

    return 0;
}