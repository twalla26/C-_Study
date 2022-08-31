#include <iostream>
#include <cstring> // ���ڿ��� �迭�� ����

using namespace std;
const int NAME_LEN = 20; // const: ��ü �Ǵ� ������ ������ �� ����.

void ShowMenu(void); // �޴� ���
void MakeAccount(void); // ���°����� ���� �Լ�
void DepositMoney(void); // �� ��
void WithdrawMoney(void); // �� ��
void ShowAllAccInfo(void); // �ܾ���ȸ

enum {MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT}; // enum: ����� ���� �ڷ���
// {} ���� ��ҵ��� ������(enumerator), �� �����ڴ� ��ǥ�� ����
// �� �����ڴ� ���� ����� ��ġ�� ���� ���� ���� �ڵ����� �Ҵ��. ���ǵ��� ���� ��� �����ڴ� ���� �����ں��� 1��ŭ �� ū ���� �ο���.

typedef struct { // typedef: ������ �Լ� -> ���ϴ� ������ ������ ���ο� ������ ������.
    // struct: ����ü ���� -> ���ο� ������ ������ ����� ��� ������ �����Ͽ� ����ü Ÿ���� ���ο� �޸� ���� �Ҵ�
    int accID; // ���� ��ȣ
    int balance; // �� ��
    char cusName[NAME_LEN]; // ���̸�
} Account; // ����ü ���� ��, Account ��� ������ ���� -> ���� ����ü ������ Account twalla;�� �����ϰ� �� �� �ִ�.

Account accArr[100]; // Account ������ ���� �迭
int accNum = 0; // ��ϵǴ� ���µ� ������ ���ϱ� ���� ���� num

int main(void) {
    int choice; // ����ڰ� ������ �޴� ��ȣ

    while (1) { // 1 -> True
        ShowMenu(); // ShowMenu()�Լ� ���� -> �޴��� ������
        cout << "����: ";
        cin >> choice; // ������� ������ ����.
        cout << endl; // choice �Է� ��, �ٹٲ�

        switch (choice) { // switch�� -> if������ �Ϲ������� �� ȿ������.
            // switch (���� ���)
            case MAKE: // case �񱷰�, �񱷰����� ����� �� �� ����. MAKE�� ��쿡�� 1 -> if (choice == 1) �� ���� ����
                MakeAccount(); // choice == 1�� ���, MakeAccount()�Լ� ����
                break; // case���� ��

            case DEPOSIT:
                DepositMoney();
                break;

            case WITHDRAW:
                WithdrawMoney();
                break;

            case INQUIRE:
                ShowAllAccInfo();
                break;

            case EXIT:
                return 0;

            default: // � case���� ���� ������ default�� �����.
                cout << "Illegal selection.." << endl;
        }
    }
    return 0;
}

void ShowMenu(void) { // �޴� �����ִ� �Լ� ����
    cout << "-----Menu-----" << endl;
    cout << "1. ���°���" << endl;
    cout << "2. �� ��" << endl;
    cout << "3. �� ��" << endl;
    cout << "4. �������� ��ü ���" <<endl;
    cout << "5. ���α׷� ����" << endl;
}

void MakeAccount(void) { // ���°��� �Լ� ����
    int id; // ���� id
    char name[NAME_LEN]; // ����� �̸�, MAKE_LEN�� 20���� �����Ǿ� ���� -> ����� �̸��� 20�� ���� �� ����
    int balance; // ���¿� �ִ� �ݾ�

    // ����ڿ��� ���� ������ �޾Ƽ� ������ ����
    cout << "[���°���]" << endl;
    cout << "����ID: "; cin >> id;
    cout << "�� ��: "; cin >> name;
    cout << "�Աݾ�: "; cin >> balance;
    cout << endl;

    // ���� ������ accArr�� ����
    accArr[accNum].accID = id; // ũ�Ⱑ [accNum]�� ����ü �迭 ���� -> �ε����� ��ҿ� ���� ��, .���� ����� ����
    accArr[accNum].balance = balance;
    strcpy(accArr[accNum].cusName, name); // strcpy: string copy -> ���ڿ��� �����ϴ� �Լ�, name�� ����� ���ڿ��� accArr[accNum].cusName�� ����
    accNum++; // ������ ����Ǵ� ������ ���� id�� 1 ����
}

void DepositMoney(void) { // �Ա� �Լ� ����
    int money; // �Աݾ�
    int id; // ���� id

    cout << "[�� ��]" << endl;
    cout << "����ID: "; cin >> id;
    cout << "�Աݾ�: "; cin >> money;

    for (int i = 0; i < accNum; i++) { // �Է¹��� ����id�� ����Ǿ� �ִ� ���� �߿� �ش� ���¸� ã��.
        if (accArr[i].accID == id) { // ã���ִ� ������ id�� ����Ǿ� �ִ� ������ id�� ������
            accArr[i].balance += money; // ���¿� money �߰�
            cout << "�ԱݿϷ�" << endl << endl;
            return;
        }
    }
    cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl; // �ش� ���¸� ã�� ����.
}

void WithdrawMoney(void) { // ��� �Լ� ����
    int money; // ��ݾ�
    int id; // ���� ID

    cout << "[�� ��]" << endl;
    cout << "����ID: "; cin >> id;
    cout << "��ݾ�: "; cin >> money;

    for (int i = 0; i < accNum; i++) { // �Է¹��� ID�� ���� ã��
        if (accArr[i].accID == id) { // ���¸� ã����
            if (accArr[i].balance < money) { // ���� ���¿� �ִ� �ݾ׺��� ��ݾ��� �� ũ��
                cout << "�ܾ׺���" << endl << endl; // ��� �Ұ�
                return;
            }

            accArr[i].balance -= money; // ����� ������ ��� -> ������ �ݾ׿��� ��ݾ��� ���ش�.
            cout << "��ݿϷ�" << endl << endl;
            return;
        }
    }
    cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl; // �ش� ���¸� ã�� ����.
}

void ShowAllAccInfo(void) { // ��ü ���� ������ ����ϴ� �Լ� ����
    for (int i = 0; i < accNum; i++) { // ������ ���µ鿡 ����
        cout << "����ID: " << accArr[i].accID << endl;
        cout << "�� ��: " << accArr[i].cusName << endl;
        cout << "�� ��: " << accArr[i].balance << endl << endl;
    }
}