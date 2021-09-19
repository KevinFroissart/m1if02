#include <iostream>

class LaBase {
    public: void affiche() {std::cout << "LaBase" << std::endl;}
};

class LaDerivee : public LaBase {
    public: void affiche() {std::cout << "LaDerivee" << std::endl;}
};

int main() {
    LaDerivee dede;
    LaBase & bibi = dede;
    bibi.affiche();
    return 0;
}

8
4*25