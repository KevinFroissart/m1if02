#include <iostream>

class LaBase {
    public: virtual void affiche() {std::cout << "LaBase" << std::endl;}
};

class LaDerivee : public LaBase {
    public: virtual void affiche(int i=5) {std::cout << "LaDerivee" << std::endl;}
};

int main() {
    LaDerivee dede;
    LaBase & bibi = dede;
    bibi.affiche(8);
    return 0;
}