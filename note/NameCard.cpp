#include <iostream>
#include <cstring>
using namespace std;

namespace COMP_POS { // 직급 관리 이름공간
    enum {CLERK, SENIOR, ASSIST, MANAGER}; // 직급명, 0,1,2,3

    void ShowPositionInfo(int pos) { // 직급을 인자로 받아 출력하는 함수
        switch (pos) {
            case CLERK:
                cout << "사원" << endl;
                break;
            case SENIOR:
                cout << "주임" << endl;
                break;
            case ASSIST:
                cout << "대리" << endl;
                break;
            case MANAGER:
                cout << "과장" << endl;
                break;
        }
    }
}

class NameCard { // 명함 클래스 정의
private:
    char *name; // 이름
    char *company; // 회사
    char *phoneNumber; // 전화번호
    int position; // 직급
public:
    NameCard(char *_name, char *_company, char *_phoneNumber, int _position) { // 생성자
        name = new char[strlen(_name) + 1]; // name에 메모리 공간 할당
        company = new char[strlen(_company) + 1];
        phoneNumber = new char[strlen(_phoneNumber) + 1];
        strcpy(name, _name); // name에 값 저장
        strcpy(company, _company);
        strcpy(phoneNumber, _phoneNumber);
        position = _position; // COMP_POS::CLERK -> 0으로 들어옴
    }

    void ShowNameCardInfo() {
        cout << "이름: " << name << endl;
        cout << "회사: " << company << endl;
        cout << "전화번호: " << phoneNumber << endl;
        cout << "직급: ";
        COMP_POS::ShowPositionInfo(position); // 이름공간 안의 함수 호출 -> 직급 이름 출력됨!!
        cout << endl;
    }

    ~NameCard() { // 소멸자 -> 동적할당 메모리 해제
        delete []name;
        delete []company;
        delete []phoneNumber;
    }
};

int main(void) {
    NameCard manClerk("Lee", "ABCEng", "010-1111-2222", COMP_POS::CLERK);
    NameCard manSENIOR("Hong", "OrangeEng", "010-3333-4444", COMP_POS::SENIOR);
    NameCard manAssist("Kim", "SoGoodComp", "010-5555-6666", COMP_POS::ASSIST);
    manClerk.ShowNameCardInfo();
    manSENIOR.ShowNameCardInfo();
    manAssist.ShowNameCardInfo();
    return 0;
}