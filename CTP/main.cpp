#include <iostream>
#include "SimpQueue.hpp"

int main()
{
    SimpQue<double, 5> sq;

    for (unsigned int i = 0; i < 25; i++)
        sq.add(i + .5);

    std::cout << sq << "(size=" << sq.getSize() << ")" << std::endl << std::endl;
    std::cout << "devrait afficher 15.5 : " << sq[15] << std::endl << std::endl;

    SimpQue<double, 5> sq2;
    std::cout << sq2 << "(size=" << sq2.getSize() << ")" << std::endl << std::endl;
    sq2 = sq;
    std::cout << sq2 << "(size=" << sq2.getSize() << ")" << std::endl << std::endl;

    SimpQue<double, 5> sq3(sq);
    std::cout << sq3 << "(size=" << sq3.getSize() << ")" << std::endl << std::endl;

    std::cout << "parcours sq3 avec iterator" << std::endl;
    SimpQue<double, 5>::const_iterator it;
    for (it = sq3.begin(); it != sq3.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl << std::endl;

    std::cout << "devrait afficher une erreur (test de l'exception) : " << std::endl;
    try {
        std::cout << *it << std::endl; // it pointe maintenant hors limites, le dereferencement doit faire une erreur propre
    } catch (const std::exception &e) {
        std::cerr << "+ exception, msg=" << e.what() << std::endl;
    }

    // valgrind ./a.out

    return 0;
}