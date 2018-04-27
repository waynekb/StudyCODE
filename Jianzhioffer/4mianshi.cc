#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

void Replace(char str[])
{
    int len=strlen(str);
    int p1=len;
    int p2=len;
    cout << "before replace \n"<<str<<endl;
    for(int i=0;i<len;i++)
    {
        if(str[i]==' ')
            p2+=2;
    }
    for(;p1>=0;p1--,p2--)
    {
        if(str[p1] != ' ')
        {
            str[p2]=str[p1];
        }
        else
        {
            str[p2--]='0';
            str[p2--]='2';
            str[p2]='%';
        }
    }
    cout << str<<endl;
}

int main(){
    char abc[100]={0};
    cin.getline(abc,100);
    Replace(abc);
    cout<< abc<<endl;
    cout<<"fix file"<<endl;
}