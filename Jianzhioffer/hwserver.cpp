#include <iostream>
using namespace std;

#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
 


void server(){
    struct sockaddr_in myAddr;
    struct sockaddr_in cli_addr;
    int server_fd,client_fd;
    server_fd=socket(AF_INET, SOCK_STREAM,0);

    myAddr.sin_addr=AF_INET;
    myAddr.sin_port=htons(32632);
    myAddr.sin_addr.s_addr=htons(INADDR_ANY);
    bzero(&(myAddr.sin_zero), 8);
    bind(server_fd,(struct sockaddr*)(&myAddr), sizeof(sockaddr));
    listen(server_fd,10);
    int sc_len=sizeof(struct sockaddr_in);
    while(1){
        client_fd=accept(server_fd, (struct sockaddr*)&cli_addr,(socketlen_t* )&sc_len);
        
    }

}




void main(){
}