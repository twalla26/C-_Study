# 04-3 생성자(Constructor)와 소멸자(Destructor)

---

## 생성자의 이해

<aside>
🔎 객체 생성시 딱 한번 호출된다

</aside>

```cpp
#include <iostream>
using namespace std;

class SimpleClass {
private:
    int num1;
    int num2;

public:
    SimpleClass() { // 생성자도 함수의 일종이므로, 매개변수에 '디폴트 값' 설정 가능
        num1 = 0;
        num2 = 0;
    }
    SimpleClass(int n) { // 생성자도 함수의 일종이므로, 오버로딩이 가능
        num1 = n;
        num2 = 0;
    }
    SimpleClass(int n1, int n2) {
        num1 = n1;
        num2 = n2;
    }

    void ShowData() const {
        cout << num1 << ' ' << num2 << endl;
    }
};

int main(void) {
    SimpleClass sc1; // SimpleClass() 생성자 호출
    sc1.ShowData(); // 기본값 0,0 전달

    SimpleClass sc2(100); // SimpleClass(int n) 생성자 호출
    sc2.ShowData(); // 100, 0 전달

    SimpleClass sc3(100, 200); // SimpleClass(int n1, int n2) 생성자 호출
    sc3.ShowData(); // 100, 200 전달
    return 0;
}
```

0 0
100 0
100 200

그런데 SimpleClass() 생성자를 이용하여 객체를 생성하기 위해, 다음과 같이 문장을 구성하면 안된다.

```cpp
SimpleClass sc1();
```

대신 다음과 같이 구성해야 한다.

```cpp
SimpleClass sc1;
SimpleClass *ptr1 = new SimpleClass;
SimpleClass *ptr1 = new SimpleClass();
```

매개변수가 선언되어 있지 않으니, 다음과 같이 소괄호의 생략을 허용하는 것은 충분히 이해할 수 있다.

그러나 

```cpp
SimpleClass sc1();
```

다음 문장은 허용되지 않는다. 그 이유는 다음과 같다.

```cpp
#include <iostream>
using namespace std;

class SimpleClass {
private:
    int num1;
    int num2;

public:
    SimpleClass(int n1 = 0, int n2 = 0) {
        num1 = n1;
        num2 = n2;
    }

    void ShowData() const {
        cout << num1 << ' ' << num2 << endl;
    }
};

int main(void) {
    SimpleClass sc1(); // 함수의 원형 선언!! -> 밑에 정의되어있는 SimpleClass sc1() 함수의 호출을 위한 것
    SimpleClass mysc = sc1(); // sc1() 함수를 호출하여, 이때 반환되는 객체의 값으로 mysc 객체를 초기화
    mysc.ShowData(); // 20, 30 전달
    return 0;
}

SimpleClass sc1() {
    SimpleClass sc(20, 30);
    return sc;
}
```

보통 함수의 원형은 전역적으로 선언하지만, 위 예제에서 보듯 함수 내에 지역적으로 선언할 수 있다. 그러나 이 함수 선언을 void형 생성자의 호출문으로 인정해버리면, 컴파일러는 이러한 문장이 객체생성문인지, 함수의 원형선언인지 구분할 수 없다. 그래서 이러한 문장은 함수의 원형선언에만 사용하기로 약속했다.

### 이전 예제에 생성자 적용하기

### FruitSaleSim2.cpp

```cpp
#include <iostream>
using namespace std;

class FruitSeller { // 과일 판매자 클래스 선언
private:
    int APPLE_PRICE; // 판매하는 사과 가격(대문자 -> 변하지 않는 값임을 암시)
    int numOfApples; // 사과 개수
    int myMoney; // 판매자의 돈

public:
    FruitSeller(int price, int num, int money) { // 생성자 선언
        APPLE_PRICE = price;
        numOfApples = num;
        myMoney = money;
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
    FruitBuyer(int money) {
        myMoney = money;
        numOfApples = 0;
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
```

### 멤버 이니셜라이저(Member Initializer)를 이용한 멤버 초기화

Point.h

```cpp
#ifndef __POINT_H_
#define __POINT_H_

class Point {
private:
    int x;
    int y;

public:
    Point(const int &xpos, const int &ypos);
    int GetX() const;
    int GetY() const;
    bool SetX(int xpos);
    bool SetY(int ypos);
};

#endif //__POINT_H_
```

Point.cpp

```cpp
#include <iostream>
#include "Point.h"
using namespace std;

Point::Point(const int &xpos, const int &ypos) {
    x = xpos;
    y = ypos;
}

int Point::GetX() const {
    return x;
}

int Point::GetY() const {
    return y;
}

bool Point::SetX(int xpos) {
    if (0 > xpos || xpos > 100) {
        cout << "벗어난 범위의 값 전달" << endl;
        return false;
    }
    x = xpos;
    return true;
}

bool Point::SetY(int ypos) {
    if (0 > ypos || ypos > 100) {
        cout << "벗어난 범위의 값 전달" << endl;
        return false;
    }
    y = ypos;
    return true;
}
```

Rectangle.h

```cpp
#ifndef __RECTANGLE_H_
#define __RECTANGLE_H_

#include "Point.h"

class Rectangle {
private:
    Point upLeft;
    Point lowRight;

public:
    Rectangle(const int &x1, const int &y1, const int &x2, const int &y2);
    void ShowRecInfo() const;
};

#endif //__RECTANGLE_H_
```

Rectangle.cpp

```cpp
#include <iostream>
#include "Rectangle.h"
using namespace std;

Rectangle::Rectangle(const int &x1, const int &y1, const int &x2, const int &y2)
            : upLeft(x1, y1), lowRight(x2, y2) { // 멤버 이니셜라이저
						// 객체 upLeft의 생성과정에서 x1,y1을 인자로 받는 생성자를 호출해라! (public으로 선언되어 호출 가능)
    // empty
}

void Rectangle::ShowRecInfo() const {
    cout << "좌 상단: " << "[" << upLeft.GetX() << ", ";
    cout << upLeft.GetY() << ']' << endl;
    cout << "우 하단: " << "[" << lowRight.GetX() << ", ";
    cout << lowRight.GetY() << "]" << endl << endl;
}
```

RectangleConstructor.cpp

```cpp
#include <iostream>
#include "Point.h"
#include "Rectangle.h"
using namespace std;

int main(void) {
    Rectangle rec(1, 1, 5, 5);
    rec.ShowRecInfo();
    return 0;
}
```

## 멤버 이니셜라이저를 이용한 변수 및 const 상수(변수) 초기화

멤버 이니셜라이저는 객체가 아닌 멤버의 초기화에도 사용할 수 있다.

```cpp
class SoSimple {
private:
    int num1;
    int num2;

public:
    SoSimple(int n1, int n2) : num1(n1) { // num1: 이니셜라이저를 통해 초기화 -> 선언과 동시에 초기화
        num2 = n2; // num2: 생성자의 몸체 부분에서 대입연산을 통한 초기화 -> 선언과 초기화를 별도의 문장에서 진행
    }
};
```

<aside>
🔎 const 멤버 변수도 이니셜라이저를 이용하면 초기화가 가능하다!

</aside>

### FruitSaleSim3.cpp

```cpp
#include <iostream>
using namespace std;

class FruitSeller { // 과일 판매자 클래스 선언
private:
    const int APPLE_PRICE; // 판매하는 사과 가격(대문자 -> 변하지 않는 값임을 암시)
    int numOfApples; // 사과 개수
    int myMoney; // 판매자의 돈

public:
    FruitSeller(int price, int num, int money): APPLE_PRICE(price), numOfApples(num), myMoney(money) { // 생성자 선언, APPLE_PRICE를 const 선언 후, 생성자에서 멤버 이니셜라이저로 초기화 했음. (멤버이니셜라이저 -> 생성과 동시에 초기화, const -> 생성과 동시에 초기화)

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
```

생성자의 몸체부분에서 대입연산을 통한 초기화를 진행하는 것보다 이니셜라이저가 더 명확한 표현이다. 게다가 성능 상의 이점도 있다.

## 이니셜라이저의 이러한 특징은 멤버변수로 참조자를 선언할 수 있게 한다.

const 변수와 마찬가지로 참조자도 선언과 동시에 초기화가 이루어져야 한다. → 이니셜라이저를 이용하여 참조자도 멤버변수로 선언될 수 있다.

```cpp
#include <iostream>
using namespace std;

class AAA { // AAA 클래스 선언
public:
    AAA() { // 생성자
        cout << "empty object" << endl; // 객체 생성시 출력(실제로 생성자가 호출되는지 확인용)
    }

    void ShowYourName() {
        cout << "I'm class AAA" << endl;
    }
};

class BBB { // BBB 클래스 선언
private:
    AAA &ref; // 참조자가 멤버변수로 선언됨! -> 이니셜라이저로 초기화해야 함!!!
    const int &num; // 참조자 + const로 멤버변수 선언됨 -> 이니셜라이저로 초기화해야 함!!!

public:
    BBB(AAA &r, const int &n): ref(r), num(n) { // 생성자, 멤버 이니셜라이저로 초기화
        // empty constructor body
    }

    void ShowYourName() {
        ref.ShowYourName(); // ref: AAA의 객체 -> AAA 클래스의 ShowYourName 함수 호출
        cout << "and" << endl;
        cout << "I ref num" << num << endl;
    }
};

int main(void) {
    AAA obj1;
    BBB obj2(obj1, 20);
    obj2.ShowYourName();
    return 0;
}
```

## 디폴트 생성자(Default Constructor)

객체가 되기 위해서는 반드시 하나의 생성자가 호출되어야 한다. 따라서 생성자가 정의되지 않은 클래스에는 디폴트 생성자라는 것이 자동으로 삽입된다.

```cpp
AAA() {} // 디폴트 생성자
```

```cpp
AAA *ptr = new AAA; // 동적할당의 과정에서도 생성자는 호출된다.
```

## private 생성자

객체의 생성이 “클래스 내부”에서 진행된다면, 생성자가 private으로 선언되어도 된다.

```cpp
#include <iostream>
using namespace std;

class AAA {
private:
    int num;
public:
    AAA() : num(0) {} // public 생성자
    AAA& CreateInitObj(int n) const { // 위가 아닌, 아래의 private에서 정의된 생성자를 통해 객체 생성 및 반환, 반환형은 참조자 형태
        AAA *ptr = new AAA(n);
        return *ptr; // 반환값으로 동적할당된 *ptr이 옴, 반환형은 참조자형
    }

    void ShowNum() const { cout << num << endl; }
private:
    AAA(int n) : num(n) {}
};

int main(void) {
    AAA base; // public 생성자 호출
    base.ShowNum(); // 0

    AAA &obj1 = base.CreateInitObj(3); // base를 이용해서 CreateInitObj 함수로 객체 생성, private 생성자 호출
    // CreateInitObj 함수의 반환형이 참조자형이므로 & 붙여줘야 함.
    obj1.ShowNum();

    AAA &obj2 = base.CreateInitObj(12);
    obj2.ShowNum();

    delete &obj1; // 동적할당했으니, 메모리 해제!!
    delete &obj2;
    return 0;
}
```

private 생성자는 객체의 생성방법을 제한하고자 하는 경우에 매우 유용하게 사용된다.

## 소멸자의 이해와 활용

객체 생성시 반드시 호출되는 것이 생성자라면, 객체소멸시 반드시 호출되는 것이 소멸자이다. 

- 클래스의 이름 앞에 “~”가 붙은 형태의 이름을 갖는다.
- 반환형이 선언되어 있지 않으며, 실제로 반환하지 않는다.
- 매개변수는 void형으로 선언되어야 하기 때문에 오버로딩도, 디폴트 값 설정도 불가능하다.

이러한 소멸자는 대개 생성자에서 할당된 리소스의 소멸에 사용된다.

```cpp
#include <iostream>
using namespace std;

class Person { //
private:
    char *name; // 이름, * -> 문자열이 저장된 메모리의 첫 주솟값이 저장됨.
    int age; // 나이
public:
    Person(char *myname, int myage) { // 생성자 정의
        int len = strlen(myname) + 1; // 입력받은 myname의 길이 + 1 -> len에 저장
        name = new char[len]; // 멤버변수 name은 len길이의 배열 동적 할당
        strcpy(name, myname); // name <- myname
        age = myage; // 나이 저장
    }

    void ShowPersonInfo() const { // 정보 출력 함수, const함수 -> 멤버변수 수정 불가능
        cout << "이름: " << name << endl;
        cout << "나이: " << age << endl;
    }

    ~Person() { // 소멸자 정의
        delete []name; // 동적할당된 name 배열 메모리 해제
        cout << "called destructor!" << endl; // 소멸자 호출 확인용 출력
    }
};

int main(void) {
    Person man1("Song su min", 21);
    Person man2("Bae sueng ho", 25);
    man1.ShowPersonInfo();
    man2.ShowPersonInfo();
    return 0;
}
```

## 문제 04-3 [C++ 기반의 데이터 입출력]

### 문제 1

```cpp
#include <iostream>
using namespace std;

class Point {
private:
    int xpos, ypos;
public:
    Point(int x, int y) {
        xpos = x;
        ypos = y;
    }

    void ShowPointInfo() const {
        cout << "[" << xpos << ", " << ypos << "]" << endl;
    }
};

class Circle {
private:
    Point center; // 원의 중심
    int radius; // 원 반지름

public:
    Circle(int x, int y, int r) : center(x, y){ // 멤버변수로 선언된 객체의 생성자 호출에는 멤버 이니셜라이저를 활용해야 함.
        radius = r;
    }

    void ShowCircleInfo() const {
        center.ShowPointInfo(); // Point 클래스의 멤버함수 호출
        cout << "원 반지름: " << radius << "cm" << endl;
    }
};

class Ring {
private:
    Circle outterCircle, innerCircle;

public:
    Ring(int xpos1, int ypos1, int rad1, int xpos2, int ypos2, int rad2)
        : outterCircle(xpos1, ypos1, rad1), innerCircle(xpos1, ypos2, rad2) {};

    void ShowRingInfo() const {
        cout << "Inner Circle Info..." << endl;
        innerCircle.ShowCircleInfo(); // Circle 클래스의 멤버함수 호출
        cout << "Outter Circle Info..." << endl;
        outterCircle.ShowCircleInfo();
    }
};

int main(void) {
    Ring ring(1,1,9,2,2,4);
    ring.ShowRingInfo();
    return 0;
}
```

### 문제 2

```cpp
#include <iostream>
#include <cstring>
using namespace std;

namespace COMP_POS { // 직급 관리 이름공간
    enum {CLERK,SENIOR,ASSIST,MANAGER}; // 직급명, 0,1,2,3

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
```