#include <iostream>

template <typename T>
void procedure(const T&x) {
    static int compteur = 1;
    std::cout << x << " : compteur = " << compteur << " ; ";
    ++compteur;
    return;
}

int main() {
    procedure(1);
    procedure(5);
    procedure(5.5);
    procedure(6);
    return 0;
}