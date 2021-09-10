#include <iostream>

class Expression
{
public:
    virtual int eval() const = 0;
    virtual Expression * clone() const = 0;
    virtual Expression * cloneTemporaire() const = 0;
};

class Constante : public Expression
{
public:
    Constante() : entier(0){}
    Constante(int entier) : entier(entier){}
    int eval() const { return entier; }
    Expression * clone() const { return new Constante(entier); }
    Expression * cloneTemporaire() const { return new Constante(std::move(entier)); }
private:
    int entier;
};

class Plus : public Expression
{
public:
    Plus(const Expression &l, const Expression &r)
    {
        left = l.clone();
        right = r.clone();
    }
    Plus(const Expression &&l, const Expression &&r)
    {
        left = std::move(l.cloneTemporaire());
        right = std::move(r.cloneTemporaire());
    }
    int eval() const { return left->eval() + right->eval(); }
    Expression * clone() const { return new Plus(*left, *right); }
    Expression * cloneTemporaire() const { return new Plus(std::move(*left), std::move(*right)); }
private:
    Expression *left;
    Expression *right;
    int entier;
};

/*
*   On utilise la classe abstraite Expression, lorsque dans nos classes dérivés nous faisons appel à Expression.clone() ou Expression.eval()
*   le type statique de la var est Expression mais sont type dynamique ne l'est pas.
*   Le compileur fera alors appel à l'eval() ou clone() correspondant à son type.
*   Exemple : Plus(Plus(Constante(5), Constante(10)), Constante(10));
*   Sur le premier plus, l.clone() appel Plus::Clone et r.clone() appel Constante::Clone
*   Après avoir fait nos copies, nous faisons appel à eval(), on remonte alors tout l'arbre
*   des Plus et Constante jusqu'a remonter à Constante.eval + Constante.eval ce qui retourne la somme des deux entiers
*   On redescent et affiche le total !
*/

// Pourquoi l’usage de la référence dans ce programme utilisateur est-il important ? 
/*
*   
*
*/

class Moins : public Expression
{
public:
    Moins(const Expression &l, const Expression &r)
    {
        left = l.clone();
        right = r.clone();
    }
    Moins(const Expression &&l, const Expression &&r)
    {
        left = std::move(l.cloneTemporaire());
        right = std::move(r.cloneTemporaire());

    }
    int eval() const { return left->eval() - right->eval(); }
    Expression * clone() const { return new Moins(*left, *right); }
    Expression * cloneTemporaire() const { return new Moins(std::move(*left), std::move(*right)); }
private:
    Expression *left;
    Expression *right;
    int entier;
};

class Mult : public Expression
{
public:
    Mult(const Expression &l, const Expression &r)
    {
        left = l.clone();
        right = r.clone();
    }
    Mult( Expression &&l,  Expression &&r)
    {
        left = std::move(l.cloneTemporaire()); //virer les move
        right = std::move(r.cloneTemporaire());
    }
    Mult(const Expression &l,  Expression &&r)
    {
        left = std::move(l.clone()); //virer les move
        right = std::move(r.cloneTemporaire());
    }
    Mult( Expression &&l, const Expression &r)
    {
        left = std::move(l.cloneTemporaire()); //virer les move
        right = std::move(r.clone());
    }
    int eval() const { return left->eval() * right->eval(); }
    Expression * clone() const { return new Mult(*left, *right); }  
    Expression * cloneTemporaire() const { return new Mult(std::move(*left), std::move(*right)); }
private:
    Expression *left;
    Expression *right;
    int entier;
};


int main()
{
    int a=5;
    const Expression & e = Mult(Plus( Constante(a), Constante(-2)),Plus( Constante(1),Constante(3)) );
    std::cout << e.eval() << std::endl;
    return 0;
}