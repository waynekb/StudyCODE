#include <iostream>

using namespace std;

class helper{
public:
    helper(){
        sum+=num;
        num++;
    }
    static void reset(){sum=0; num=1;}
    static unsigned int sum;
    static unsigned int num;
};

unsigned int helper::sum=0;
unsigned int helper::num=1;

class Solution {
public:
    int Sum_Solution(int n) {
        helper::reset();
        // helper* array=new helper[1];
        helper array[n];
        // delete[] array;
        return helper::sum;
    }
};

int main(){
    Solution sol;
    int a=sol.Sum_Solution(5);
    cout << a<< endl;
    int b=sol.Sum_Solution(2);
    cout << b<< endl;
    return 0;
}