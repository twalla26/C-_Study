#include <iostream>
using namespace std;

class First {
public:
    void FirstFunc() { cout << "FirstFunc()" << endl; }
    virtual void SimpleFunc() { cout << "First's SimpleFunc()" << endl; } // virtual 선언
};

class Second : public First {
public:
    void SecondFunc() { cout << "SecondFunc()" << endl; }
    virtual void SimpleFunc() { cout << "Second's SimpleFunc()" << endl; } // virtual 선언
};

class Third: public Second {
public:
    void ThirdFunc() { cout << "ThirdFunc()" << endl; }
    virtual void SimpleFunc() { cout << "Third's SimpleFunc()" << endl; } // virtual 선언
};

int main(void) {
    Third obj; // Third형 객체 obj 생성
    obj.FirstFunc(); // Third 클래스가 Second, First 클래스를 상속받으니, 각각의 멤버변수 호출 가능
    obj.SecondFunc();
    obj.ThirdFunc();
    obj.SimpleFunc(); // obj는 Third 클래스의 객체이므로 가장 마지막에 오버라이딩 된 Third 클래스의 SimpleFunc를 호출

    Second & sref = obj; // obj는 Second 클래스를 직접참조하는 Third형 객체이므로, Second형 참조자로 참조 가능
    sref.FirstFunc(); // 컴파일러는 참조자의 자료형을 가지고 함수의 호출가능성을 판단하기 때문에
    sref.SecondFunc(); // sref는 Third형 객체 obj를 참조하지만, ThirdFunc() 함수는 호출 불가능
    sref.SimpleFunc();
    // SimpleFunc 함수는 가상함수이므로, sref가 실제로 참조하는 객체(Third형 객체)를 대상으로 함수 호출
    // -> 가장 마지막에 오버라이딩된 Third클래스에 정의된 함수가 호출됨.

    First & fref = obj; // obj는 First 클래스를 간접참조하는 Third형 객체이므로, First형 참조자로 참조 가능
    fref.FirstFunc(); // First형 참조자이므로, FirstFunc() 함수만 호출 가능
    fref.SimpleFunc();
    // SimpleFunc 함수는 가상함수이므로, fref가 실제로 참조하는 객체(Third형 객체)를 대상으로 함수 호출
    // -> 가장 마지막에 오버라이딩된 Third클래스에 정의된 함수가 호출됨.
    return 0;
}