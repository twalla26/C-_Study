/*
 * Banking System Ver 0.5
 * 작성자: 송수민
 * 내 용: AccountHandler라는 이름의 컨트롤 클래스 정의
 */

#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20; // 이름 길이 제한 20

enum {MAKE=1, DEPOSIT, WITHDRAW, INQUIRE, EXIT};

/*
 * 클래스 이름: Account
 * 클래스 유형: Entity 클래스
 */

class Account { // 계좌 정보 정의 클래스
private:
    int accID; // 계좌 ID
    int balance; // 잔 액
    char * cusName; // 사용자 이름
public:
    Account(int ID, int money, char * name); // 생성자
    Account(const Account & ref); // 복사 생성자

    int GetAccID() const; // 계좌ID 반환 함수
    void Deposit(int money); // 예금 함수
    int Withdraw(int money); // 출금 함수
    void ShowAccInfo() const; // 계좌 정보 출력 함수
    ~Account(); // 소멸자
};

Account::Account(int ID, int money, char *name) // 생성자
    : accID(ID), balance(money) {
    cusName = new char[strlen(name)+1]; // 동적 할당
    strcpy(cusName, name);
}

Account::Account(const Account &ref)
    : accID(ref.accID), balance(ref.balance) {
    cusName = new char[strlen(ref.cusName)+1]; // 동적 할당
    strcpy(cusName, ref.cusName);
}

int Account::GetAccID() const { return accID; }

void Account::Deposit(int money) {
    balance += money;
}

int Account::Withdraw(int money) {
    if (balance < money) { // 출금할 돈이 부족하다면
        return 0; // 0 반환
    }
    // 출금 가능하다면
    balance -= money; // 출금
    return money; // 출금한 돈 반환
}

void Account::ShowAccInfo() const {
    cout << "계좌ID: " << accID << endl;
    cout << "이 름: " << cusName << endl;
    cout << "잔 액: " << balance << endl;
}

Account::~Account() { // 소멸자
    delete []cusName; // 메모리 해제
}

/*
 * 클래스 이름: AccountHandler
 * 클래스 유형: 컨트롤(Control) 클래스
 */

class AccountHandler { // 컨트롤 클래스
private:
    Account * accArr[100]; // 계좌 객체를 저장할 배열
    int accNum; // 저장된 계좌의 총 개수
public:
    AccountHandler();
    void ShowMenu(void) const;
    void MakeAccount(void);
    void DepositMoney(void);
    void WithdrawMoney(void);
    void ShowAllAccInfo(void) const;
    ~AccountHandler();
};

void AccountHandler::ShowMenu() const { // 메뉴 출력 함수
    cout << "-----Menu-----" << endl;
    cout << "1. 계좌개설" << endl;
    cout << "2. 입 금" << endl;
    cout << "3. 출 금" << endl;
    cout << "4. 계좌정보 전체 출력" << endl;
    cout << "5. 프로그램 종료" << endl;
}

void AccountHandler::MakeAccount() { // 계좌 개설 함수
    int id;
    char name[NAME_LEN];
    int balance;

    cout << "[계좌개설]" << endl;
    cout << "계좌ID: "; cin >> id;
    cout << "이 름: "; cin >> name;
    cout << "입금액: "; cin >> balance;
    cout << endl;

    accArr[accNum++] = new Account(id, balance, name); // 계좌 객체 동적 할당
}

void AccountHandler::DepositMoney() { // 예금 함수
    int money; // 예금할 돈
    int id;
    cout << "[입   금]" << endl;
    cout << "계좌ID: "; cin >> id;
    cout << "입금액: "; cin >> money;

    for (int i = 0; i < accNum; i++) {
        if (accArr[i]->GetAccID() == id) {
            accArr[i]->Deposit(money);
            cout << "입금완료" << endl << endl;
            return;
        }
    }
    cout << "유효하지 않은 ID 입니다." << endl << endl;
}

void AccountHandler::WithdrawMoney() { // 출금 함수
    int money; // 출금할 돈
    int id;
    cout << "[출   금]" << endl;
    cout << "계좌ID: "; cin >> id;
    cout << "출금액: "; cin >> money;

    for (int i = 0; i < accNum; i++) {
        if (accArr[i]->GetAccID() == id) {
            if (accArr[i]->Withdraw(money) == 0) { // 잔액 부족이면 0 반환
                cout << "잔액부족" << endl << endl;
                return;
            }

            cout << "출금완료" << endl << endl;
            return;
        }
    }
    cout << "유효하지 않은 ID 입니다." << endl << endl;
}

AccountHandler::AccountHandler() : accNum(0) {} // 생성자, 계좌 개수는 0으로 초기화

void AccountHandler::ShowAllAccInfo() const { // 모든 계좌 정보 출력 함수
    for (int i = 0; i < accNum; i++) {
        accArr[i]->ShowAccInfo();
        cout << endl;
    }
}

AccountHandler::~AccountHandler() { // 소멸자
    for (int i = 0; i < accNum; i++) {
        delete accArr[i]; // 동적할당한 계좌 객체 메모리 해제
    }
}

/*
 * 컨트롤 클래스 AccountHandler 중심으로 변경된 main 함수
 */

int main(void) {
    AccountHandler manager; // 객체 생성
    int choice;

    while (1) {
        manager.ShowMenu();
        cout << "선택: ";
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