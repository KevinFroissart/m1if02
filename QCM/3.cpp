#include <iostream>

class LaBase {
    public: virtual void affiche() {std::cout << "LaBase" << std::endl;}
};

class LaDerivee : public LaBase {
    public: virtual void affiche() {std::cout << "LaDerivee" << std::endl;}
};

int main() {
    LaDerivee dede;
    LaBase & bibi = dede;
    bibi.affiche();
    return 0;
}