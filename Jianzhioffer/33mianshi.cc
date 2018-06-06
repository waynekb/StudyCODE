#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct compare{
    bool operator()(int a, int b)
    {
        string astr = to_string(a) + to_string(b);
        string bstr = to_string(b) + to_string(a);
        return astr < bstr;
    }

};

class Solution
{
  public:
    string PrintMinNumber(vector<int> numbers) {
        int size=numbers.size();
        if(size == 0 )return "";
        string result;
        sort(numbers.begin(), numbers.end(), compare());
        for(auto &w:numbers){
            result+=to_string(w);
        }
        return result;
    }
    
}; 

int main(){
    // double num1=1433.45;
    // string res=to_string(num1);
    // cout<< res<<endl;

    vector<int> num={12,13,41,435,324,321,453};
    Solution sol;
    string res=sol.PrintMinNumber(num);
    cout<<res<<endl;
    return 0;
}

