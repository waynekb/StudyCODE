#include <set>
#include <iostream>
#include <vector>

using namespace std;

int main(){
    multiset<int,greater<int> > res={1,2,5,8,9,3,3,1,12,55};
    for(auto &w:res){
        cout<<w<<" ";
    }
    cout<<endl;
    cout<<*(--res.end())<<endl;
    return 0;
}