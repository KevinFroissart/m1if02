#include <iostream>

class LaBase {
    public:     template <int NB>
virtual void affiche() {std::cout << "LaBase" << NB << std::endl;}
};

class LaDerivee : public LaBase {
    public:     template <int NB>
virtual void affiche() {std::cout << "LaDerivee" << NB << std::endl;}
};

int main() {
    LaDerivee dede;
    LaBase & bibi = dede;
    bibi.affiche();
    return 0;
}