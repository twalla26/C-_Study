#include <iostream>
#include <cstring>
using namespace std;

class Employee { // 직원 클래스
private:
    char name[100]; // 이 름
public:
    Employee(char * name) { // 생성자
        strcpy(this->name, name);
    }
    void ShowYourName() const { // 이름 출력 함수
        cout << "name: " << name << endl;
    }
    virtual int GetPay() const = 0; // 순수 가상함수 -> Employee 객체 생성을 막음
    virtual void ShowSalaryInfo() const = 0; // 순수 가상함수
};

class PermanentWorker : public Employee { // 정규직 클래스, 정규직 IS-A 직원
private:
    int salary; // 월 급여
public:
    PermanentWorker(char * name, int money) // 생성자
        : Employee(name), salary(money) {}
    virtual int GetPay() const { // 월 급여 반환 함수
        return salary;
    }
    virtual void ShowSalaryInfo() const { // 급여 출력 함수
        ShowYourName();
        cout << "salary: " << GetPay() << endl << endl;
    }
};

class TemporaryWorker : public Employee { // 임시직 클래스, 임시직 IS-A 직원
private:
    int workTime; // 이 달에 일한 시간의 합계
    int payPerHour; // 시간당 급여
public:
    TemporaryWorker(char * name, int pay) // 생성자
        : Employee(name), workTime(0), payPerHour(pay) {}
    void AddWorkTime(int time) { // 일한 시간의 추가
        workTime += time;
    }
    virtual int GetPay() const { // 이 달의 급여
        return workTime*payPerHour;
    }
    virtual void ShowSalaryInfo() const { // 월 급여 출력 함수
        ShowYourName();
        cout << "salary: " << GetPay() << endl << endl;
    }
};

class SalesWorker: public PermanentWorker { // 영업직 클래스, 임시직 IS-A 정규직, 직원
private:
    int salesResult; // 월 판매실적
    double bonusRatio; // 상여금 비율
public:
    SalesWorker(char * name, int money, double ratio) // 생성자
        : PermanentWorker(name, money), salesResult(0), bonusRatio(ratio) {}
    virtual void AddSalesResult(int value) { // 판매실적 추가
        salesResult += value;
    }
    // 함수 오버라이딩 -> SalesWorker 클래스 내에서 GeyPay()를 호출하면, 재정의된 GetPay()함수가 호출됨.
    // PermanentWorker 클래스에서 정의된 GeyPay() 함수를 호출하려면, PermanentWorker::GetPay() 방식을 이용해야 함.
    virtual int GetPay() const { // 월 급여
        return PermanentWorker::GetPay() + (int)(salesResult*bonusRatio); // PermanentWorker의 GetPay 함수 호출
    }
    virtual void ShowSalaryInfo() const {
        ShowYourName();
        cout << "salary: " << GetPay() << endl << endl; // SalesWorker의 GetPay 함수가 호출됨.
    }
};

namespace RISK_LEVEL { // 이름공간 안에 enum 정의
    enum {RISK_A=30, RISK_B=20, RISK_C=10};
}

class ForeignSalesWorker : public SalesWorker { // 해외 영업직 클래스, 해외 영업직 IS-A 영업직, 정규직
private:
    const int riskLevel; // 위험 수준
public:
    ForeignSalesWorker(char * name, int money, double ratio, int risk) // 생성자
        : SalesWorker(name, money, ratio), riskLevel(risk) {} // riskLevel에는 30, 20, 10 등이 들어감
    int GetRiskPay() const { // 위험수당 계산
        return (int)(SalesWorker::GetPay() * (riskLevel/100.0)); // 위험 수당 추가 전 계산은 영업직 급여 계산 함수를 호출하여 해결
    }
    virtual int GetPay() const { // 총 급여
        return SalesWorker::GetPay() + GetRiskPay(); // 영업직 급여 + 위험수당
    }
    virtual void ShowSalaryInfo() const {
        ShowYourName();
        cout << "salary: " << SalesWorker::GetPay() << endl;
        cout << "risk pay: " << GetRiskPay() << endl;
        cout << "sum: " << GetPay() << endl << endl;
    }
};

class EmployeeHandler { // 컨트롤 클래스
private:
    Employee * empList[50]; // 객체 주소 저장 배열
    int empNum; // 객체 총 개수
public:
    EmployeeHandler() : empNum(0) {} // 생성자
    void AddEmployee(Employee * emp) { // 직원 추가 함수, 저장의 대상이 PermanentWorker에서 Employee 객체로 바뀜
        // 고용인의 형태가 다양해짐을 반영, 모두 Employee를 상속받으므로 객체 저장 가능
        empList[empNum++] = emp; // Employee 클래스를 상속하는 클래스의 객체도 이 배열에 저장이 가능함!!
    }
    void ShowAllSalaryInfo() const {
        /*
         * // 수정 전
         * for (int i = 0; i < empNum; i++) {
         *      empList[i]->ShowSalaryInfo();
         * } // 배열을 구성하는 포인터 변수가 Employee형 포인터 변수이므로,
         *   // Employee 클래스의 멤버가 아닌 GetPay 함수와 ShowSalaryInfo 함수의 호출부분에서 에러 발생
         *   // 해결: Employee 클래스에 GetPay 함수와 ShowSalaryInfo 함수를 추가로 정의하고, 이를 가상함수로 선언
         */
        for (int i = 0; i < empNum; i++) {
            empList[i]->ShowSalaryInfo();
        }
    }
    void ShowTotalSalary() const {
        int sum = 0;
        /*
         * for (int i = 0; i < empNum; i++) {
         *      sum += empList[i]->GetPay();
         * } // 위의 해결방법과 마찬가지
         */
        for (int i = 0; i < empNum; i++) {
            sum += empList[i]->GetPay();
        }
        cout << "salary sum: " << sum << endl;
    }
    ~EmployeeHandler() { // 소멸자
        for (int i = 0; i < empNum; i++) {
            delete empList[i]; // 동적 할당된 객체들 메모리 해제
        }
    }
};

int main(void) {
    // 직원관리를 목적으로 설계된 컨트롤 클래스의 객체 생성
    EmployeeHandler handler;

    // 해외 영업직 등록
    ForeignSalesWorker * fseller1 = new ForeignSalesWorker("Hong", 1000, 0.1, RISK_LEVEL::RISK_A);
    fseller1->AddSalesResult(7000);
    handler.AddEmployee(fseller1);

    ForeignSalesWorker * fseller2 = new ForeignSalesWorker("Yoon", 1000, 0.1, RISK_LEVEL::RISK_B);
    fseller2->AddSalesResult(7000);
    handler.AddEmployee(fseller2);

    ForeignSalesWorker * fseller3 = new ForeignSalesWorker("Lee", 1000, 0.1, RISK_LEVEL::RISK_C);
    fseller3->AddSalesResult(7000);
    handler.AddEmployee(fseller3);

    // 정규직 등록
    handler.AddEmployee(new PermanentWorker("KIM", 1000)); // 동적 할당
    handler.AddEmployee(new PermanentWorker("LEE", 1500));

    // 임시직 등록
    TemporaryWorker * alba = new TemporaryWorker("Jung", 700);
    alba->AddWorkTime(5); // 5시간 일한 결과 등록
    handler.AddEmployee(alba);

    // 영업직 등록
    SalesWorker * seller = new SalesWorker("Hong", 1000, 0.1);
    seller->AddSalesResult(7000); // 영업실적 7000
    handler.AddEmployee(seller);

    // 이번 달에 지불해야 할 급여의 정보
    handler.ShowAllSalaryInfo();

    // 이번 달에 지불해야 할 급여의 총합
    handler.ShowTotalSalary();
    return 0;
}