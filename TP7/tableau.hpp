//====================================================================
// Classe Tableau generique :
//   - sur le type de ses elements
//   - et sur la taille des agrandissements de la capacite
//
//====================================================================

#ifndef _TABLEAU
#define _TABLEAU

#include <iostream>
#include <cassert>

//====================================================================
//  Declarations classe Tableau et fonctions amies 
//   (pour eviter les messages d'erreurs lors des declarations d'amitie 
//    dans la classe Tableau)
//====================================================================
template <typename T,int agrandissement>
class Tableau;

template <typename T,int agrandissement>
Tableau<T,agrandissement>  operator+ (const Tableau<T, agrandissement> & t1,
                                      const Tableau<T, agrandissement> & t2);

template <typename T,int agrandissement1, int agrandissement2>
Tableau<T,agrandissement1>  operator+ (const Tableau<T, agrandissement1> & t1,
				      const Tableau<T, agrandissement2> & t2);

template <typename T,int agrandissement>
std::ostream  & operator << (std::ostream & os, const Tableau<T,agrandissement> & V);

template <typename T,int agrandissement>
std::istream  & operator >> (std::istream & is, Tableau<T,agrandissement> & V);


//====================================================================
//  Definition classe Tableau 
//====================================================================

template <typename T,int agrandissement>
class Tableau {
public:  
  typedef T value_type;
  typedef Tableau<T,agrandissement> Self;

//-- Declarations FONCTIONS et CLASSES AMIES
//-- Il faut bien penser a donner le nom complet des fonctions amies.
//-- En particulier, si ces fonctions sont instanciees a partir d'un
//-- template, penser a preciser les parametres d'instanciation.
  template <typename T2, int agrandissement2>
  friend class Tableau;

  // Addition de 2 Tableaux
  friend  Self
    operator+<T,agrandissement>(const Self &, const Self  &);
    
  template <class TT,int agrandissement1, int agrandissement2>
  friend  Tableau<TT,agrandissement1>
	operator+(const Tableau<TT,agrandissement1> &, const Tableau<TT,agrandissement2>  &);
	
  // E/S de Tableaux
  friend std::ostream& operator<< <T,agrandissement>(std::ostream &, const Self &);
  friend std::istream& operator>> <T,agrandissement>(std::istream &, Self &);

 public:
  //Constructeurs et destructeur
  explicit Tableau (const int=0);
  Tableau (const int, const T & );
    
  Tableau (const Tableau<T,agrandissement> &);
  template <typename T2, int agrandissement2>
  Tableau (const Tableau<T2,agrandissement2> &);
    
  ~Tableau ();
  //Acces aux elements d'un tableau
  T       & operator[](int); //Acces en lecture/ecriture
  const T & operator[](int) const; //Acces en ecriture
  int taille() const {return nombre_element;}
  int capacite() const {return cap;}
  // Operateur d'affectation
  Tableau & operator=(const Tableau<T,agrandissement> & );
  template <typename T2, int agrandissement2>	
  Tableau & operator=(const Tableau<T2,agrandissement2> & );
  Tableau & ajoute(const T &);
    
  //-----------------------------------------------------------------------
  
  static int nb_instances(){return compteur;}

  //--------------------------------------------------------
private :
  T * vect; 
  int nombre_element;
  int cap;
  static int compteur;
};

//====================================================================
//             Membre static template
//====================================================================
template <typename T,int agrandissement>
int Tableau<T,agrandissement>::compteur=0;

//====================================================================
// Implantation des fonctions membres de Tableau
//====================================================================

template <class T,int agrandissement>
Tableau<T,agrandissement>::Tableau(const int  n)
{
  nombre_element=n;
  cap = ( n/agrandissement +1 )*agrandissement;
  vect = new T [cap];
  compteur++;
}

template <typename T,int agrandissement>
Tableau<T,agrandissement>::Tableau(const int n,const T & val)
{   
  nombre_element=n;
  cap = (n/agrandissement+1)*agrandissement;
  vect = new T [cap];
  for (int i = 0; i<nombre_element; i++)
    vect[i]= val;
  compteur++;
}

template <typename T,int agrandissement>
Tableau<T,agrandissement>::Tableau(const Tableau<T,agrandissement> &V)
: nombre_element(V.nombre_element), cap(V.cap)
{
    vect = new T[cap];
    for (int i= 0; i<nombre_element; i++)
        vect[i]=V.vect[i];
    compteur++;
}
template <typename T,int agrandissement>
template <typename T2, int agrandissement2>
Tableau<T,agrandissement>::Tableau(const Tableau<T2,agrandissement2> &V)
  : nombre_element(V.nombre_element), cap(V.cap)
{
  vect = new T[cap];
  for (int i= 0; i<nombre_element; i++)
    vect[i]=V.vect[i];
  compteur++;
}

// Destructeur
template <class T,int agrandissement>
Tableau<T,agrandissement>::~Tableau(void)
{
  compteur--;
  delete [] vect;
}

// Acces ieme element
template <class T,int agrandissement>
T &  Tableau<T,agrandissement>::operator[] (int i)
{
  assert((i < nombre_element)&&(i>=0));
  return vect[i];
}

template <class T,int agrandissement>
const T &  Tableau<T,agrandissement>::operator[] (int i) const
{
  assert((i < nombre_element)&&(i >= 0));
  return vect[i];
}

// Operateur d'affectation
template <typename T,int agrandissement>
Tableau<T,agrandissement> & Tableau<T,agrandissement>::operator = (const Tableau<T,agrandissement> &  t)
{
    if (&t == this)
        return *this;
    
    delete [] vect;
    nombre_element = t.nombre_element;
    cap = t.cap;
    vect = new T[t.cap];
    for (int i=0; i<nombre_element ; i++)
        vect[i] =  t.vect[i];
    return *this;
}

template <typename T,int agrandissement>
template <typename T2,int agrandissement2>
Tableau<T,agrandissement> & Tableau<T,agrandissement>::operator = (const Tableau<T2,agrandissement2> &  t)
{
  if ( reinterpret_cast<const Tableau<T,agrandissement>*>(&t) == this)  
    return *this; 

  delete [] vect;
  nombre_element = t.nombre_element; 
  cap = t.cap;
  vect = new T[t.cap];
  for (int i=0; i<nombre_element ; i++)
    vect[i] =  t.vect[i];
  return *this;
}

template <class T,int agrandissement>
Tableau<T,agrandissement> & Tableau<T,agrandissement>::ajoute(const T & el)
{
  if(nombre_element == cap-1)
    { 
      T * temp = new T[cap+agrandissement];
      for (int i=0;i<nombre_element;i++)
	temp[i]=vect[i];
      delete vect;
      vect=temp;
      cap+=agrandissement;
    }
  vect[nombre_element++]=el;
  assert(nombre_element<cap);
  return *this;
}

//====================================================================
// Implantation des fonctions externes
//====================================================================
template <typename T,int agrandissement>
Tableau<T,agrandissement>  operator+ (const Tableau<T, agrandissement> & t1,
                                      const Tableau<T, agrandissement> & t2)
{
    const T * maxtab;
    int minnb;
    int nbelm = ((t1.nombre_element>t2.nombre_element)?
                 (maxtab=t1.vect,minnb=t2.nombre_element,t1.nombre_element):
                 (maxtab=t2.vect,minnb=t1.nombre_element,t2.nombre_element));
    
    Tableau<T,agrandissement> R(nbelm);
    for(int i=0; i<minnb ; i++)
        R.vect[i]= t1.vect[i] + t2.vect[i];
    
    for(int i=minnb; i<R.nombre_element ; i++)
        R.vect[i]= maxtab[i];
    return R;
}

template <class T,int agrandissement1, int agrandissement2>
Tableau<T,agrandissement1>  operator+ (const Tableau<T, agrandissement1> & t1,
				      const Tableau<T, agrandissement2> & t2)
{
  const T * maxtab;
  int minnb;
  int nbelm = ((t1.nombre_element>t2.nombre_element)?
	       (maxtab=t1.vect,minnb=t2.nombre_element,t1.nombre_element):
	       (maxtab=t2.vect,minnb=t1.nombre_element,t2.nombre_element));

  Tableau<T,agrandissement1> R(nbelm);
  for(int i=0; i<minnb ; i++)
    R.vect[i]= t1.vect[i] + t2.vect[i];

  for(int i=minnb; i<R.nombre_element ; i++)
    R.vect[i]= maxtab[i];
  return R;
}

// Surcharge operateurs de flots
template <class T,int agrandissement>
std::ostream  & operator<< (std::ostream & os, const Tableau<T,agrandissement> & V)
{ os << std::endl << "[";
 for (int i=0; i< V.nombre_element; i++) 
      os << V.vect[i] << " ";
  os << "]" << std::endl;
  return os ;
}


template <class T,int agrandissement>
std::istream  & operator>> (std::istream &is, Tableau<T,agrandissement> & V)

{ std::cout << std::endl << "Debut saisie tableau\n";
  for (int i=0; i < V.nombre_element; i++)
       { 
	 std::cout << "[" << i<<"] :";
	 is >> V.vect[i];
	 std::cout << std::endl;
       }
  std::cout << "Fin saisie tableau\n";
  return is;
}
//==============================================================

template <typename T, int _n>
class TablIterator
{
private:
  T _value*;
  int _n;
public:
  TablIterator(T* value) : _value(value) {}
  TablIterator<T> &operator++() {
    ++_value;
    return *this;
  }
  TablIterator<T> &operator++(T x) {
    TablIterator<T> iter = *this;
    ++_value;
    return iter;
  }
  T &operator*() {
    return *_value;
  }
  T* &operator->() {
    return _value;
  }
  bool &operator!=(const TablIterator<T> &other) {
    return _value != other._value;
  }
  TablIterator<T> begin() {
    return TablIterator<T>(_value);
  }
  TablIterator<T> end() {
    return TablIterator<T>(_value + _n);
  }
};

#endif