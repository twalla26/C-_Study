#include <iostream>
using namespace std;

// #define: ��ũ�� ���� -> �����Ϸ��� ������ ����, ��ó����.
#define ID_LEN 20
#define MAX_SPD 200
#define FUEL_STEP 2
#define ACC_STEP 10
#define BRK_STEP 10
// ��ũ�� ��� -> �̸� ������ ��ũ�� ������� ���̸�, ��ũ�� Ȯ�� ���ڿ��� ġȯ��.

struct Car { // Car ����ü ����
    char gamerID[ID_LEN]; // ������ ID
    int fuelGauge; // ���ᷮ
    int curSpeed; // ����ӵ�

    void ShowCarState() { // ���� ���� ���� ��� �Լ�
        cout << "������ID: " << gamerID << endl; // ���� ����� gamerID�� ����
        cout << "���ᷮ: " << fuelGauge << "%" << endl;
        cout << "����ӵ�: " << curSpeed << "km/s" << endl << endl;
    }

    void Accel() { // ���� �Լ�
        if (fuelGauge <= 0) // ���� ����� fuelGauge�� ����
            return; // ���� �� ����.
        else // ���� ���ᷮ�� �ִٸ�,
            fuelGauge -= FUEL_STEP; // ���� ���ᷮ���� FUEL_STEP(2)�� ��.

        if (curSpeed + ACC_STEP >= MAX_SPD) { // ���� ���� ����ӵ��� ������ ���� ��ŭ�� �ӵ�(10)�� ���� ���� �ְ� �ӵ�(200)���� ũ��
            curSpeed = MAX_SPD; // ���� �ӵ��� �ְ�ӵ��� ����.
            return;
        }

        curSpeed += ACC_STEP; // ���� ����ӵ��� ������ ���� ��ŭ�� �ӵ��� ���� ���� �ְ� �ӵ����� ������,
        // ���� �ӵ��� ACC_STEP(10)�� ���� �� ����.
    }

    void Break() { // �극��ũ �Լ�
        if (curSpeed < BRK_STEP) { // ���� �ӵ��� �극��ũ�� ������ �پ��� �ӵ���(10)���� ������
            curSpeed = 0; // �� �ӵ��� 0
            return;
        }

        curSpeed -= BRK_STEP; // �װ� �ƴ϶��, �� �ӵ����� 10�� ��.
    }

};


int main(void) {
    Car run99 = {"run99", 100, 0}; // run99��� �̸��� Car ����ü ����
    Car sped77 = {"sped77", 100, 0};
    return 0;
}