#include <iostream>

template <int i>
void procedure(){
    i += 2;
    std::cout << i;
}

int main() {
    procedure<5>();
    return 0;
}