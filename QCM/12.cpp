#include <iostream>

class Employe
{
    public:
    virtual void f1()
    {
        std::cout << "employe f1" << std::endl;
    }
    virtual void f2(int i=0)
    {
        std::cout << "employe f2" << std::endl;
    }
    virtual void f3(int i)
    {
        std::cout << "employe f3" << std::endl;
    }
};

class Cadre : public Employe
{
    private:
    void f1()
    {
        std::cout << "cadre f1" << std::endl;
    }
    public:
    void f2(int i)
    {
        std::cout << "cadre f2" << std::endl;
    }
    void f3(int i)
    {
        std::cout << "cadre f3 int" << std::endl;
    }
    void f3(char i)
    {
        std::cout << "cadre f3 char" << std::endl;
    }
};

int main()
{
    Employe *e = new Cadre;
    e->f1();
    e->f2();
    e->f3('a');
    Cadre *c = new Cadre;
    //c->f1();
    //c->f2();
    c->f3('a');
    return 0;
}