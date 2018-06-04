#include <iostream>
#include <vector>
#include <bits/stl_iterator.h>
#include <string>
#include <algorithm>
using namespace std;


class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        int size=input.size();
        if(size <= k) return input;
        vector<int> result(input.begin(), input.begin()+k);
        vector<int>::iterator beg=result.begin();
        vector<int>::iterator end=result.end();
        make_heap(beg, end);
        
        for(int i=k; i<size; i++){
            if(input[i]< result[0]){
                pop_heap(beg, end);
                result[k-1]=input[i];
                push_heap(beg, end);
            }
        }
        return result;
        
    }
};


int main(){
    Solution sol;
    vector<int> array={1,5,6,23,4,76,9,55,49,87,42,13,16,25};
    vector<int> res=sol.GetLeastNumbers_Solution(array,-1);
    for(auto &w: res){
        cout<< w <<" ";
    }
    cout<<endl;
    return 0;
}

// int main(){
//     vector<int> array={1,5,7,9,3,0,10,13,4,15};
//     vector<int>::iterator begin=array.begin();
//     vector<int>::iterator end=array.end();
//     make_heap(begin, end);
//     // pop_back(begin,end);
//     for(auto &w: array){
//         cout<< w <<" ";
//     }
//     cout<<endl;

//     array.push_back(65);
//     push_heap(array.begin(),array.end());
//     for(auto &w: array){
//         cout<< w <<" ";
//     }
//     cout<<endl;

//     pop_heap(array.begin(),array.end());
//     for(auto &w: array){
//         cout<< w <<" ";
//     }
//     cout<<endl; 

//     vector<int> aar(array.begin(),array.begin()+4);  
//     for(auto &w: aar){
//         cout<< w <<" ";
//     }
//     cout<<endl; 
//     return 0;

// }