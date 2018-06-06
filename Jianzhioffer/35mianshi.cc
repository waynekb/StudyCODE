#include <map>
#include <iostream>
#include <set>
#include <string.h>
#include <stdlib.h>

using namespace std;


class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        map<char,int> contain;
        map<char,int>::iterator it;
        for(auto &w:str){
            it=contain.find(w);
            if(it==contain.end())
                contain.insert(pair<char,int>(w,1));
            else
                contain[w]++;
        }
        int size=contain.size();
        it=contain.begin();
        for(int i=0; i<size; i++,it++){
            if((*it).second==1)return i;
        }
        return 0;
        
    }
};


struct testnode{
    int a;
    char* name;
};

testnode array11[10]={0};

testnode func(){
    return array11[0];
}
int main(){
    // string str("google");
    // Solution sol;
    // int res=sol.FirstNotRepeatingChar(str);
    // cout<<res<<endl;

    // set<int> cont;
    // cont.insert(4);
    // cont.insert(5);
    // cont.insert(1);
    // cont.insert(3);

    // testnode array[10]={0};
    // const char* cons="abcdefgsgsdg";
    // char* testarry=(char*)malloc(10);
    // strncpy(testarry,cons,9);
    // *(testarry+10)=0;
    // cout<<testarry<<endl;
    // *(testarry+8)='d';
    // cout<<testarry<<endl;
    // cout<<*(testarry+3)<<endl;

    char* name="abcdefg";
    array11[0].a=10;
    array11[0].name=name;

    testnode test=func();

    cout << test.a<<endl;
    cout << test.name<<endl;
}