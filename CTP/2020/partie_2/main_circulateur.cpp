/**
 * @author      : David JULIEN (david.julien@etu.univ-lyon1.fr)
 * @file        : main
 * @created     : Friday Sep 18, 2020 14:16:25 CEST
 */

#include <iostream>
#include <cstdlib>

#include "circulateur.hpp"

int main()
{
    Sequence<double> cercle(10, 5.5); // sequence (periode = 1à, v =5.5)
	std::cout << cercle << std::endl;

	for(int i=0; i < 10; i++)
	{
		cercle[i] = i * .1;
	}
	std::cout << cercle << std::endl;

	Sequence<double>::Circulator circ(cercle, 5);
	Sequence<double>::Circulator circend(cercle, 4);

	for( ; circ != circend; ++circ)
	{
		std::cout << *circ << std::endl;
	}

	circ = cercle.circulator(0);
	for(int i = 0; i < 20; i++)
	{
		*circ = i + .2;
		++circ;
	}
	std::cout << cercle << std::endl;

	/* ARITHMETIQUE DES CIRCULATEURS */
	Sequence<double>::Circulator circ2(cercle, 5);
	Sequence<double>::Circulator circ3(circ2);
	circ2 = circ3+4;

	std::cout << "circ2(cercle, 5)" << "\n";
	std::cout << "circ3(circ2)" << "\n";
	std::cout << "circ2 = circ3+4" << "\n";
	std::cout << "position dans circ2: " << circ2.pos() << std::endl;

	circ2 = circ3-2;
	std::cout << "circ2 = circ3-2" << "\n";
	std::cout << "position dans circ2: " << circ2.pos() << std::endl;

    return 0;
}

