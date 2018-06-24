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
    fd_set read_set;
    int stdin_fd=fileno(stdin);
    while(1){
        int maxfd=-1;
        FD_ZERO(&read_set);
        FD_SET(stdin_fd,&read_set);
        maxfd=maxfd > stdin_fd ? maxfd:stdin_fd;
        FD_SET(client_fd,&read_set);
        maxfd=maxfd > client_fd ? maxfd:client_fd;
        int ret=select(maxfd+1,&read_set,NULL,NULL,NULL);
        if(FD_ISSET(stdin_fd,&read_set)){
            char send_buf[MAXSIZE]={0};
            fgets(send_buf, sizeof(send_buf), stdin);
            int read_len=strlen(send_buf);
            if(send_buf[read_len-1] == '\n')
                send_buf[read_len-1] = '\0';
            send(client_fd,send_buf,strlen(send_buf),0);    
        }
        if(FD_ISSET(client_fd,&read_set)){
            char recv_buf[MAXSIZE]={0};
            int read_len=read(client_fd,recv_buf,MAXSIZE-1);
            recv_buf[MAXSIZE-1];
            cout << "recv msg from server："<<recv_buf<<endl;
        }
    }
    close(client_fd);
    return;

}

int main(){

    cout<<"hello client"<<endl;
    client();
    return 0;
}