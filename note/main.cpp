#include <iostream>

int main(void) {
    int sale_price = 0;
    while (sale_price != -1) {
        std::cout << "�Ǹ� �ݾ��� ���� ������ �Է�(-1 to end): ";
        std::cin >> sale_price;
        if (sale_price == -1) {
            std::cout << "���α׷��� �����մϴ�.";
            return 0;
        }
        else {
            std::cout << "�̹� �� �޿�: " << 50 + (sale_price * 0.12) << "����" << std::endl;
        }
    }
}
