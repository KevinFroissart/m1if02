#include <iostream>

class LaClasse
{
public :
  //Construction, conversion, affectation et destruction
  LaClasse() : l(0)
  {std::cout << "LaClasse::LaClasse()\n";}
  LaClasse(const LaClasse & lc) : l(lc.l)
  {std::cout << "LaClasse::LaClasse(const LaClasse & )\n";}
  LaClasse(int i) : l(i) 
  {std::cout << "LaClasse::LaClasse(int)\n";}
  operator bool() const
  {std::cout << "LaClasse::operator bool() const\n"; return true;}
  ~LaClasse()
  {std::cout << "~LaClasse::LaClasse()\n";}
  const LaClasse & operator=(const LaClasse & c)
  {l=c.l; std::cout << "LaClasse::operator=(const LaClasse &)\n"; return *this;}
  //Autre fonction membre
  LaClasse F(LaClasse);
  // Déclaration fonction extérieure amie
  friend std::ostream & operator << (std::ostream & os, const LaClasse & lc);
private :
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

std::ostream & operator << (std::ostream & os, const LaClasse & lc)
{
  os << " in ostream << LaClasse "<< lc.l << std::endl;
  return os;
}

// Testez et analysez la séquence d'appels aux fonctions membres 
// de LaClasse dans le programme suivant :


int main()
{
  LaClasse c1; //copy
  LaClasse c2=LaClasse(); //copy
  LaClasse cc1(c1); 
  LaClasse cc2=c1; //copy
  LaClasse cc3=LaClasse(c1); // copy + copy
  LaClasse cv1(5); // int
  LaClasse cv2=5; // int
  LaClasse cv3=LaClasse(5); // int + copy 
  LaClasse cv4=(LaClasse)5; // int + copy
  std::cout << std::endl;
  c1=cc1; // opérateur = (d'affectation) (si on met le type au début : pas une affectation mais déclarations)
  std::cout << std::endl;
  c2=8; // int + opérateur =
  if(LaClasse()){} // default + bool + ~
  std::cout << std::endl;
  if(cv1) // opérateur bool
    {
      cv1=F(10); // int + copy + int + copy + opérateur = (premier copy car le param est passé en copy, second copy car return passé en copy)
      cv1=F(c1); // copy + int + copy + opérateur =
      cv1=c1.F(c2); // copy c2 + copy vv + int + copy + copy + opérateur = (pas de copy car l'opé = prends en paramètre une réfeérence constance ce qui évite de faire une copie)
    }

  std::cout << "Tableaux \n";
  LaClasse tab[3];
  LaClasse *pc=new LaClasse(tab[0]);
  delete pc;
  std::cout << "Avant de sortir ... \n";
  return 0; 
}
 
