#include <iostream>
#include <cstdlib>
#include "ABR.hpp"

template <typename U>
std::ostream &operator<<(std::ostream &out, const ABR<U> &that) {
    return that.print(out, that.racine);
}

int main() {

    ABR<int> tree;
    for(int i=0;i<10;i++)
        tree.insert(rand() % 100); // #include<cstdlib>
    std::cout << tree << std::endl; // Affichage infixé
    while(!tree.find(rand() % 100));

    ABR<int>::iterator it=tree.begin();
    ABR<int>::iterator ite=tree.end();
    for(;it!=ite;++it)
        std::cout << *it << std::endl;
        

    return 0;
}