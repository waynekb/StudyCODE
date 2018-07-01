// #include <iostream>

// using namespace std;

// class foo{
// private:
//     int &a_;
// public:
//     foo(int &a):a_(a){}
//     ~foo()=default;
//     void print(){cout<<a_<<endl;}
// };

// int main(){
//     int b=10;
//     foo A(b);
//     A.print();
//     b=11;
//     A.print();
//     return 0;
// }

#include <iostream>
using namespace std;

class A{
private:
    int num_;
public:
    A()=default;
    A(int num):num_(num){}
    A(const A& a,int num=5):num_(num){cout<<"call func !"<<endl;}
    void print(){
        cout<<num_<<endl;
    }
};

int main(){
    A a(10);
    a.print();
    A b(a);
    b.print();
    // A::A(const A& a,int num=5);
    // A c(a);
    // c.print();
    return 0;

}