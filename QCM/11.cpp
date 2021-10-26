#include <iostream>

class Employe
{
    public:
    virtual void affiche()
    {
        std::cout << "employe" << std::endl;
    }
};

class Cadre : public Employe
{
    public:
    virtual void affiche()
    {
        Employe::affiche();
        std::cout << "cadre" << std::endl;
    }
};

int main()
{
    Employe e;
    Cadre c;
    Employe &re = c;
    Employe *pe = &e;

    e.affiche(); //statique e
    c.affiche(); //statique c
    re.affiche(); // dynamique c car virtual
    pe->affiche(); // dynamique e

    e = c; // dynamique change pas sur des objets T -> e
    e.affiche();
    pe = &c; // dynamique change sur des pointeurs ou références -> c
    pe->affiche();

    return 0;
}