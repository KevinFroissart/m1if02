#include <iostream>

class Objet
{
public:
    Objet(int val = 5) : val(val) {
        std::cout << "Objet::Objet(int) : val = " << val << std::endl;
    }
    int operator()() 
    {
        val = val + 5;
        std::cout << "val = " << val << std::endl;
        return val;
    }
private:
    int val;
};

int main()
{
    Objet obj(12);
    obj();
    Objet(20)();
    Objet()();
    return 0;
}
