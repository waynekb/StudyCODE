#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

class CMyString
{
public:
    CMyString(char* pData =NULL);
    CMyString(const CMyString& str);
    CMyString& operator=(const CMyString& str);
    void print();
    ~CMyString(void);

private:
    char* m_pData;
};

CMyString& CMyString::operator=(const CMyString& str){
    if(this==&str)return *this;
    char* tmp=new char[strlen(str.m_pData)+1];
    strcpy(tmp,str.m_pData);
    delete []m_pData;
    m_pData=tmp;
    return *this;
}

CMyString::CMyString(char* pData)
{
    if(pData==nullptr){
        m_pData=new char[1];
        m_pData[0]='\0';
    }
    else{
    m_pData=new char[strlen(pData)+1];
    strcpy(m_pData,pData);
    }
}

CMyString::~CMyString(void){};

CMyString::CMyString(const CMyString& str)
{
    m_pData=new char[strlen(str.m_pData)+1];
    strcpy(m_pData,str.m_pData);
}

void CMyString::print()
{
    cout<<m_pData<<endl;
}
// int main(int argc,char** argv){
//     // char* str1=new char[10]();
//     // char* str2=new char[10]();
//     char str1[]="abcdefg";
//     char str2[]="1234567";
//     {
//         CMyString cmstr1(str1);
//         CMyString cmstr2(str2);
//         cmstr1.print();
//         cmstr2.print();
//         cmstr2 = cmstr1;
//         cmstr2.print();
//     }
//     return 0;
// }


void Test1()
{
    printf("Test1 begins:\n");

    char* text = "Hello world";

    CMyString str1(text);
    CMyString str2;
    str2 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str2.print();
    printf(".\n");
}

// 赋值给自己
void Test2()
{
    printf("Test2 begins:\n");

    char* text = "Hello world";

    CMyString str1(text);
    str1 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str1.print();
    printf(".\n");
}

// 连续赋值
void Test3()
{
    printf("Test3 begins:\n");

    char* text = "Hello world";

    CMyString str1(text);
    CMyString str2, str3;
    str3 = str2 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str2.print();
    printf(".\n");

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str3.print();
    printf(".\n");
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();

    return 0;
}