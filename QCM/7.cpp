#include <iostream>
class Mystere {
    int d;
    public:
    operator int() const { return d+5;}
    Mystere(int i=10) : d(i+1){}
    int operator()(int i) const {return d+i;}
};

int main(){
    std::cout << Mystere(8) << " puis " << Mystere(9)(3) << std::endl;
}