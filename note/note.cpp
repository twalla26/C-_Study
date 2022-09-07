#include <iostream>
using namespace std;

class First {
public:
    void FirstFunc() { cout << "FirstFunc()" << endl; }
    virtual void SimpleFunc() { cout << "First's SimpleFunc()" << endl; } // virtual ����
};

class Second : public First {
public:
    void SecondFunc() { cout << "SecondFunc()" << endl; }
    virtual void SimpleFunc() { cout << "Second's SimpleFunc()" << endl; } // virtual ����
};

class Third: public Second {
public:
    void ThirdFunc() { cout << "ThirdFunc()" << endl; }
    virtual void SimpleFunc() { cout << "Third's SimpleFunc()" << endl; } // virtual ����
};

int main(void) {
    Third obj; // Third�� ��ü obj ����
    obj.FirstFunc(); // Third Ŭ������ Second, First Ŭ������ ��ӹ�����, ������ ������� ȣ�� ����
    obj.SecondFunc();
    obj.ThirdFunc();
    obj.SimpleFunc(); // obj�� Third Ŭ������ ��ü�̹Ƿ� ���� �������� �������̵� �� Third Ŭ������ SimpleFunc�� ȣ��

    Second & sref = obj; // obj�� Second Ŭ������ ���������ϴ� Third�� ��ü�̹Ƿ�, Second�� �����ڷ� ���� ����
    sref.FirstFunc(); // �����Ϸ��� �������� �ڷ����� ������ �Լ��� ȣ�Ⱑ�ɼ��� �Ǵ��ϱ� ������
    sref.SecondFunc(); // sref�� Third�� ��ü obj�� ����������, ThirdFunc() �Լ��� ȣ�� �Ұ���
    sref.SimpleFunc();
    // SimpleFunc �Լ��� �����Լ��̹Ƿ�, sref�� ������ �����ϴ� ��ü(Third�� ��ü)�� ������� �Լ� ȣ��
    // -> ���� �������� �������̵��� ThirdŬ������ ���ǵ� �Լ��� ȣ���.

    First & fref = obj; // obj�� First Ŭ������ ���������ϴ� Third�� ��ü�̹Ƿ�, First�� �����ڷ� ���� ����
    fref.FirstFunc(); // First�� �������̹Ƿ�, FirstFunc() �Լ��� ȣ�� ����
    fref.SimpleFunc();
    // SimpleFunc �Լ��� �����Լ��̹Ƿ�, fref�� ������ �����ϴ� ��ü(Third�� ��ü)�� ������� �Լ� ȣ��
    // -> ���� �������� �������̵��� ThirdŬ������ ���ǵ� �Լ��� ȣ���.
    return 0;
}