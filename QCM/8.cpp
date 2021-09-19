#include <iostream>
template <int T>
struct X{
    enum {res = T+X<T-1>::res};
};

template <>
struct X<1>{
    enum {res = 1};
};

int main() {std::cout << X<5>::res << std::endl; return 0;}