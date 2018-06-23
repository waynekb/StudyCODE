// #include "foo.h"

// int main(){
//     foo();
// }


#include <stdio.h>

int main(){
    union rec{
        char buf[4];
        int a;
    };

    union rec r;
    r.a=0x12345678;
    r.buf[1]=0x32;
    printf("%x\n",r.a);
}