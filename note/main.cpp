#include <iostream>
using namespace std;

class FruitSeller { // ���� �Ǹ��� Ŭ���� ����
private:
    int APPLE_PRICE; // �Ǹ��ϴ� ��� ����(�빮�� -> ������ �ʴ� ������ �Ͻ�)
    int numOfApples; // ��� ����
    int myMoney; // �Ǹ����� ��

public:
    void InitMembers(int price, int num, int money) { // (�Ǹ��� ��� ����, ������ �ִ� ��� ����, ������ �ִ� ��)
        APPLE_PRICE = price;
        numOfApples = num;
        myMoney = money;
    }

    int SaleApples(int money) { // ��� �Ǹ� �Լ�, �μ��� �����ڰ� �� ���� ����
        int num = money/APPLE_PRICE; // num: �� ��� ����(�����ڰ� �� ��/��� ����)
        numOfApples -= num; // �Ǹ��� ���� ��� ���� - �� ��� ����
        myMoney += money; // �� + ���� ��
        return num; // �Ǹ��� ��� ���� ��ȯ
    }

    void ShowSalesResult() { // �Ǹ� ��Ȳ �Լ�
        cout << "���� ���: " << numOfApples << endl;
        cout << "�Ǹ� ����: " << myMoney << endl;
    }
};

class FruitBuyer { // ��� ������ Ŭ���� ����
private:
    int myMoney; // ������ ��
    int numOfApples; // �����ڰ� �� �� ��� ����

public:
    void InitMembers(int money) { // (�����ڰ� ���� ��)
        myMoney = money;
        numOfApples = 0; // �����ڰ� ������ ��� ����
    }

    void BuyApples(FruitSeller &seller, int money) { // ��� ���� �Լ� (�Ǹ��� ������ ����, �����ϱ� ���� �� ��)
        numOfApples += seller.SaleApples(money); // ������ ���� ��� ������, �Ǹ��ڿ��� �� ��� ������ ����. public -> �Լ� ȣ�� ��𼭳� ����
        myMoney -= money; // ���� �� ��ŭ ����
    }

    void ShowBuyResult() { // ���� ��� �Լ�
        cout << "���� �ܾ�: " << myMoney << endl;
        cout << "��� ����: " << numOfApples << endl << endl;
    }
};

int main(void) {
    FruitSeller seller; // seller ��ü ����
    seller.InitMembers(1000, 20, 0); // ��� ����: 1000, ����: 20, ��: 0
    FruitBuyer buyer; // buyer ��ü ����
    buyer.InitMembers(5000); // ��: 5000
    buyer.BuyApples(seller, 2000); // ������ ����!!, seller ��ü���� 2000�� ����

    cout << "���� �Ǹ����� ��Ȳ" << endl;
    seller.ShowSalesResult();
    cout << "���� �������� ��Ȳ" << endl;
    buyer.ShowBuyResult();
    return 0;
}