#include <iostream>
using namespace std;

class FruitSeller { // 과일 판매자 클래스 선언
private:
    const int APPLE_PRICE; // 판매하는 사과 가격(대문자 -> 변하지 않는 값임을 암시)
    int numOfApples; // 사과 개수
    int myMoney; // 판매자의 돈

public:
    FruitSeller(int price, int num, int money): APPLE_PRICE(price), numOfApples(num), myMoney(money) { // 생성자 선언

    }

    int SaleApples(int money) { // 사과 판매 함수, 인수로 구매자가 낸 돈을 받음
        int num = money/APPLE_PRICE; // num: 판 사과 개수(구매자가 낸 돈/사과 가격)
        numOfApples -= num; // 판매자 기존 사과 개수 - 판 사과 개수
        myMoney += money; // 돈 + 받은 돈
        return num; // 판매한 사과 개수 반환
    }

    void ShowSalesResult() { // 판매 현황 함수
        cout << "남은 사과: " << numOfApples << endl;
        cout << "판매 수익: " << myMoney << endl;
    }
};

class FruitBuyer { // 사과 구매자 클래스 선언
private:
    int myMoney; // 구매자 돈
    int numOfApples; // 구매자가 산 총 사과 개수

public:
    FruitBuyer(int money): myMoney(money), numOfApples(0) {

    }

    void BuyApples(FruitSeller &seller, int money) { // 사과 구매 함수 (판매자 참조자 선언, 구매하기 위해 낸 돈)
        numOfApples += seller.SaleApples(money); // 구매자 가진 사과 개수에, 판매자에게 산 사과 개수를 더함. public -> 함수 호출 어디서나 가능
        myMoney -= money; // 돈은 낸 만큼 감소
    }

    void ShowBuyResult() { // 구매 결과 함수
        cout << "현재 잔액: " << myMoney << endl;
        cout << "사과 개수: " << numOfApples << endl << endl;
    }
};

int main(void) {
    FruitSeller seller(1000, 20, 0); // seller 객체 생성
    FruitBuyer buyer(5000); // buyer 객체 생성
    buyer.BuyApples(seller, 2000); // 과일의 구매!!, seller 객체에게 2000원 지불

    cout << "과일 판매자의 현황" << endl;
    seller.ShowSalesResult();
    cout << "과일 구매자의 현황" << endl;
    buyer.ShowBuyResult();
    return 0;
}