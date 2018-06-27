#include <hw_muduo/net/EventLoop.h>
#include <stdio.h>
void threadFunc(){
    printf("threadFunc() pid=%d ,tid=%d\n",getpid(),hw_muduo::CurrentThread::tid());
    hw_muduo::EventLoop loop;
    loop.loop();
}

int main(){
    printf("main():pid %d, tid=%d\n",getpid(),hw_muduo::CurrentThread::tid());

    hw_muduo::EventLoop loop;

    hw_muduo::Thread  (threadFunc);
    thread.start();
    loop.loop();
    pthread_exit(NULL);
    return 0;
}