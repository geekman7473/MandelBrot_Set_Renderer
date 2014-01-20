#ifndef UTIL_c
#define UTIL_c

#include "Util.hpp"
#include <string>
#include <sstream>

std::string intToString(long long int val){
    std::stringstream ss;
    ss << val;
    return  ss.str();
}
std::string doubleToString(long double val){
    std::stringstream ss;
    ss << val;
    return  ss.str();
}
#endif
