
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int GetNumberOfK(vector<int> data ,int k) {
        if(data.size()==0)return 0;
        return binarysearch(data, 0, data.size(), (double)k+0.5) - binarysearch(data, 0, data.size(), (double)k-0.5);
    }
    int binarysearch(vector<int>& data, int begin, int end, double m){
        int low=begin;
        int high=end;
        if(begin==end)return begin;
        int mid = low+(high-low)/2;
        if(data[mid] < m )
            return binarysearch(data, ++mid, end, m);
        else
            return binarysearch(data, begin, mid, m);
    }
};


int main(){
    vector<int> array={1,2,3,4,4,4,4,4,6,6,6};
    Solution sol;
    int res=sol.GetNumberOfK(array, 6);
    cout << res<<endl;
}