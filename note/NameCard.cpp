#include <iostream>
#include <cstring>
using namespace std;

namespace COMP_POS { // ���� ���� �̸�����
    enum {CLERK, SENIOR, ASSIST, MANAGER}; // ���޸�, 0,1,2,3

    void ShowPositionInfo(int pos) { // ������ ���ڷ� �޾� ����ϴ� �Լ�
        switch (pos) {
            case CLERK:
                cout << "���" << endl;
                break;
            case SENIOR:
                cout << "����" << endl;
                break;
            case ASSIST:
                cout << "�븮" << endl;
                break;
            case MANAGER:
                cout << "����" << endl;
                break;
        }
    }
}

class NameCard { // ���� Ŭ���� ����
private:
    char *name; // �̸�
    char *company; // ȸ��
    char *phoneNumber; // ��ȭ��ȣ
    int position; // ����
public:
    NameCard(char *_name, char *_company, char *_phoneNumber, int _position) { // ������
        name = new char[strlen(_name) + 1]; // name�� �޸� ���� �Ҵ�
        company = new char[strlen(_company) + 1];
        phoneNumber = new char[strlen(_phoneNumber) + 1];
        strcpy(name, _name); // name�� �� ����
        strcpy(company, _company);
        strcpy(phoneNumber, _phoneNumber);
        position = _position; // COMP_POS::CLERK -> 0���� ����
    }

    void ShowNameCardInfo() {
        cout << "�̸�: " << name << endl;
        cout << "ȸ��: " << company << endl;
        cout << "��ȭ��ȣ: " << phoneNumber << endl;
        cout << "����: ";
        COMP_POS::ShowPositionInfo(position); // �̸����� ���� �Լ� ȣ�� -> ���� �̸� ��µ�!!
        cout << endl;
    }

    ~NameCard() { // �Ҹ��� -> �����Ҵ� �޸� ����
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