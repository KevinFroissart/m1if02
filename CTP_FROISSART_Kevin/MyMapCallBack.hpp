#ifndef MYMAPCALLBACK_HPP
#define MYMAPCALLBACK_HPP
#include <iostream>
#include "MyPair.hpp"
#include "MyEnum.hpp"

class MyMapCallBack {
private:
    bool func_min;
public:
    MyMapCallBack() : func_min(false) {
        //std::cout << "MyMApCallBack()" << std::endl;
    }
    MyMapCallBack(const bool &min) : func_min(min) {
        //std::cout << "MyMApCallBack()" << std::endl;
    }
    MyMapCallBack(const MyMapCallBack &that) {
        //std::cout << "MyMapCallBack(const MyMapCallBack &that)" << std::endl;
        *this = that;
    }
    MyMapCallBack &operator=(const MyMapCallBack &that) {
        //std::cout << "MyMapCallBack &operator=(const MyMapCallBack &that)" << std::endl;
        this->func_min = that.func_min;
        return *this;
    }
    virtual ~MyMapCallBack() {
        //std::cout << "~MyMapCallBack()" << std::endl;
    }

    MyPair<Etiquette, char> operator()(char c) {
        //std::cout << "MyPair<Etiquette, char> operator()(char c)" << std::endl;
        int i = (int) c;
        char copie = c;
        Etiquette etiquette = Other;
        if(i >= 65 && i <= 90) {
            etiquette = func_min ? VMin : VMaj;
            if(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y') etiquette = func_min ? CMin : CMaj;
            if(func_min) {
                copie = char(copie + 32);
            }
        }
        else if(i >= 97 && i <= 122){
            etiquette = VMin;
            if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') etiquette = CMin;
        }
        return MyPair<Etiquette, char>(etiquette, copie);
    }

};


#endif