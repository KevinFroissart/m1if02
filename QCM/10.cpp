#include <iostream>

class Derivee
{
    public:
    void affiche(int i)
    {
        std::cout << "Derivee " << i << std::endl;
    }
};

class Base : public Derivee
{
    public:
    void affiche(int i, int j)
    {
        std::cout << "Base " << i+j << std::endl;
    }
    using Derivee::affiche;
};

int main()
{
    Base b1;
    b1.affiche(5);
    Derivee d1;
    d1.affiche(5);
    Derivee &d2 = b1;
    d2.affiche(5);
    return 0;
}