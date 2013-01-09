#ifndef UTILS_H
#define UTILS_H

#define debug 1

#if debug
    #define LOGLN(msg) std::cout << msg << std::endl
    #define LOG(msg) std::cout << msg
#else
    #define LOGLN(msg) 
    #define LOG(msg)

#endif

#endif
