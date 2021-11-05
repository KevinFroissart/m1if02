#include <iostream>
#include <vector>
#include "MyPair.hpp"
#include "MyMapCallBack.hpp"
#include "MyReduceCallBack.hpp"
#include "MyMap.hpp"

template <typename X, typename Y>
MyPair<X,Y> makeMyPair(const X &first, const Y &second) {
    return MyPair<X,Y>(first, second);
}

int main() {

    MyPair<int, double> p;
    p = makeMyPair(8, 9.5);
    p.first = 4;
    p.second = 5.5;
    auto pp = makeMyPair(24, 35);

    // --- 3.1 Etiquetage

    MyMapCallBack funcmin(true);
    MyMapCallBack func(false);
    MyPair<Etiquette, char> mp = funcmin('Y');

    std::cout << "Y Maj deviens 'y' grace à MapCallBack avec réduction des Majs" << std::endl;
    std::cout << mp.second << std::endl;

    MyPair<Etiquette, char> mp2 = func('Y');

    std::cout << "Y Maj reste 'Y' grace à MapCallBack sans réduction des Majs" << std::endl;
    std::cout << mp2.second << std::endl;

    int test = 5;
    MyReduceCallback mr(10);
    mr(mp2, &test);

    std::cout << "5 devient 15 grâce à ReduceCallBack avec une inrémentation de 10" << std::endl;
    std::cout << test << std::endl;

    // --- 3.2 Map

    std::vector<char> input;
    for(int i = 65; i <= 90; i++) {
        input.push_back((char) i);
    }
    std::vector<MyPair<Etiquette, char> > output;
    output.resize(26);
    MyMapCallBack fonctionCallBack(true);

    // Il est possible d'appliquer Map avec une liste, la fonction est en revanche incompatible 
    // avec les tableaux classiques car nous ne pouvons pas utiliser les iterateurs requis par
    // la fonction.

    std::vector<char>::iterator inBeg = input.begin();
    std::vector<char>::iterator inEnd = input.end();
    std::vector<MyPair<Etiquette, char> >::iterator outpos = output.begin();
    std::vector<MyPair<Etiquette, char> >::iterator outposEnd = output.end();

    Map<std::vector<char>::iterator, std::vector<MyPair<Etiquette, char> >::iterator, MyMapCallBack>(inBeg, inEnd, outpos, fonctionCallBack);

    outpos = output.begin();
    outposEnd = output.end();

    std::cout << "Itération sur le conteneur output après utilisation de Map et de la fonction MapCallBack avec réduction des Maj" << std::endl;

    for(; outpos != outposEnd; outpos++){
        std::cout << outpos->second << " ";
    }
    std::cout << std::endl;

    return 0;
}