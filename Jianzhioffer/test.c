#include <stdlib.h>
#include <stdio.h>
#include <time.h>


// static void gettodaytime(char *todaytime){
//     time_t timep;
//     struct tm *local_time_p;

//     timep=time(NULL);
//     local_time_p = localtime(&timep);
//     todaytime[19]='a';
//     snprintf(todaytime, 20, "%d-%02d-%02d 00:00:00", local_time_p->tm_year + 1900, local_time_p->tm_mon + 1, local_time_p->tm_mday);
//     int i=0;
//     int sum=0;


// }

// int main(){
//     char time[20];
//     gettodaytime((char*)&time);
//     printf("%s\n",time);
// }


// void fun1(char* str,int count){
//     // int count=strlen(str);
//     int a[count];
//     int i=1;
//     for(;i<=count;i++){
//         a[i]=i;
//     }
//     for(i=1;i<=count;i++){
//         printf("%d ",a[i]);
//     }
//     printf("\n");
// }

// int main(){
//     char s[1024]={0};
//     scanf("%s",s);
//     fun1(s,strlen(s));
// }

