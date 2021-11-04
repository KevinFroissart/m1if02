#include <iostream>
#include "SequenceCirculaire.hpp"

SequenceCirculaire<int> fct_bidon()
{
	SequenceCirculaire<int> un_truc;
	un_truc.insert(6, 0);
	un_truc.insert(9, 1);
	return un_truc;
}

int main()
{
	SequenceCirculaire<double> looping;

	for (int i = 0; i < 11; ++i)
	{
		looping.insert(i * 1.01, i);
	}
	looping.display();
	std::cout << std::endl;

	SequenceCirculaire<double>::iterator it = looping.begin(5);
	SequenceCirculaire<double>::iterator fin = looping.end(5);

	for (; it != fin; ++it)
	{
		std::cout << *it << "\t";
		*it = *it + 0.5;
	}
	std::cout << std::endl;
	looping.display();

	for (auto it2 = looping.begin(7); it2 != fin; ++it2)
	{
		std::cout << *it2 << "\t";
	}
	std::cout << std::endl;
	std::cout << std::endl;
	
	double a = 3.5;
	std::cout << "looping.search(" << a << ")\t" << looping.search(a) << std::endl;
	a = 3 * 1.01;
	std::cout << "looping.search(" << a << ")\t" << looping.search(a) << std::endl;


	return 0;
}