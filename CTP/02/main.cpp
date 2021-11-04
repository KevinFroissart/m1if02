#include <iostream>
#include "Circulaire.hpp"

template <typename U>
std::ostream &operator<<(std::ostream &out, const Circulaire<U> &that) {
    return that.print(out, 0);
}

int main() {

    Circulaire<double> cercle(10, 5.5);

    Circulaire<double> cercle2(cercle);

    std::cout << cercle << std::endl;

    for(int i = 0; i < 30; i++)
        cercle.insere(i, i*0.5);
    std::cout << cercle << std::endl;
    
    cercle=cercle2;

    for(int i = 0; i < 30; i++) 
        cercle[i] = i*0.3;
    std::cout << cercle << std::endl;

    return 0;
}