/**
 * @author      : David JULIEN (david.julien@etu.univ-lyon1.fr)
 * @file        : main
 * @created     : Friday Sep 18, 2020 14:16:25 CEST
 */

#include <iostream>
#include <cstdlib>

#include "sequence.hpp"

int main()
{
    Sequence<double> cercle(10, 5.5); // sequence (periode = 10, v =5.5)
	Sequence<double> cercle2(cercle);

	std::cout << cercle << std::endl;

	for(size_t i = 0; i < 30; i++)
	{
		cercle.insere(i, i * .5);
	}
	std::cout << cercle << std::endl;

	cercle = cercle2;
	std::cout << cercle << std::endl;

	for(size_t i = 0; i < 30; i++)
	{
		cercle[i] = i * .3;
	}
	std::cout << cercle << std::endl;

	cercle = cercle2;
	double elem = (double) (rand() % 10 + 0.1); // erreur à la compilation
	while(cercle.find(elem) != -1) 				// sans le cast
	{
		cercle.insere(0, elem);
		elem = (double) (rand() % 10 + 0.1);
		std::cout << elem << std::endl;
	}

    return 0;
}

