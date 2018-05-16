#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char* nextline(char** ptr){
    char* p=strsep(ptr," ");
    while(p!=0 && *p == 0 ){
        p=strsep(ptr," ");
    }
    return p;
}

static void doline(char* line){
    int Pid;
    char* procname;
    char* tmp;
    float Cpu;
    float Mem;
    tmp=nextline(&line);
    if(tmp==0)return ;
    if(isdigit(tmp[0])){
        Pid=atoi(tmp);
        nextline(&line);
        nextline(&line);
        nextline(&line);
        nextline(&line);
        nextline(&line);
        nextline(&line);
        nextline(&line);
        tmp=nextline(&line);
        Cpu=atof(tmp);
        tmp=nextline(&line);
        Mem=atof(tmp);
        nextline(&line);
        tmp=nextline(&line);
        int size=strlen(tmp);
        if(tmp[size-1]=='\n'){
            tmp[size-1]=0;
        }
        printf("%-20s",tmp);
        printf("\t%5d",Pid);
        printf("\t%.1f",Cpu);
        printf("\t%.1f\n",Mem);
    }
    else if(tmp[0]=='t'){
        printf("\n\n\n\n");
    }
}

int main(){
    char buff[1024]={0};
    printf("Cmd                     Pid\t%%Cpu\t%%Mem\n");
    FILE* inptr=popen("top -b -d 5","r");
    if(inptr==NULL){
        printf("file open error\n");
    }
    while(1){
        fgets(buff,1024,inptr);
        doline(buff);
        memset(buff,0,1024);
    }
    fclose(inptr);
    pclose(inptr);
    return 0;
}
