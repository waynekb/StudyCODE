#include <iostream>
#include <math.h>
using namespace std;
class Solution {
public:
    int Add(int num1, int num2)
    {
        if(num1 <0 && num2 <0){
            string str1(-num1,'a');
            str1.append(-num2,'a');
            return -str1.size();
        }
        else if(num1 >=0 && num2>=0){
            string str1(num1,'a');
            str1.append(num2,'a');
            return str1.size();
        }
        else{
            int tmp1=abs(num1)<abs(num2)?abs(num1):abs(num2);
            int tmp2=abs(num1)>abs(num2)?abs(num1):abs(num2);
            string str1(tmp2,'a');
            if(tmp1==0)return -str1.size();
            str1.erase(0,tmp1);
            if(tmp1 <0 ){
                return str1.size();
            }
            else{
                return -str1.size();
            }
        }
    }
};

int main(){
    Solution sol;
    cout<<sol.Add(0,-4)<<endl;
}