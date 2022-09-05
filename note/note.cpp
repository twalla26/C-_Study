#include <iostream>
using namespace std;

class First {
public:
    virtual void SimpleFunc() { cout << "FirstFunc" << endl; }
};

class Second : public First {
public:
    virtual void SimpleFunc() {
        cout << "SecondFunc" << endl;
    }
};

int main(void) {
    First * ptr = new First();
    ptr->SimpleFunc();
    delete ptr;

    ptr = new Second();
    ptr->SimpleFunc();
    delete ptr;
    return 0;
}