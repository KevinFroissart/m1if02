#include <iostream>

/*
*
* Ligne de commande pour compiler : g++ -std=c++14 -fno-elide-constructors Laclasse.cpp
* c++14 car fno-elide ne fonctionne pas en c++17
*
*/

class LaClasse
{
public:
  //Construction, conversion, affectation et destruction
  LaClasse() : l(0), ptr(new int(0))
  {
    std::cout << "LaClasse::LaClasse()\n";
  }

  LaClasse(const LaClasse &lc) : l(lc.l), ptr(new int(*lc.ptr))
  {
    std::cout << "LaClasse::LaClasse(const LaClasse & )\n";
  }

  LaClasse(int i) : l(i), ptr(new int(i))
  {
    std::cout << "LaClasse::LaClasse(int)\n";
  }

  LaClasse(LaClasse &&other) : l(other.l), ptr(other.ptr)
  {
    other.ptr = nullptr;
  }

  operator bool() const
  {
    std::cout << "LaClasse::operator bool() const\n";
    return true;
  }

  ~LaClasse()
  {
    std::cout << "~LaClasse::LaClasse()\n";
    delete ptr;
  }

  const LaClasse &operator=(const LaClasse &c)
  {
    l = c.l;
    ptr = new int(*c.ptr);
    std::cout << "LaClasse::operator=(const LaClasse &)\n";
    return *this;
  }

  LaClasse &operator=(LaClasse &&m)
  {
    l = m.l;
    delete ptr;
    ptr = m.ptr;
    m.ptr = nullptr;
    return *this;
  }

  //Autre fonction membre
  LaClasse F(LaClasse);
  // Déclaration fonction extérieure amie
  friend std::ostream &operator<<(std::ostream &os, const LaClasse &lc);

private:
  int *ptr;
  int l;
};

LaClasse F(LaClasse vv)
{
  std::cout << " in F \n";
  return 8;
}

LaClasse LaClasse::F(LaClasse v)
{
  std::cout << " in LaClasse::F \n";
  return ::F(v);
}

std::ostream &operator<<(std::ostream &os, const LaClasse &lc)
{
  os << " in ostream << LaClasse " << lc.l << std::endl;
  return os;
}

// Testez et analysez la séquence d'appels aux fonctions membres
// de LaClasse dans le programme suivant :

class LaClasseSpecialisee : public LaClasse
{
public:
  LaClasseSpecialisee() : t(0)
  {
    std::cout << "LaClasseSpecialisee::LaClasseSpecialisee()" << std::endl;
  }

  LaClasseSpecialisee(const LaClasseSpecialisee &lc) : t(lc.t)
  {
    std::cout << "LaClasseSpecialisee::LaClasseSpecialisee(const LaClasseSpecialisee & )\n";
  }

  LaClasseSpecialisee &operator=(LaClasseSpecialisee &&m)
  {
    t = m.t;
    std::cout << "LaClasseSpecialisee::operator=(const LaClasseSpecialisee &)" << std::endl;
    return *this;
  }

  ~LaClasseSpecialisee() {}

private:
  int t;
};

int main()
{
  LaClasse c1;                 //copy
  LaClasse c2 = LaClasse();    //copy
  LaClasse cc1(c1);            //copy
  LaClasse cc2 = c1;           //copy
  LaClasse cc3 = LaClasse(c1); // copy + copy
  LaClasse cv1(5);             // int
  LaClasse cv2 = 5;            // int
  LaClasse cv3 = LaClasse(5);  // int + copy
  LaClasse cv4 = (LaClasse)5;  // int + copy
  std::cout << std::endl;
  c1 = cc1; // opérateur = (d'affectation) (si on met le type au début : pas une affectation mais déclarations)
  std::cout << std::endl;
  c2 = 8; // int + opérateur =
  if (LaClasse())
  {
  } // default + bool + ~
  std::cout << std::endl;
  if (cv1) // opérateur bool
  {
    cv1 = F(10);    // int + copy + int + copy + opérateur = (premier copy car le param est passé en copy, second copy car return passé en copy)
    cv1 = F(c1);    // copy + int + copy + opérateur =
    cv1 = c1.F(c2); // copy c2 + copy vv + int + copy + copy + opérateur = (pas de copy car l'opé = prends en paramètre une réfeérence constance ce qui évite de faire une copie)
  }

  std::cout << "Tableaux \n";
  LaClasse tab[3];
  LaClasse *pc = new LaClasse(tab[0]);
  delete pc;

  std::cout << "\nDérivée\n";
  LaClasseSpecialisee lc1;
  LaClasseSpecialisee lc2 = LaClasseSpecialisee();

  std::cout << "\nUpcast\n";
  LaClasse uc1 = lc1;

  //std::cout << "\nDowncast\n";
  //LaClasseSpecialisee dc1 = c1;

  std::cout << "\nAvant de sortir ... \n";
  return 0;
}
