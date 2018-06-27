#ifndef _NONCOPYABLE_H
#define _NONCOPYABLE_H




class noncopyalbe{
public:
    noncopyalbe()=default;
    ~noncopyalbe()=default;
private:
    noncopyalbe(const noncopyalbe& )=delete;
    noncopyalbe& operator=(const noncopyalbe& )=delete;
};
#endif