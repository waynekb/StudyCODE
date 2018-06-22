#include <iostream>

using namespace std;

class temp{
public:
    temp(int num):val(num){};
    // temp(const temp& x):val(x.val){};
    operator
    ~temp(){};
    void print(){cout<<val<<endl;}
private:
    int val;
};

int main(){
    class temp a(10);
    a.print();
    class temp b(a);
    b.print();
    class temp c(3);
    c.print();
    c=a;
    c.print();
    // class temp c(10);
    // c.print();
    return 0;
}