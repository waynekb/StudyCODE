#ifndef LOGING_H
#define LOGING_H

#include <iostream>
using std::cin
using std::cout
using std::endl;


#define LOG_TRACE cout<<__FILE__<<" "<<__LINE__<<" "
#define LOG_FATAL cerr<<__FILE__<<" "<<__LINE__<<" "
// class LOG_TRACE:public noncopyable{
//     LOG_TRACE()=default;
//     ~LOG
// };

#endif