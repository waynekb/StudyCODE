#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <hw_muduo/base/noncopyable.h>
#include <hw_muduo/base/Loging.h>


namespace hw_muduo{
namespace net{

class EventLoop:public noncopyalbe{
public:
    EventLoop();
    ~EeventLoop();

    void loop();
    void assertInLoopThread(){
        if(!isInLoopThread()){
            abortNotInLoopThread();
        }
    }

    bool isInLoopThread() const{return threadId == CurrentThread::tid();}

private:
    void abortNotInLoopThread();
    bool looping_;
    const pid_t threadId_;
};



}
}


#endif