/*
 파일이름: Account.cpp
 작성자: Twalla
 업데이트 정보: [2022, 09, 19] 파일버전 0.7
 */

#include "BankingCommonDecl.h"
#include "Account.h"

Account::Account(int ID, int money, char * name) // 생성자 -> 계좌 객체 생성
: accID(ID), balance(money) { // 멤버 이니셜라이저
    cusName = new char[strlen(name)+1];
    strcpy(cusName, name);
};

Account::Account(const Account & ref) // 복사 생성자
: accID(ref.accID), balance(ref.balance) {
    cusName = new char[strlen(ref.cusName)+1]; // 동적 할당
    strcpy(cusName, ref.cusName);
}

int Account::GetAccID() const { return accID; } // 계좌번호 반환 함수

void Account::Deposit(int money) { // 입금 함수
    balance += money;
}

int Account::Withdraw(int money) { // 출금 함수
    if (balance < money) {
        return 0; // 출금할 돈이 모자라면 0 반환
    }
    
    balance -= money;
    return money;
}

void Account::ShowAccInfo() const {
    cout << "계좌ID: " << accID << endl;
    cout << "이 름: " << cusName << endl;
    cout << "잔 액: " << balance << endl;
}

Account::~Account() { // 소멸자
    delete []cusName; // 동적 할당된 cusName 객체 메모리 해제
}
