#ifndef MYCONVERSIONS_H_INCLUDED
#define MYCONVERSIONS_H_INCLUDED

#include <sstream>

template<class T>
std::string float2str(T n, std::streamsize no_digits, std::ios_base::fmtflags fmtfl){
    std::ostringstream oss;
    oss.flags(fmtfl);
    oss.precision(no_digits);
    oss << n;
    return oss.str();
}

template<class T>
std::string float2str(T n, std::streamsize no_digits){
    std::ostringstream oss;
    oss.precision(no_digits);
    oss << n;
    return oss.str();
}


template<class T>
T ato(const std::string& in){
    T ret;
    std::istringstream iss(in);
    iss >> ret;
    return ret;
}

#endif // MYCONVERSIONS_H_INCLUDED
