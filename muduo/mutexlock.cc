#include <thread>
#include <assert.h>
#include <sys/types.h>
#include <sys/syscall.h>

#include "mutexlock.h"

#include <unistd.h>

// #define gettid() syscall(__NR_gettid)

using namespace std;
using namespace muduo;

namespace muduo{
inline pid_t gettid(){
    return syscall(__NR_gettid);
}

}

MutexLock::MutexLock():holder(0)
{
    pthread_mutex_init(&_mutex, NULL);
}
MutexLock::~MutexLock()
{
    assert(holder == 0);
    pthread_mutex_destroy(&_mutex);
}
bool MutexLock::isLockedByThisThread()
{
    return holder == gettid();
}

void MutexLock::assertLocked()
{
    assert(isLockedByThisThread());
}
void MutexLock::lock()
{
    pthread_mutex_lock(&_mutex);
    holder = gettid();
}
void MutexLock::unlock()
{
    holder = 0;
    pthread_mutex_unlock(&_mutex);
}
pthread_mutex_t *MutexLock::getPthreadMutex()
{
    return &_mutex;
}


MutexLockGuard::MutexLockGuard(MutexLock &mutex):mutex_(mutex)
{
    mutex_.lock();
}

MutexLockGuard::~MutexLockGuard() { mutex_.unlock(); }

#define MutexLockGuard(x) static_assert(false,"missing mutex guard var name")


Condition::Condition(MutexLock& mutex):mutex_(mutex){
    pthread_cond_init(&pcond_,NULL);
}

Condition::~Condition(){}

void  Condition::wait(){
    pthread_cond_wait(&pcond_,mutex_.getPthreadMutex);
}

void Condition::notify(){
    pthread_cond_signal(&pcond_);
}

void Condition::notifyAll(){
    pthread_cond_broadcast(&pcond_);
}




int main(){
    MutexLock mutex;
    {
        MutexLockGuard lock(mutex);

    }

}



















// #include <pthread.h>
// #include <thread>
// #include <iostream>
// #include <unistd.h>
// #include <stdio.h>
// #include <string>
// #include <sys/syscall.h>  
// #define gettid() syscall(__NR_gettid)

// using namespace std;


// void thread1(string name){
//     cout<<"---------------"<<name<<endl;
//     cout<<"process id: "<<getpid()<<endl;
//     cout<<"kernel id: "<<gettid()<<endl;
//     cout<<"std thread id: "<< std::this_thread::get_id()<<endl;
//     cout<<"pthread id:"<< pthread_self()<<endl;
    
// }

// int main()
// {

//     thread thr1(thread1,"hello");
//     thread thr2(thread1,"world");
//     thread thr3(thread1,"china");

//     cout<<"----------main"<<endl;
//     cout<<"process id: "<<getpid()<<endl;
//     cout<<"kernel id: "<<gettid()<<endl;
//     cout<<"std thread id: "<< std::this_thread::get_id()<<endl;
//     cout<<"pthread id:"<< pthread_self()<<endl;
//     thr1.join();
//     thr2.join();
//     thr3.join();
//     return 0;
// }