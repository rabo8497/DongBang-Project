#include <iostream>
using namespace std;

class Base
{
public:
    Base() = default;
    ~Base() = default;
    virtual void print() = 0;
};

class Derived : public Base
{
public:
    Derived() = default;
    ~Derived() = default;
    void print(int arg)
    {
        cout << "Hello " << arg << "!" << endl;
    }
};

int main()
{
    Derived *d = new Derived;
    Base *b = d;

    b->print(11);

    return 0;
}