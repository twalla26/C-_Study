#include <iostream>
using namespace std;

int main(void) {
    int num = 10;
    int i = 0;

    cout << "true: " << true << endl; // true != (1�� �ǹ��ϴ� Ű����), true�� ����ϰų� ������ �� ��ȯ�� �� ��쿡 1�� ��ȯ��.
    cout << "false: " << false << endl; // false�� ��������..

    while (true) { // ���ѷ��� ������ �� true or 1 ���
        cout << i++ << ' '; // (cout << i++): i�� ����ϸ鼭 +1�� ����
        if (i > num) // ���ѷ����� ������ ���ǹ�
            break; // �ݺ��� ����
    }
    cout << endl;

    cout << "sizeof 1: " << sizeof(1) << endl; // sizeof(): ����, �ڷ��� ���� ���� byte, �޸� ����
    cout << "sizeof 0: " << sizeof(0) << endl;
    cout << "sizeof true: " << sizeof(true) << endl;
    cout << "sizeof false: " << sizeof(false) << endl;
    // �������� ���� 4byte�� ����������, true, false�� �Ҹ����� 1byte�� �����Ѵ�.
    return 0;
}
