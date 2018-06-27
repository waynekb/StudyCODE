
#include <hw_muduo/base/EventLoop.h>
#include <poll.h>
using namespace hw_muduo;
using namespace hw_muduo::net;

namespace{

__thread EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop()
    :looping_(false);thread_(CurrentThread::tid())
{
    LOG_TRACE<<"EventLoop created "<<this<<" in thread "<< threadId_;
    if(t_loopInThisThread){
        LOG_FATAL<<"Another EventLoop "<< t_loopInThisThread 
                <<"exits in this thread"<<threadId_<<endl;
    }
    else
    {
        t_loopInThisThread = this;
    }
}

EventLoop::~EeventLoop()
{
    assert(!looping_);
    t_loopInThisThread=NULL;
}

EventLoop* EventLoop::getEventLoopOfCurrentThread()
{
    return t_loopInThisThread;
}


void EeventLoop::loop()
{
    assert(!looping_);
    assertInLoopThread();
    looping_=true;
    ::poll(NULL, 0 , 5*1000);
    LOG_TRACE<<"EventLoop "<<this<<"stop looping";
    looping_=false;
}


}
