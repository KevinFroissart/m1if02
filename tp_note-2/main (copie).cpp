#include <cstdio>
#include <iostream>
#include "Map.h"
#include "Reduce.h"
#include <vector>
#include "string.h"

int main(){

    // Test de la classe MyPair
    auto myPair = makeMyPair(2,'c');

    std::cout << myPair;

    // Test de la classe MyMapCallback
    MyMapCallback funcmin(true);
    MyMapCallback func(false);
    auto p1 = funcmin('Y');
    auto p2 = funcmin('C');
    auto p3 = funcmin('4');
    auto p4 = func('Y');

    std::cout << p1 << p2 << p3 << p4 << "\n\n";

    // Test de la classe MyReduceCallback
    MyReduceCallback redfunc(0,1,1,0,0);
    int agg = 0;
    redfunc(agg, p4);

    std::cout << agg << "\n\n\n";


    // Test de la fonction Map
    std::vector<MyPair<Etiquette, char>> out;
    std::vector<char> in;
    const char* s = "CoUCoU Thibaut123";

    for(size_t i = 0; i < strlen(s); i++){
        in.push_back(s[i]);
        out.push_back(makeMyPair(Etiquette::Other, 'c'));
    }

    Map(in.begin(), in.end(), out.begin(), func);

    std::cout << "Résultat du Mapping\n\n";
    for(auto it = out.begin(); it != out.end(); it++){
        std::cout << *it;
    }
    std::cout << "\n\n";


    // Test de la fonction Reduce
    MyReduceCallback redcallback(1,2,1,2,0);
    int agg1 = 0;

    Reduce(out.begin(), out.end(), redcallback, agg1);

    std::cout << "Résultat de la réduction : " << agg1 << "\n\n";

    return 0;
}