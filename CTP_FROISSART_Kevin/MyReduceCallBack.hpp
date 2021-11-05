#ifndef MYREDUCECALLBACK_HPP
#define MYREDUCECALLBACK_HPP
#include <iostream>
#include "MyPair.hpp"
#include "MyEnum.hpp"

#define DEFAULT_INCR 1

class MyReduceCallback {
private:
    int incr;
public:
    MyReduceCallback() : incr(DEFAULT_INCR) {
        //std::cout << "MyReduceCallback()" << std::endl;
    }
    MyReduceCallback(const int &incr) : incr(incr) {
        //std::cout << "MyReduceCallback(const int &incr)" << std::endl;
    }
    MyReduceCallback(const MyReduceCallback &that) {
        //std::cout << "MyReduceCallback(const MyReduceCallback &that)" << std::endl;
        *this = that;
    }
    virtual ~MyReduceCallback() {
        //std::cout << "~MyReduceCallback()" << std::endl;
    }
    MyReduceCallback &operator=(const MyReduceCallback &that) {
        //std::cout << "MyReduceCallback &operator=(const MyReduceCallback &that)" << std::endl;
        this->incr = that.incr;
        return *this;
    }

    void operator()(const MyPair<Etiquette, char> &mp, int *agg) {
        //std::cout << "void operator()(const MyPair<Etiquette, char> &mp, int *agg)" << std::endl;
        if(mp.first == CMaj || mp.first == VMaj || mp.first == VMin) *agg += this->incr;
    }

};

#endif