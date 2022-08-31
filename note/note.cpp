#include <iostream>
using namespace std;

class SoSimple {
private:
    int num1;
    mutable int num2; // const 함수 내에서 변경이 허용됨.
public:
    SoSimple(int n1, int n2) : num1(n1), num2(n2) {} // 생성자
    void ShowSimpleData() const { // const 함수
        cout << num1 << ", " << num2 << endl;
    }
    void CopyToNum2() const { // const 함수 -> 멤버 변수의 값을 변경할 수 없지만!!
        num2 = num1; // num2는 mutable로 선언되어 const 함수에서 변경이 허용됨.
    }
};

int main(void) {
    SoSimple sm(1, 2); // 객체 생성
    sm.ShowSimpleData(); // 1, 2 출력
    sm.CopyToNum2(); // mutable로 선언된 num2의 값이 바뀜.
    sm.ShowSimpleData(); // 1, 1 출력
    return 0;
}