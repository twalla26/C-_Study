#include <iostream>
#include <cstring>
using namespace std;

class Employee { // ���� Ŭ����
private:
    char name[100]; // �� ��
public:
    Employee(char * name) { // ������
        strcpy(this->name, name);
    }
    void ShowYourName() const { // �̸� ��� �Լ�
        cout << "name: " << name << endl;
    }
    virtual int GetPay() const = 0; // ���� �����Լ� -> Employee ��ü ������ ����
    virtual void ShowSalaryInfo() const = 0; // ���� �����Լ�
};

class PermanentWorker : public Employee { // ������ Ŭ����, ������ IS-A ����
private:
    int salary; // �� �޿�
public:
    PermanentWorker(char * name, int money) // ������
        : Employee(name), salary(money) {}
    virtual int GetPay() const { // �� �޿� ��ȯ �Լ�
        return salary;
    }
    virtual void ShowSalaryInfo() const { // �޿� ��� �Լ�
        ShowYourName();
        cout << "salary: " << GetPay() << endl << endl;
    }
};

class TemporaryWorker : public Employee { // �ӽ��� Ŭ����, �ӽ��� IS-A ����
private:
    int workTime; // �� �޿� ���� �ð��� �հ�
    int payPerHour; // �ð��� �޿�
public:
    TemporaryWorker(char * name, int pay) // ������
        : Employee(name), workTime(0), payPerHour(pay) {}
    void AddWorkTime(int time) { // ���� �ð��� �߰�
        workTime += time;
    }
    virtual int GetPay() const { // �� ���� �޿�
        return workTime*payPerHour;
    }
    virtual void ShowSalaryInfo() const { // �� �޿� ��� �Լ�
        ShowYourName();
        cout << "salary: " << GetPay() << endl << endl;
    }
};

class SalesWorker: public PermanentWorker { // ������ Ŭ����, �ӽ��� IS-A ������, ����
private:
    int salesResult; // �� �ǸŽ���
    double bonusRatio; // �󿩱� ����
public:
    SalesWorker(char * name, int money, double ratio) // ������
        : PermanentWorker(name, money), salesResult(0), bonusRatio(ratio) {}
    virtual void AddSalesResult(int value) { // �ǸŽ��� �߰�
        salesResult += value;
    }
    // �Լ� �������̵� -> SalesWorker Ŭ���� ������ GeyPay()�� ȣ���ϸ�, �����ǵ� GetPay()�Լ��� ȣ���.
    // PermanentWorker Ŭ�������� ���ǵ� GeyPay() �Լ��� ȣ���Ϸ���, PermanentWorker::GetPay() ����� �̿��ؾ� ��.
    virtual int GetPay() const { // �� �޿�
        return PermanentWorker::GetPay() + (int)(salesResult*bonusRatio); // PermanentWorker�� GetPay �Լ� ȣ��
    }
    virtual void ShowSalaryInfo() const {
        ShowYourName();
        cout << "salary: " << GetPay() << endl << endl; // SalesWorker�� GetPay �Լ��� ȣ���.
    }
};

namespace RISK_LEVEL { // �̸����� �ȿ� enum ����
    enum {RISK_A=30, RISK_B=20, RISK_C=10};
}

class ForeignSalesWorker : public SalesWorker { // �ؿ� ������ Ŭ����, �ؿ� ������ IS-A ������, ������
private:
    const int riskLevel; // ���� ����
public:
    ForeignSalesWorker(char * name, int money, double ratio, int risk) // ������
        : SalesWorker(name, money, ratio), riskLevel(risk) {} // riskLevel���� 30, 20, 10 ���� ��
    int GetRiskPay() const { // ������� ���
        return (int)(SalesWorker::GetPay() * (riskLevel/100.0)); // ���� ���� �߰� �� ����� ������ �޿� ��� �Լ��� ȣ���Ͽ� �ذ�
    }
    virtual int GetPay() const { // �� �޿�
        return SalesWorker::GetPay() + GetRiskPay(); // ������ �޿� + �������
    }
    virtual void ShowSalaryInfo() const {
        ShowYourName();
        cout << "salary: " << SalesWorker::GetPay() << endl;
        cout << "risk pay: " << GetRiskPay() << endl;
        cout << "sum: " << GetPay() << endl << endl;
    }
};

class EmployeeHandler { // ��Ʈ�� Ŭ����
private:
    Employee * empList[50]; // ��ü �ּ� ���� �迭
    int empNum; // ��ü �� ����
public:
    EmployeeHandler() : empNum(0) {} // ������
    void AddEmployee(Employee * emp) { // ���� �߰� �Լ�, ������ ����� PermanentWorker���� Employee ��ü�� �ٲ�
        // ������� ���°� �پ������� �ݿ�, ��� Employee�� ��ӹ����Ƿ� ��ü ���� ����
        empList[empNum++] = emp; // Employee Ŭ������ ����ϴ� Ŭ������ ��ü�� �� �迭�� ������ ������!!
    }
    void ShowAllSalaryInfo() const {
        /*
         * // ���� ��
         * for (int i = 0; i < empNum; i++) {
         *      empList[i]->ShowSalaryInfo();
         * } // �迭�� �����ϴ� ������ ������ Employee�� ������ �����̹Ƿ�,
         *   // Employee Ŭ������ ����� �ƴ� GetPay �Լ��� ShowSalaryInfo �Լ��� ȣ��κп��� ���� �߻�
         *   // �ذ�: Employee Ŭ������ GetPay �Լ��� ShowSalaryInfo �Լ��� �߰��� �����ϰ�, �̸� �����Լ��� ����
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
         * } // ���� �ذ����� ��������
         */
        for (int i = 0; i < empNum; i++) {
            sum += empList[i]->GetPay();
        }
        cout << "salary sum: " << sum << endl;
    }
    ~EmployeeHandler() { // �Ҹ���
        for (int i = 0; i < empNum; i++) {
            delete empList[i]; // ���� �Ҵ�� ��ü�� �޸� ����
        }
    }
};

int main(void) {
    // ���������� �������� ����� ��Ʈ�� Ŭ������ ��ü ����
    EmployeeHandler handler;

    // �ؿ� ������ ���
    ForeignSalesWorker * fseller1 = new ForeignSalesWorker("Hong", 1000, 0.1, RISK_LEVEL::RISK_A);
    fseller1->AddSalesResult(7000);
    handler.AddEmployee(fseller1);

    ForeignSalesWorker * fseller2 = new ForeignSalesWorker("Yoon", 1000, 0.1, RISK_LEVEL::RISK_B);
    fseller2->AddSalesResult(7000);
    handler.AddEmployee(fseller2);

    ForeignSalesWorker * fseller3 = new ForeignSalesWorker("Lee", 1000, 0.1, RISK_LEVEL::RISK_C);
    fseller3->AddSalesResult(7000);
    handler.AddEmployee(fseller3);

    // ������ ���
    handler.AddEmployee(new PermanentWorker("KIM", 1000)); // ���� �Ҵ�
    handler.AddEmployee(new PermanentWorker("LEE", 1500));

    // �ӽ��� ���
    TemporaryWorker * alba = new TemporaryWorker("Jung", 700);
    alba->AddWorkTime(5); // 5�ð� ���� ��� ���
    handler.AddEmployee(alba);

    // ������ ���
    SalesWorker * seller = new SalesWorker("Hong", 1000, 0.1);
    seller->AddSalesResult(7000); // �������� 7000
    handler.AddEmployee(seller);

    // �̹� �޿� �����ؾ� �� �޿��� ����
    handler.ShowAllSalaryInfo();

    // �̹� �޿� �����ؾ� �� �޿��� ����
    handler.ShowTotalSalary();
    return 0;
}