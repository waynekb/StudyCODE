#include <iostream>
using namespace std;

#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define PORT 23456
#define SOURCE_PORT 32631
#define MAXSIZE 2014

void client(){
    int client_fd;
    char send_buf[MAXSIZE]={0};
    char recv_buf[MAXSIZE]={0};

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port=htons(PORT);
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    if((client_fd=socket(AF_INET,SOCK_STREAM, 0)) == -1){
        cout<<"create socket fail"<<endl;
    }
    cout<<"create socket success client_fd="<<client_fd<<endl;

    if(connect(client_fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr))==-1){
        cout<<"connect fail"<<endl;
        return;
    }

    while(1){
        fgets(send_buf, sizeof(send_buf), stdin);
        send(client_fd,send_buf,strlen(send_buf),0);
        recv(client_fd,recv_buf,sizeof(recv_buf),0);
        if(strcmp(send_buf,"exit\n")==0)break;
        cout<<recv_buf<<endl;
        memset(recv_buf,0,sizeof(recv_buf));
        memset(send_buf,0,sizeof(send_buf));
    }
    close(client_fd);
    return;

}

int main(){

    cout<<"hello client"<<endl;
    client();
    return 0;
}