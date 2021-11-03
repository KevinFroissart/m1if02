#include <iostream>
#include <cstdlib>
#include "Noeud.hpp"
#include "ABR.hpp"

template <typename U>
std::ostream &operator<<(std::ostream &out, const ABR<U> &that) {
    return that.print(out, that.racine);
}


int main() {

    ABR<int> tree;
    for(int i=0;i<10;i++)
        tree.insert(rand() % 100); 

    std::cout << tree << std::endl;
    while(!tree.find(rand() % 100));


    return 0;
}