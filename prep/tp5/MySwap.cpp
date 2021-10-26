#include <iostream>
#include <string.h>

template <typename T>
void mySwap(T &a, T &b)
{
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
};

template <typename T>
T myMin(const T &a, const T &b)
{
    return a<b?a:b;
}

template < >
const char* myMin<const char*>(const char* const &a, const char* const &b)
{
    return strcmp(a,b)<0?a:b;
}


template<size_t I, size_t J>
const char* myMin(const char (&a)[I], const char (&b)[J])
{
    return strcmp(a,b)<0?a:b;
}


int main()
{
    std::cout << myMin(5,6) <<std::endl;
    std::cout << myMin(6,5) <<std::endl;
    std::cout << myMin("lili","lala") <<std::endl;
    std::cout << myMin("li","lala") <<std::endl; // 2 arguments de types différents
    const char * cc="mumu";
    const char * dd="ma";
    std::cout << myMin(cc,dd) <<std::endl;
    char ee[5]="toto";
    char ff[5]="ta"; //tableau de même taille que le précédent
    std::cout << myMin(ee,ff) <<std::endl;
    std::cout << myMin("zut",ff) <<std::endl;
    return 0;
}