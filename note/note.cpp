#include <iostream>
using namespace std;

class SoSimple {
private:
    int num1;
    mutable int num2; // const �Լ� ������ ������ ����.
public:
    SoSimple(int n1, int n2) : num1(n1), num2(n2) {} // ������
    void ShowSimpleData() const { // const �Լ�
        cout << num1 << ", " << num2 << endl;
    }
    void CopyToNum2() const { // const �Լ� -> ��� ������ ���� ������ �� ������!!
        num2 = num1; // num2�� mutable�� ����Ǿ� const �Լ����� ������ ����.
    }
};

int main(void) {
    SoSimple sm(1, 2); // ��ü ����
    sm.ShowSimpleData(); // 1, 2 ���
    sm.CopyToNum2(); // mutable�� ����� num2�� ���� �ٲ�.
    sm.ShowSimpleData(); // 1, 1 ���
    return 0;
}