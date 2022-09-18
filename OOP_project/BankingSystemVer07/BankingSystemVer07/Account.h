/*
 파일이름: Account.h
 작성자: Twalla
 업데이트 정보: [2010, 09, 19] 파일버전 0.7
 */

#ifndef __ACCOUNT_H__ // if not defined -> Account.h 파일을 define 문장으로 정의하지 않았다면
#define __ACCOUNT_H__ // endif가 나오기 전까지의 문장을 include 영역에 포함시켜라!

class Account {
private:
    int accID; // 계좌 번호
    int balance; // 잔액
    char * cusName; // 사용자
public:
    Account(int ID, int money, char * name); // 생성자
    Account(const Account & ref); // 복사 생성자
    
    int GetAccID() const;
    virtual void Deposit(int money);
    int Withdraw(int money);
    void ShowAccInfo() const;
    ~Account(); // 소멸자
};
#endif
