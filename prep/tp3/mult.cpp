#include <iostream>

class multi
{
public:
    multi(int val = 5) : val(val) {}
    int operator()() {
        val += val;
        std::cout << val << std::endl;
        return val;
    }
private:
    int val;
};

int main() {
    multi(5)();
    multi c = multi(5);
    c();
    c();
    c();
    multi()();
    return 0;
}