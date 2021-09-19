#include <iostream>

struct LaBase {
    virtual void addicheType() {std::cout << "LaBase" << std::endl;}
};

template <typename Derivee>
struct LaSpecialisee : public LaBase {
    virtual void afficheType() {std::cout << typeid(Derivee).name() << std::endl;}
};

struct LaDerivee : public LaSpecialisee<LaDerivee> {};

int main() {
    LaBase *baby = new LaDerivee;
    baby->addicheType();
    return 0;
}

