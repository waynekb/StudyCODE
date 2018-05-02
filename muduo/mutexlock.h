#ifndef _MUTEXLOCK_H
#define _MUTEXLOCK_H


#include <thread>
// #include <assert.h>
// #include <sys/type.h>

namespace muduo{

class noncopyable{
protected:
    noncopyable()=default;
    ~noncopyable()=default;
private:
    noncopyable(const noncopyable& );
    noncopyable& operator=(const noncopyable&);
};

class MutexLock:public noncopyable{
public:
    MutexLock();
    ~MutexLock();
    bool isLockedByThisThread();
    void assertLocked();
    void lock();
    void unlock();
    pthread_mutex_t* getPthreadMutex();

private:
    pthread_mutex_t _mutex;
    pid_t holder;
};


class MutexLockGuard:public noncopyable{
public:
    MutexLockGuard(MutexLock& mutex);
    ~MutexLockGuard();
private:
    MutexLock& mutex_;
};

pid_t gettid(); 

class Condition :public noncopyable{
public:
    explicit Condition(MutexLock& mutex);
    ~Condition ();
    void wait();
    void notify();
    void notifyAll();
private:
    MutexLock& mutex_;
    pthread_cond_t pcond_;
};


}
#endif