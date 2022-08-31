/*
 * Banking System Ver 0.3
 * �ۼ���: �ۼ���
 * ����: ���� ���縦 �ϴ� ���� ������ �߰�
 */

#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;

void ShowMenu(void); // �޴����
void MakeAccount(void); // ���°����� ���� �Լ�
void DepositMoney(void); // �Ա�
void WithdrawMoney(void); // ���
void ShowAllAccInfo(void); // �ܾ���ȸ

enum {MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT};

class Account { // ���� Ŭ����
private:
    int accID; // ���¹�ȣ
    int balance; // �ܾ�
    char * cusName; // ���̸�

public:
    Account(int ID, int money, char * name) // ������
            : accID(ID), balance(money) {
        cusName = new char[strlen(name) + 1]; // cusName ���� �Ҵ�, �迭 ũ�� ����
        strcpy(cusName, name); // cusName <- name
    }

    Account(const Account & ref) // ���� ������ ����(���� ����)
        : accID(ref.accID), balance(ref.balance) {
        cusName = new char[strlen(ref.cusName) + 1]; // cusName�� �����Ҵ�Ǵ�, ���� �����ڿ��� ���Ӱ� �Ҵ�!
        strcpy(cusName, ref.cusName);
    }

    int GetAccID() { // ����ID ��ȯ �Լ�
        return accID;
    }

    void Deposit(int money) { // �Ա� �Լ�
        balance += money;
    }

    int Withdraw(int money) { // ��� �Լ�
        if (balance < money) { // �ܾ��� ��ݾ׺��� ���� ��
            return 0; // ��� �Ұ�
        }
        // ��� ������ ��
        balance -= money; // �ܾ׿��� ��ݾ��� ����
        return money; // ��ݾ� ��ȯ
    }

    void ShowAccInfo() { // ���� ���� ��� �Լ�
        cout << "����ID: " << accID << endl;
        cout << "�̸�: " << cusName << endl;
        cout << "�ܾ�: " << balance << endl;
    }

    ~Account() { // �Ҹ���
        delete []cusName; // �����Ҵ�� cusName �޸� ����
    }
};

Account * accArr[100]; // Account ��ü ������ ���� �迭
int accNum = 0; // ����� Account ��

int main(void) {
    int choice; // ����ڰ� ������ �޴�

    while (1) {
        ShowMenu(); // �޴� �Լ� ȣ��
        cout << "����: ";
        cin >> choice; // �޴� ���� ���� �� choice�� ����
        cout << endl;

        switch (choice) {
            case MAKE: // choice�� 1�̶��
                MakeAccount(); // ���� ���� �Լ� ȣ��
                break;
            case DEPOSIT:
                DepositMoney();
                break;
            case WITHDRAW:
                WithdrawMoney();
                break;
            case INQUIRE:
                ShowAllAccInfo();
                break;
            case EXIT: // choice�� 5���
                for (int i = 0; i < accNum; i++) { // ����� ���µ� �ϳ��ϳ�
                    delete accArr[i]; // �޸� ����
                }
                return 0;
            default: // choice�� 1,2,3,4,5 ���� ���ڶ��
                cout << "Illegal selection.." << endl; // ����
        }
    }

    return 0;
}

void ShowMenu(void) { // �޴� ��� �� ���� �Լ�
    cout << "-----Menu-----" << endl;
    cout << "1. ���°���" << endl;
    cout << "2. �Ա�" << endl;
    cout << "3. ���" << endl;
    cout << "4. �������� ��ü ���" << endl;
    cout << "5. ���α׷� ����" << endl;
}

void MakeAccount(void) { // ���� ���� �Լ�
    int id; // ���� ID
    char name[NAME_LEN]; // �̸�, ���̴� 20 ����
    int balance; // �ܾ�

    cout << "[���°���]" << endl;
    cout << "����ID: "; cin >> id;
    cout << "�̸�: "; cin >> name;
    cout << "�Աݾ�: "; cin >> balance;
    cout << endl;

    accArr[accNum++] = new Account(id, balance, name); // �Է� ���� ������ ���� ���� ��, ���� ��ü �迭�� ��ü �ּ� ����
}

void DepositMoney(void) { // �Ա� �Լ�
    int money; // �Ա��� ��
    int id; // ����ID
    cout << "[�Ա�]" << endl;
    cout << "����ID: "; cin >> id; // ID ����
    cout << "�Աݾ�: "; cin >> money; // �Ա��� �� ����

    for (int i = 0; i < accNum; i++) { // ����� ���� �ϳ��ϳ�
        if (accArr[i]->GetAccID() == id) { // �Է� ���� ���� ID�� ���� �� ã�Ƽ�
            accArr[i]->Deposit(money); // �� �Ա�
            cout << "�ԱݿϷ�" << endl << endl;
            return;
        }
    }
    cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl; // ã�� ���°� ������ ����
}

void WithdrawMoney(void) { // ��� �Լ�
    int money; // ��ݾ�
    int id; // ���¹�ȣ
    cout << "[���]" << endl;
    cout << "����ID: "; cin >> id;
    cout << "��ݾ�: "; cin >> money;

    for (int i = 0; i < accNum; i++) { // ����� ���� �ϳ��ϳ�
        if (accArr[i]->GetAccID() == id) { // �Է¹��� ��ȣ�� ���� �� ã�Ƽ�
            if (accArr[i]->Withdraw(money) == 0) { // ���� ��ȯ���� 0(��� �Ұ���)
                cout << "�ܾ׺���" << endl; // �ܾ׺��� �˸�
                return;
            }
            // ��� �����ϴٸ�
            cout << "��ݿϷ�" << endl << endl;
            return;
        }
    }
    // ���¸� ã�� ���ϸ�
    cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl;
}

void ShowAllAccInfo(void) { // ���� ���� ��� �Լ�
    for (int i = 0; i < accNum; i++) { // ����� ���� �ϳ��ϳ�
        accArr[i]->ShowAccInfo(); // ���� ���� ��� �Լ� ȣ��
        cout << endl;
    }
}