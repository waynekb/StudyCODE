
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> data={4,6,2,18,4,20,33,27,34};
    vector<int> data1(data);
    vector<int> data2(data.begin(), data.end());
    vector<int> data3(data.begin(), data.begin()+4);
    vector<int> data4(10);
    copy(data.begin()+3, data.begin()+7, data4.begin());
    for(auto &w:data1){
        cout<<w<<" ";
    }
    cout<<endl;

    for(auto &w:data2){
        cout<<w<<" ";
    }
    cout<<endl;

    for(auto &w:data3){
        cout<<w<<" ";
    }
    cout<<endl;  

    for(auto &w:data4){
        cout<<w<<" ";
    }
    cout<<endl; 
    cout<< *(data.begin()+4)<<"****" <<endl;
    return 0;
}