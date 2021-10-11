#include <iostream>

class Expression
{
public:
    virtual int eval() const = 0;
    virtual Expression * clone() const = 0;
private:
};

class Constante : public Expression
{
public:
    Constante(int constante = 0) : constante(constante) {}
    int eval() const { return constante; }
    Expression* clone() const 
    {
        return new Constante(constante);
    }
    ~Constante()
    {  
    } 
private:
    int constante;
};

class Plus : public Expression
{
public:
    Plus(const Expression &c1, const Expression &c2) {
        l = c1.clone();
        r = c2.clone();
    }
    int eval() const
    {
        return l->eval() + r->eval();
    }
    Expression * clone() const
    {
        return new Plus(*l, *r);
    }
    ~Plus() {
        delete l;
        delete r;
    }
private:
    Expression *l;
    Expression *r;
};

class Moins : public Expression
{
public:
    Moins(const Expression &c1, const Expression &c2) {
        l = c1.clone();
        r = c2.clone();
    }
    int eval() const
    {
        return l->eval() - r->eval();
    }
    Expression * clone() const
    {
        return new Moins(*l, *r);
    }
    ~Moins() {
        delete r;
        delete l;
    }
private:
    Expression *l;
    Expression *r;
};

class Mult : public Expression
{
public:
    Mult(const Expression &c1, const Expression &c2) {
        l = c1.clone();
        r = c2.clone();
    }
    int eval() const
    {
        return l->eval() * r->eval();
    }
    Expression * clone() const
    {
        return new Mult(*l, *r);
    }
    ~Mult() {
        delete r;
        delete l;
    }
private:
    Expression *l;
    Expression *r;
};

int main()
{

    int a=5;
    const Expression & e = Mult(Plus( Constante(a), Constante(-2)), Plus( Constante(1), Constante(3)) );
    std::cout << e.eval() << std::endl;
    return 0;
    return 0;
}