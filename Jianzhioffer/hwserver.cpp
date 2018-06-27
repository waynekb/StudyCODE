#include <iostream>
using namespace std;

#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
// #include <errno.h>
#include <stdio.h>
 
#define MAXSIZE 1024
#define PORT 23456

void server(){
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int server_fd,client_fd;
    int addr_len=sizeof(struct sockaddr_in);
    bzero(&server_addr,addr_len);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(PORT);
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    if((server_fd=socket(AF_INET,SOCK_STREAM,0))<0){
        perror("create server_fd failed\n");
        return;
    }
    cout<<"create server_fd success server_fd="<<server_fd<<endl;

    if(bind(server_fd,(struct sockaddr*)&server_addr,addr_len) <0 ){
        perror("bind server_addr with server_fd failed\nddddd");
        return;
    }
    cout<<"bind server_fd success"<<endl;

    if(listen(server_fd,10)<0)
    {
        perror("listen failed");
        return;
    }
    cout<<"listen success"<<endl;

    while(1){
        int sin_len=addr_len;
        if((client_fd=accept(server_fd,(struct sockaddr*)&server_addr,(socklen_t*)&sin_len))<0){
            perror("accpet connection failed");
            return;
        }
        cout<<"accpet a new connection success"<<endl;
        cout<<"new client_fd="<<client_fd<<endl;
        char recv_buf[MAXSIZE]={0};
        while(1){
            int recv_len=recv(client_fd,recv_buf,MAXSIZE, 0);
            if(recv_len <=0)break;
            cout<<recv_buf<<endl;
            send(client_fd, recv_buf, recv_len, 0);
            memset(recv_buf,0,MAXSIZE);
        }
        close(client_fd);
    }
    close(server_fd);
    return;  
}




int main(){
    server();
    return 0;
}