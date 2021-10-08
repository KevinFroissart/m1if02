#include <iostream>
#include "tableau.hpp"
int main()
{
    Tableau<int,6> A(5);
    std::cin >> A;
    TabIterator<int,6> it=A.begin();
    TabIterator<int,6> ite=A.end();
    for(;it!=ite;++it)
    std::cout << *it << std::endl;
    return 0;
}