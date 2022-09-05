/*
 * Banking System Ver 0.5
 * �ۼ���: �ۼ���
 * �� ��: AccountHandler��� �̸��� ��Ʈ�� Ŭ���� ����
 */

#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20; // �̸� ���� ���� 20

enum {MAKE=1, DEPOSIT, WITHDRAW, INQUIRE, EXIT};

/*
 * Ŭ���� �̸�: Account
 * Ŭ���� ����: Entity Ŭ����
 */

class Account { // ���� ���� ���� Ŭ����
private:
    int accID; // ���� ID
    int balance; // �� ��
    char * cusName; // ����� �̸�
public:
    Account(int ID, int money, char * name); // ������
    Account(const Account & ref); // ���� ������

    int GetAccID() const; // ����ID ��ȯ �Լ�
    void Deposit(int money); // ���� �Լ�
    int Withdraw(int money); // ��� �Լ�
    void ShowAccInfo() const; // ���� ���� ��� �Լ�
    ~Account(); // �Ҹ���
};

Account::Account(int ID, int money, char *name) // ������
    : accID(ID), balance(money) {
    cusName = new char[strlen(name)+1]; // ���� �Ҵ�
    strcpy(cusName, name);
}

Account::Account(const Account &ref)
    : accID(ref.accID), balance(ref.balance) {
    cusName = new char[strlen(ref.cusName)+1]; // ���� �Ҵ�
    strcpy(cusName, ref.cusName);
}

int Account::GetAccID() const { return accID; }

void Account::Deposit(int money) {
    balance += money;
}

int Account::Withdraw(int money) {
    if (balance < money) { // ����� ���� �����ϴٸ�
        return 0; // 0 ��ȯ
    }
    // ��� �����ϴٸ�
    balance -= money; // ���
    return money; // ����� �� ��ȯ
}

void Account::ShowAccInfo() const {
    cout << "����ID: " << accID << endl;
    cout << "�� ��: " << cusName << endl;
    cout << "�� ��: " << balance << endl;
}

Account::~Account() { // �Ҹ���
    delete []cusName; // �޸� ����
}

/*
 * Ŭ���� �̸�: AccountHandler
 * Ŭ���� ����: ��Ʈ��(Control) Ŭ����
 */

class AccountHandler { // ��Ʈ�� Ŭ����
private:
    Account * accArr[100]; // ���� ��ü�� ������ �迭
    int accNum; // ����� ������ �� ����
public:
    AccountHandler();
    void ShowMenu(void) const;
    void MakeAccount(void);
    void DepositMoney(void);
    void WithdrawMoney(void);
    void ShowAllAccInfo(void) const;
    ~AccountHandler();
};

void AccountHandler::ShowMenu() const { // �޴� ��� �Լ�
    cout << "-----Menu-----" << endl;
    cout << "1. ���°���" << endl;
    cout << "2. �� ��" << endl;
    cout << "3. �� ��" << endl;
    cout << "4. �������� ��ü ���" << endl;
    cout << "5. ���α׷� ����" << endl;
}

void AccountHandler::MakeAccount() { // ���� ���� �Լ�
    int id;
    char name[NAME_LEN];
    int balance;

    cout << "[���°���]" << endl;
    cout << "����ID: "; cin >> id;
    cout << "�� ��: "; cin >> name;
    cout << "�Աݾ�: "; cin >> balance;
    cout << endl;

    accArr[accNum++] = new Account(id, balance, name); // ���� ��ü ���� �Ҵ�
}

void AccountHandler::DepositMoney() { // ���� �Լ�
    int money; // ������ ��
    int id;
    cout << "[��   ��]" << endl;
    cout << "����ID: "; cin >> id;
    cout << "�Աݾ�: "; cin >> money;

    for (int i = 0; i < accNum; i++) {
        if (accArr[i]->GetAccID() == id) {
            accArr[i]->Deposit(money);
            cout << "�ԱݿϷ�" << endl << endl;
            return;
        }
    }
    cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl;
}

void AccountHandler::WithdrawMoney() { // ��� �Լ�
    int money; // ����� ��
    int id;
    cout << "[��   ��]" << endl;
    cout << "����ID: "; cin >> id;
    cout << "��ݾ�: "; cin >> money;

    for (int i = 0; i < accNum; i++) {
        if (accArr[i]->GetAccID() == id) {
            if (accArr[i]->Withdraw(money) == 0) { // �ܾ� �����̸� 0 ��ȯ
                cout << "�ܾ׺���" << endl << endl;
                return;
            }

            cout << "��ݿϷ�" << endl << endl;
            return;
        }
    }
    cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl;
}

AccountHandler::AccountHandler() : accNum(0) {} // ������, ���� ������ 0���� �ʱ�ȭ

void AccountHandler::ShowAllAccInfo() const { // ��� ���� ���� ��� �Լ�
    for (int i = 0; i < accNum; i++) {
        accArr[i]->ShowAccInfo();
        cout << endl;
    }
}

AccountHandler::~AccountHandler() { // �Ҹ���
    for (int i = 0; i < accNum; i++) {
        delete accArr[i]; // �����Ҵ��� ���� ��ü �޸� ����
    }
}

/*
 * ��Ʈ�� Ŭ���� AccountHandler �߽����� ����� main �Լ�
 */

int main(void) {
    AccountHandler manager; // ��ü ����
    int choice;

    while (1) {
        manager.ShowMenu();
        cout << "����: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case MAKE:
                manager.MakeAccount();
                break;
            case DEPOSIT:
                manager.DepositMoney();
                break;
            case WITHDRAW:
                manager.WithdrawMoney();
                break;
            case INQUIRE:
                manager.ShowAllAccInfo();
                break;
            case EXIT:
                return 0;
            default:
                cout << "Illegal selection.." << endl;
        }
    }
    return 0;
}