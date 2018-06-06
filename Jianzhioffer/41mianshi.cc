#include <iostream>
#include <vector>
#include <set>
#include <math.h>
using namespace std;


class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum) {
        vector<vector<int> > result;
        set<vector<int>,cmp >contain;
        if(sum < 3)return result;
        for(int i=2; ;i++){
            if( i*i+i > 2*sum)
                break;
            
            double tmp=(double)sum/(double)i;
            double b;
            tmp=modf(tmp,&b);

            if( i&1 ){        //i是奇数
                if( (int)b*i== sum){        // sum除以i是整数
                    vector<int> subarry;
                    for(int j=sum/i-i/2; j<=sum/i+i/2; j++){
                        subarry.push_back(j);
                    }
                    contain.insert(subarry);
                }
            }
            else{    //i是偶数
                if(!(tmp<0.5 || tmp > 0.5)){
                    vector<int> subarry;
                    for(int j=sum/i-i/2+1; j<=sum/i+i/2; j++)
                        subarry.push_back(j);
                    contain.insert(subarry);
                }
            }
        }
        auto it=contain.begin();
        auto end=contain.end();
        while(it != end){
            result.push_back(*it);
            it++;
        }
        return result;
    }
    
struct cmp{
    bool operator()(vector<int> a, vector<int> b){
        return a[0] < b[0];
    }
};
};

int main(){
    Solution sol;
    vector<vector<int> > res=sol.FindContinuousSequence(100);
    for(auto &w: res){
        for(auto &t:w){
            cout<<t<<" ";
        }
        cout<<endl;
    }
    return 0;
}