#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

const int MB=0;
const int KB=1;
float number(float a){
    int unit=KB;
    if(a>1024){
        a=a/1024;
        unit=MB;
    }
    // int tmp=(int)((a+0.0005)*1000);
    // float tmp1=tmp/1;
    // float res=tmp1/1000;
    float res;
    char str[20]={0};
    sprintf(str,"%.3f",a);
    res=atof(str);
    return res;
}

int main(){
    float a;
    scanf("%f",&a);
    a=number(a);
    printf("%f",a);
    return 0;
}