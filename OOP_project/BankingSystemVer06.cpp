/*
 * Banking System Ver 0.6
 * 작성자: 송수민
 * 내 용: 이자관련 계좌 클래스의 추가
 */

#include <iostream>
#include <cstring>

using namespace std; // 이름 공간
const int NAME_LEN=20; // 전역변수 설정, const 선언!;

// 프로그램 사용자의 선택 메뉴
enum {MAKE=1, DEPOSIT, WITHDRAW, INQUIRE, EXIT}; // 열거자: 사용자 정의 자료형, 코드문서화 및 가독성 목적 or 집합 정리

// 신용등급
enum {LEVEL_A=7, LEVEL_B=4, LEVEL_C=2}; // 숫자는 이율

// 계좌의 종류
enum {NORMAL=1, CREDIT=2}; // NORMAL: 보통예금계좌, CREDIT: 신용신뢰계좌

/*
 * 클래스 이름: Account
 * 클래스 유형: Entity 클래스
 */

class Account {
private:
    int accID; // 계좌번호
    int balance; // 잔 액
    char * cusName; // 사용자
public:
    Account(int ID, int money, char * name); // 생성자
    Account(const Account & ref); // 복사생성자, Account 객체를 받아 참조자, const 선언(함수 인자 수정 불가)!!

    int GetAccID() const; // 계좌번호 반환 함수, const 선언 -> 멤버변수 변경 X
    virtual void Deposit(int money); // 입금 함수, virtual 선언 -> 포인터 변수가 실제로 가리키는 객체를 대상으로 함수 호출
    int Withdraw(int money); // 출금 함수
    void ShowAccInfo() const; // 계좌 정보 출력 함수
    ~Account();
};

Account::Account(int ID, int money, char *name) // Account 클래스의 생성자 정의
    : accID(ID), balance(money) { // 멤버 이니셜라이저 -> 선언과 동시에 초기화
    cusName = new char[strlen(name)+1];  // 동적 할당 -> 배열 칸 할당
    strcpy(cusName, name);
}

Account::Account(const Account &ref) // Account 클래스의 복사생성자 정의, 인자로 받은 Account 객체 ref를 참초자, const 선언!
    : accID(ref.accID), balance(ref.balance) {
    cusName = new char[strlen(ref.cusName)+1];
    strcpy(cusName, ref.cusName);
}

int Account::GetAccID() const { return accID; } // 계좌 반환 함수 정의

void Account::Deposit(int money) { // 입금 함수, 인자로 입금할 돈을 받음
    balance += money; // 잔액 + 입금액
}

int Account::Withdraw(int money) { // 출금 함수, 인자로 출금할 돈을 받음
    if (balance < money) { // 만약 잔액이 출금액보다 적다면
        return 0; // 출금 불가 -> 0 반환
    }
    // 위의 조건에 걸리지 않았다면(출금이 가능하다면)
    balance -= money; // 잔액 - 출금액
    return money; // 출금액 반환
}

void Account::ShowAccInfo() const { // 계좌 정보 출력 함수
    cout << "계좌ID: " << accID << endl;
    cout << "이 름: " << cusName << endl;
    cout << "잔 액: " << balance << endl;
}

Account::~Account() { // 소멸자 정의
    delete []cusName; // 동적할당된 메모리 해제
}

/*
 * 클래스 이름: NormalAccount
 * 클래스 유형: Entity 클래스
 */

class NormalAccount : public Account { // Account 클래스를 public으로 선언받음
private:
    int interRate; // 이자율 % 단위
public:
    NormalAccount(int ID, int money, char * name, int rate) // 생성자
        : Account(ID, money, name), interRate(rate) {} // 멤버 이니셜라이저 -> 부모클래스 생성자 호출

    virtual void Deposit(int money) { // 입금 함수, virtual 선언 -> 포인터 변수가 실제로 가리키는 객체를 대상으로 함수 호출
        Account::Deposit(money); // 원금 추가, Account 클래스의 Deposit 함수 호출!!
        Account::Deposit(money*(interRate/100.0)); // 이자 추가
    }
};

/*
 * 클래스 이름: HighCreditAccount
 * 클래스 유형: Entity 클래스
 */

class HighCreditAccount : public NormalAccount { // NormalAccount 클래스를 public으로 상속받음.
private:
    int specialRate; // 신용 등급
public:
    HighCreditAccount(int ID, int money, char * name, int rate, int special) // 생성자
        : NormalAccount(ID, money, name, rate), specialRate(special) {}

    virtual void Deposit(int money) { // 입금 함수, virtual 선언 -> 포인터 변수가 실제로 가리키는 객체를 대상으로 함수 호출
        NormalAccount::Deposit(money); // 원금과 이자 추가
        Account::Deposit(money*(specialRate/100.0)); // 특별 이자 추가
    }
};

/*
 * 클래스 이름: AccountHandler
 * 클래스 유형: 컨트롤(control) 클래스
 */

class AccountHandler {
private:
    Account * accArr[100]; // 계좌 객체들의 주소가 저장될 배열
    int accNum; // 저장된 계좌 객체들의 주소
public:
    AccountHandler(); // 생성자
    void ShowMenu(void) const; // 메뉴 출력, 함수에 const 선언 -> 멤버변수 수정 불가, const 함수만 호출 가능
    void MakeAccount(void); // 계좌 생성 함수
    void DepositMoney(void); // 입금 함수
    void WithdrawMoney(void); // 출금 함수
    void ShowAllAccInfo(void) const; // 모든 계좌 정보 출력 함수
    ~AccountHandler(); // 소멸자
protected: // protected 선언!!
    void MakeNormalAccount(void); // 보통예금계좌 생성
    void MakeCreditAccount(void); // 신용신뢰계좌 생성
};

void AccountHandler::ShowMenu() const { // 메뉴 출력, 함수에 const 선언 -> 멤버변수 수정 불가, const 함수만 호출 가능
    cout << "-----Menu-----" << endl;
    cout << "1. 계좌개설" << endl;
    cout << "2. 입 금" << endl;
    cout << "3. 출 금" << endl;
    cout << "4. 계좌정보 전체 출력" << endl;
    cout << "5. 프로그램 종료" << endl;
}

void AccountHandler::MakeAccount() { // 계좌 생성 함수
    int sel; // 사용자가 입력한 번호
    cout << "[계좌종류선택]" << endl;
    cout << "1. 보통예금계좌 ";
    cout << "2. 신용신뢰계좌" << endl;
    cout << "선택: ";
    cin >> sel;

    if (sel==NORMAL) { // NORMAL=1, 사용자가 1을 선택했다면
        MakeNormalAccount(); // 보통예금계좌 생성 함수 호출
    }
    else {
        MakeCreditAccount(); // 신용신뢰계좌 생성 함수 호출
    }
}

void AccountHandler::MakeNormalAccount() { // 보통예금계좌 생성 함수 정의
    int id; // 계좌 번호
    char name[NAME_LEN]; // 사용자, 이름칸은 20으로 제한
    int balance; // 잔 액
    int interRate; // 이자율

    cout << "[보통예금계좌 개설]" << endl;
    cout << "계좌ID: "; cin >> id;
    cout << "이 름: "; cin >> name;
    cout << "입금액: "; cin >> balance;
    cout << "이자율: "; cin >> interRate;
    cout << endl;

    accArr[accNum++] = new NormalAccount(id, balance, name, interRate); // 배열에 저장
}

void AccountHandler::MakeCreditAccount() { // 신용신뢰계좌 생성 함수 정의
    int id;
    char name[NAME_LEN];
    int balance;
    int interRate; // 이자율
    int creditLevel; // 신용등급

    cout << "[신용신뢰계좌 개설]" << endl;
    cout << "계좌ID: "; cin >> id;
    cout << "이 름: "; cin >> name;
    cout << "입금액: "; cin >> balance;
    cout << "이자율: "; cin >> interRate;
    cout << "신용등급(1toA, 2toB, 3toC): "; cin >> creditLevel;
    cout << endl;

    switch (creditLevel) { // 입력받은 creditLevel로 비교
        case 1: // 신용등급이 1이라면
            accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_A); // 배열에 저장
            break;
        case 2:
            accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_B);
            break;
        case 3:
            accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_C);
    }
}

void AccountHandler::DepositMoney() { // 입금 함수
    int money;
    int id;
    cout << "[입   금]" << endl;
    cout << "계좌ID: "; cin >> id;
    cout << "입금액: "; cin >> money;

    for (int i = 0; i < accNum; i++) { // 입력받은 번호에 해당하는 계좌 찾기
        if (accArr[i]->GetAccID()==id) { // GetAccID 함수의 반환값은 해당 계좌의 번호
            accArr[i]->Deposit(money); // 찾으면 입금 진행, Deposit은 가상함수선언 -> 해당 객체 기준으로 함수 호출
            cout << "입금완료" << endl << endl;
            return;
        }
    }
    // 해당 계좌를 찾지 못했을 때
    cout << "유효하지 않은 ID 입니다." << endl << endl;
}

void AccountHandler::WithdrawMoney() {
    int money;
    int id;
    cout << "[출   금]" << endl;
    cout << "계좌ID: "; cin >> id;
    cout << "출금액: "; cin >> money;

    for (int i = 0; i < accNum; i++) { // 해당 계좌 찾기
        if (accArr[i]->GetAccID()==id) { // 계좌를 찾으면
            if (accArr[i]->Withdraw(money)==0) { // 출금 불가능하면
                cout << "잔액부족" << endl << endl; // 불가능 안내
                return;
            }
            // 출금 가능한 경우
            cout << "출금완료" << endl << endl;
            return;
        }
    }
    // 계좌를 찾지 못한 경우
    cout << "유효하지 않은 ID 입니다." << endl << endl;
}

AccountHandler::AccountHandler() : accNum(0) {} // 생성자

void AccountHandler::ShowAllAccInfo() const { // 모든 계좌 정보 출력 함수
    for (int i = 0; i < accNum; i++) { // 모든 계좌들에 대해서
        accArr[i]->ShowAccInfo(); // 정보 출력 함수 호출
        cout << endl;
    }
}

AccountHandler::~AccountHandler() { // 소멸자
    for (int i = 0; i < accNum; i++) { // 모든 저장된 계좌 객체에 대해서
        delete accArr[i]; // 메모리 해제
    }
}

/*
 * 컨트롤 클래스 AccountHandler 중심의 main 함수
 */

int main(void) {
    AccountHandler manager;
    int choice;

    while(1) {
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