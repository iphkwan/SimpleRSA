#ifndef UTILS_H
#define UTILS_H

#define debug 1

#include <iostream>
#include <cstdio>

#if debug
    #define LOGLN(msg) std::cout << msg << std::endl
    #define LOG(msg) std::cout << msg << flush
#else
    #define LOGLN(msg) 
    #define LOG(msg)

#endif

#endif
