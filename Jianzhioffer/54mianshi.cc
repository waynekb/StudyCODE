#include <iostream>

using namespace std;

class Solution {
public:
    bool match(char* str,const char* pattern)
    {
        if (*str == '\0' && *pattern == '\0')
            return true;
        if (*str != '\0' && *pattern == '\0')
            return false;
        //if the next character in pattern is not '*'
        if (*(pattern+1) != '*')
        {
            if (*str == *pattern || (*str != '\0' && *pattern == '.'))
                return match(str+1, pattern+1);
            else
                return false;
        }
        //if the next character is '*'
        else
        {
            if (*str == *pattern || (*str != '\0' && *pattern == '.'))
                return match(str, pattern+2) || match(str+1, pattern);
            else
                return match(str, pattern+2);
        }
    }
};

int main(int argc, char** argv){
    if(argc!=3){
        cout<<"Please input right argument!!!!"<<endl;
        return 0;
    }
    Solution sol;
    bool res=sol.match(argv[1], "*");
    if(res)
        cout<< "match success!!"<<endl;
    else
        cout<< "match failure!!"<<endl;
    return 0;
}