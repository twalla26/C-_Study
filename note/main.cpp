#include <iostream>
using namespace std;

int val = 10; // ��������

int SimpleFunc(void) {
    int val = 20; // ��������
    val += 3; // �������� val�� �� 3 ����
    ::val += 7; // �������� val�� �� 7 ����
}