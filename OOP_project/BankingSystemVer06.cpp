/*
 * Banking System Ver 0.6
 * �ۼ���: �ۼ���
 * �� ��: ���ڰ��� ���� Ŭ������ �߰�
 */

#include <iostream>
#include <cstring>

using namespace std; // �̸� ����
const int NAME_LEN=20; // �������� ����, const ����!;

// ���α׷� ������� ���� �޴�
enum {MAKE=1, DEPOSIT, WITHDRAW, INQUIRE, EXIT}; // ������: ����� ���� �ڷ���, �ڵ幮��ȭ �� ������ ���� or ���� ����

// �ſ���
enum {LEVEL_A=7, LEVEL_B=4, LEVEL_C=2}; // ���ڴ� ����

// ������ ����
enum {NORMAL=1, CREDIT=2}; // NORMAL: ���뿹�ݰ���, CREDIT: �ſ�ŷڰ���

/*
 * Ŭ���� �̸�: Account
 * Ŭ���� ����: Entity Ŭ����
 */

class Account {
private:
    int accID; // ���¹�ȣ
    int balance; // �� ��
    char * cusName; // �����
public:
    Account(int ID, int money, char * name); // ������
    Account(const Account & ref); // ���������, Account ��ü�� �޾� ������, const ����(�Լ� ���� ���� �Ұ�)!!

    int GetAccID() const; // ���¹�ȣ ��ȯ �Լ�, const ���� -> ������� ���� X
    virtual void Deposit(int money); // �Ա� �Լ�, virtual ���� -> ������ ������ ������ ����Ű�� ��ü�� ������� �Լ� ȣ��
    int Withdraw(int money); // ��� �Լ�
    void ShowAccInfo() const; // ���� ���� ��� �Լ�
    ~Account();
};

Account::Account(int ID, int money, char *name) // Account Ŭ������ ������ ����
    : accID(ID), balance(money) { // ��� �̴ϼȶ����� -> ����� ���ÿ� �ʱ�ȭ
    cusName = new char[strlen(name)+1];  // ���� �Ҵ� -> �迭 ĭ �Ҵ�
    strcpy(cusName, name);
}

Account::Account(const Account &ref) // Account Ŭ������ ��������� ����, ���ڷ� ���� Account ��ü ref�� ������, const ����!
    : accID(ref.accID), balance(ref.balance) {
    cusName = new char[strlen(ref.cusName)+1];
    strcpy(cusName, ref.cusName);
}

int Account::GetAccID() const { return accID; } // ���� ��ȯ �Լ� ����

void Account::Deposit(int money) { // �Ա� �Լ�, ���ڷ� �Ա��� ���� ����
    balance += money; // �ܾ� + �Աݾ�
}

int Account::Withdraw(int money) { // ��� �Լ�, ���ڷ� ����� ���� ����
    if (balance < money) { // ���� �ܾ��� ��ݾ׺��� ���ٸ�
        return 0; // ��� �Ұ� -> 0 ��ȯ
    }
    // ���� ���ǿ� �ɸ��� �ʾҴٸ�(����� �����ϴٸ�)
    balance -= money; // �ܾ� - ��ݾ�
    return money; // ��ݾ� ��ȯ
}

void Account::ShowAccInfo() const { // ���� ���� ��� �Լ�
    cout << "����ID: " << accID << endl;
    cout << "�� ��: " << cusName << endl;
    cout << "�� ��: " << balance << endl;
}

Account::~Account() { // �Ҹ��� ����
    delete []cusName; // �����Ҵ�� �޸� ����
}

/*
 * Ŭ���� �̸�: NormalAccount
 * Ŭ���� ����: Entity Ŭ����
 */

class NormalAccount : public Account { // Account Ŭ������ public���� �������
private:
    int interRate; // ������ % ����
public:
    NormalAccount(int ID, int money, char * name, int rate) // ������
        : Account(ID, money, name), interRate(rate) {} // ��� �̴ϼȶ����� -> �θ�Ŭ���� ������ ȣ��

    virtual void Deposit(int money) { // �Ա� �Լ�, virtual ���� -> ������ ������ ������ ����Ű�� ��ü�� ������� �Լ� ȣ��
        Account::Deposit(money); // ���� �߰�, Account Ŭ������ Deposit �Լ� ȣ��!!
        Account::Deposit(money*(interRate/100.0)); // ���� �߰�
    }
};

/*
 * Ŭ���� �̸�: HighCreditAccount
 * Ŭ���� ����: Entity Ŭ����
 */

class HighCreditAccount : public NormalAccount { // NormalAccount Ŭ������ public���� ��ӹ���.
private:
    int specialRate; // �ſ� ���
public:
    HighCreditAccount(int ID, int money, char * name, int rate, int special) // ������
        : NormalAccount(ID, money, name, rate), specialRate(special) {}

    virtual void Deposit(int money) { // �Ա� �Լ�, virtual ���� -> ������ ������ ������ ����Ű�� ��ü�� ������� �Լ� ȣ��
        NormalAccount::Deposit(money); // ���ݰ� ���� �߰�
        Account::Deposit(money*(specialRate/100.0)); // Ư�� ���� �߰�
    }
};

/*
 * Ŭ���� �̸�: AccountHandler
 * Ŭ���� ����: ��Ʈ��(control) Ŭ����
 */

class AccountHandler {
private:
    Account * accArr[100]; // ���� ��ü���� �ּҰ� ����� �迭
    int accNum; // ����� ���� ��ü���� �ּ�
public:
    AccountHandler(); // ������
    void ShowMenu(void) const; // �޴� ���, �Լ��� const ���� -> ������� ���� �Ұ�, const �Լ��� ȣ�� ����
    void MakeAccount(void); // ���� ���� �Լ�
    void DepositMoney(void); // �Ա� �Լ�
    void WithdrawMoney(void); // ��� �Լ�
    void ShowAllAccInfo(void) const; // ��� ���� ���� ��� �Լ�
    ~AccountHandler(); // �Ҹ���
protected: // protected ����!!
    void MakeNormalAccount(void); // ���뿹�ݰ��� ����
    void MakeCreditAccount(void); // �ſ�ŷڰ��� ����
};

void AccountHandler::ShowMenu() const { // �޴� ���, �Լ��� const ���� -> ������� ���� �Ұ�, const �Լ��� ȣ�� ����
    cout << "-----Menu-----" << endl;
    cout << "1. ���°���" << endl;
    cout << "2. �� ��" << endl;
    cout << "3. �� ��" << endl;
    cout << "4. �������� ��ü ���" << endl;
    cout << "5. ���α׷� ����" << endl;
}

void AccountHandler::MakeAccount() { // ���� ���� �Լ�
    int sel; // ����ڰ� �Է��� ��ȣ
    cout << "[������������]" << endl;
    cout << "1. ���뿹�ݰ��� ";
    cout << "2. �ſ�ŷڰ���" << endl;
    cout << "����: ";
    cin >> sel;

    if (sel==NORMAL) { // NORMAL=1, ����ڰ� 1�� �����ߴٸ�
        MakeNormalAccount(); // ���뿹�ݰ��� ���� �Լ� ȣ��
    }
    else {
        MakeCreditAccount(); // �ſ�ŷڰ��� ���� �Լ� ȣ��
    }
}

void AccountHandler::MakeNormalAccount() { // ���뿹�ݰ��� ���� �Լ� ����
    int id; // ���� ��ȣ
    char name[NAME_LEN]; // �����, �̸�ĭ�� 20���� ����
    int balance; // �� ��
    int interRate; // ������

    cout << "[���뿹�ݰ��� ����]" << endl;
    cout << "����ID: "; cin >> id;
    cout << "�� ��: "; cin >> name;
    cout << "�Աݾ�: "; cin >> balance;
    cout << "������: "; cin >> interRate;
    cout << endl;

    accArr[accNum++] = new NormalAccount(id, balance, name, interRate); // �迭�� ����
}

void AccountHandler::MakeCreditAccount() { // �ſ�ŷڰ��� ���� �Լ� ����
    int id;
    char name[NAME_LEN];
    int balance;
    int interRate; // ������
    int creditLevel; // �ſ���

    cout << "[�ſ�ŷڰ��� ����]" << endl;
    cout << "����ID: "; cin >> id;
    cout << "�� ��: "; cin >> name;
    cout << "�Աݾ�: "; cin >> balance;
    cout << "������: "; cin >> interRate;
    cout << "�ſ���(1toA, 2toB, 3toC): "; cin >> creditLevel;
    cout << endl;

    switch (creditLevel) { // �Է¹��� creditLevel�� ��
        case 1: // �ſ����� 1�̶��
            accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_A); // �迭�� ����
            break;
        case 2:
            accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_B);
            break;
        case 3:
            accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_C);
    }
}

void AccountHandler::DepositMoney() { // �Ա� �Լ�
    int money;
    int id;
    cout << "[��   ��]" << endl;
    cout << "����ID: "; cin >> id;
    cout << "�Աݾ�: "; cin >> money;

    for (int i = 0; i < accNum; i++) { // �Է¹��� ��ȣ�� �ش��ϴ� ���� ã��
        if (accArr[i]->GetAccID()==id) { // GetAccID �Լ��� ��ȯ���� �ش� ������ ��ȣ
            accArr[i]->Deposit(money); // ã���� �Ա� ����, Deposit�� �����Լ����� -> �ش� ��ü �������� �Լ� ȣ��
            cout << "�ԱݿϷ�" << endl << endl;
            return;
        }
    }
    // �ش� ���¸� ã�� ������ ��
    cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl;
}

void AccountHandler::WithdrawMoney() {
    int money;
    int id;
    cout << "[��   ��]" << endl;
    cout << "����ID: "; cin >> id;
    cout << "��ݾ�: "; cin >> money;

    for (int i = 0; i < accNum; i++) { // �ش� ���� ã��
        if (accArr[i]->GetAccID()==id) { // ���¸� ã����
            if (accArr[i]->Withdraw(money)==0) { // ��� �Ұ����ϸ�
                cout << "�ܾ׺���" << endl << endl; // �Ұ��� �ȳ�
                return;
            }
            // ��� ������ ���
            cout << "��ݿϷ�" << endl << endl;
            return;
        }
    }
    // ���¸� ã�� ���� ���
    cout << "��ȿ���� ���� ID �Դϴ�." << endl << endl;
}

AccountHandler::AccountHandler() : accNum(0) {} // ������

void AccountHandler::ShowAllAccInfo() const { // ��� ���� ���� ��� �Լ�
    for (int i = 0; i < accNum; i++) { // ��� ���µ鿡 ���ؼ�
        accArr[i]->ShowAccInfo(); // ���� ��� �Լ� ȣ��
        cout << endl;
    }
}

AccountHandler::~AccountHandler() { // �Ҹ���
    for (int i = 0; i < accNum; i++) { // ��� ����� ���� ��ü�� ���ؼ�
        delete accArr[i]; // �޸� ����
    }
}

/*
 * ��Ʈ�� Ŭ���� AccountHandler �߽��� main �Լ�
 */

int main(void) {
    AccountHandler manager;
    int choice;

    while(1) {
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