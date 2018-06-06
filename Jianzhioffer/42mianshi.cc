#include <string>
#include <iostream>

using namespace std;
void reverse(string& str){
    string tmpstr;
    int size=str.size();
    int low=0;
    int high=0;
    while(high < size){
        if(str[high]==' '){
            tmpstr=string(str.begin()+low, str.begin()+high)+tmpstr;
            tmpstr=" "+tmpstr;
            high++;
            low=high;
        }
        else{
            high++;
        }
    }
    if(high == size && low!=high)
        tmpstr=string(str.begin()+low, str.begin()+high)+tmpstr;
    cout << tmpstr<<endl;
}
int main(){
    string str="ab cde   fg ";
    reverse(str);
    return 0;
}