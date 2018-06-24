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


/**
 * 多线程服务器
 * 多线程服务器
 * 多线程服务器
 * **/
void server1(){
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
        if((client_fd=accept(server_fd,(struct sockaddr*)&client_addr,(socklen_t*)&sin_len))<0){
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





class SocketList{
    private:
    int num;//记录socket的真实数目
    int socketArry[FD_SETSIZE];
    int maxfd;
    
    public:
    int getSocket(int i){
        return socketArry[i];
    }
    SocketList(){
        num=0;
        for(int i=0; i<FD_SETSIZE; i++){
            socketArry[i]=-1;
        }
    }

    void insertSocket(int fd){
        socketArry[num]=fd;
        num++;
    }

    void deleteSocket(int fd){
        for(int i=0; i<FD_SETSIZE; i++){
            if(socketArry[i]==fd){
                socketArry[i]=socketArry[num-1];
                socketArry[num-1]=-1;
                num--;
                break;
            }
        }
    }

    int makefd(fd_set* fd_list){
        FD_ZERO(fd_list);
        maxfd=-1;
        for(int i=0;i<FD_SETSIZE;i++){
            if(socketArry[i]>=0){
                FD_SET(socketArry[i],fd_list);
                if(socketArry[i]>maxfd)
                    maxfd=socketArry[i];
            }
            else break;
        }
        return maxfd+1;
    }
    int getfdnums(){
        return num;
    }
};






void server(){
    struct sockaddr_in server_addr;
    int server_fd;
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
        perror("bind server_addr with server_fd failed\n");
        return;
    }
    cout<<"bind server_fd success"<<endl;

    if(listen(server_fd,10)<0)
    {
        perror("listen failed");
        return;
    }
    cout<<"listen success"<<endl;
    cout<<"server start working"<<endl;

    fd_set write_set;
    fd_set read_set;
    SocketList socklist;
    socklist.insertSocket(server_fd);
    int stdin_fd=fileno(stdin);
    socklist.insertSocket(stdin_fd);
    while(1){
        int maxfd=socklist.makefd(&read_set);
        int ret=select(maxfd,&read_set,NULL,NULL,NULL);

        if(ret == 0)continue;
        else if(ret <0 ){
            perror("select error\n");
            return ;
        }
        if (FD_ISSET(server_fd, &read_set))
        { //有新的socket连接
            struct sockaddr_in client_addr;
            memset(&client_addr, 0, sizeof(client_addr));
            int addr_len = sizeof(sockaddr_in);
            int client_fd;
            if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&addr_len)) < 0)
            {
                perror("accpet connection failed\n");
                continue;
            }
            socklist.insertSocket(client_fd);
            cout << "new connection client addr is:" << inet_ntoa(client_addr.sin_addr) << " port:" << client_addr.sin_port << endl;
            cout << "new client_fd=" << client_fd << endl;
        }
        if(FD_ISSET(stdin_fd, &read_set))
        {
            char read_buf[MAXSIZE] = {0};
            int read_len = read(stdin_fd, read_buf, MAXSIZE - 1);
            // recv(stdin_fd,read_buf,MAXSIZE-1,0)
            if(read_buf[read_len-1] == '\n')
                read_buf[read_len-1] = '\0';
            read_buf[MAXSIZE - 1] = '\0';
            int fd_num = socklist.getfdnums();
            for(int i = 0; i < fd_num; i++)
            {
                int fd = socklist.getSocket(i);
                if (fd == server_fd || fd == stdin_fd)
                    continue;
                int write_len = write(fd, read_buf, read_len);
                if (write_len < read_len)
                {
                    perror("send data no complete\n");
                }
            }
        }
        int fd_num=socklist.getfdnums();
        for(int i=0;i<fd_num;i++)
        {
            int fd=socklist.getSocket(i);
            if(fd != server_fd && fd != stdin_fd){
                if(FD_ISSET(fd,&read_set)){
                    char recv_buf[MAXSIZE]={0};
                    int read_len=read(fd,recv_buf,MAXSIZE-1);
                    if(read_len < 0 ){
                        cout<<"read socket error\n"<<endl;
                        close(fd);
                        socklist.deleteSocket(fd);
                    }
                    else if(read_len > 0){
                        recv_buf[MAXSIZE-1]='\0';
                        cout << "recerv from client msg:" << recv_buf << endl;
                    }
                }
            }
        }
    }
    close(server_fd);
    return;  
}


int main(){
    server();
    return 0;
}