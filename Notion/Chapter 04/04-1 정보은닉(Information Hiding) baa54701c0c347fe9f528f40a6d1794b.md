# 04-1 정보은닉(Information Hiding)

---

좋은 클래스가 되기위한 조건에는 ‘정보은닉'과 ‘캡슐화'가 있다.

## 정보은닉

### 클래스의 멤버변수가 public으로 선언되었을 때 발생할 수 있는 문제점

```cpp
#include <iostream>
using namespace std;

class Point { // Point 클래스 선언 (직사각형의 꼭짓점 좌표)
public: // 멤버 변수를 public으로 선언함 -> 어디서든 접근 가능
    int x; // x좌표의 범위는 0 이상 100 이하
    int y; // y좌표의 범위는 0 이상 100 이하
};

class Rectangle { // Rectangle 클래스 선언, 직사각형은 두개의 점으로 표현 가능
public: // 멤버 변수를 public으로 선언함! -> 어디서든 접근 가능
    Point upLeft; // 좌표로서 Point 클래스의 객체 사용
    Point lowRight;

public: // 멤버 함수 public으로 선언
    void ShowRecInfo() { // 직사각형의 좌표 출력 함수
        cout << "좌 상단: " << '[' << upLeft.x << ", ";
        cout << upLeft.y << ']' << endl;
        cout << "우 하단: " << '[' << lowRight.x << ", ";
        cout << lowRight.y << ']' << endl << endl;
    }
};

int main(void) {
    Point pos1 = {-2, 4}; // 직사각형을 구성할 두 개의 Point 객체 생성, 멤버 변수가 public으로 선언되었기에, 구조체 변수를 초기화하듯 초기화 가능
    Point pos2 = {5, 9};
    Rectangle rec = {pos2, pos1}; // pos1, pos2가 각각 upLeft, lowRight가 됨.
    rec.ShowRecInfo();
    return 0;
}
```

- 점의 좌표는 0이상 100이하여야 하는데, 그렇지 못한 Point 객체가 있다.
- Rectangle 객체의 좌 상단 좌표 값이 우 하단 좌표 값보다 크다.

→ 제한된 방법으로의 접근만 허용해서 잘못된 값이 저장되지 않도록 도와야 하고, 또 실수를 했을 때, 실수가 쉽게 발견되도록 해야 한다.

### Point.h

```cpp
//
// Created by twalla on 2022/08/29.
//

#ifndef __POINT_H_
#define __POINT_H_

class Point {
private:
    int x;
    int y;

public:
    bool InitMembers(int xpos, int ypos);
    int GetX() const;
    int GetY() const;
    bool SetX(int xpos);
    bool SetY(int ypos);
};

#endif //__POINT_H_
```

### Point.cpp

```cpp
#include <iostream>
#include "Point.h"
using namespace std;

bool Point::InitMembers(int xpos, int ypos) { // 잘못된 값이 전달되면 에러를 발생시키며, 값의 저장을 허용하지 않음.
    if (xpos < 0 || ypos < 0) {
        cout << "벗어난 범위의 값 전달" << endl;
        return false;
    }

    x = xpos;
    y = ypos;
    return true;
}

int Point::GetX() const { // const 함수!!
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

→ 멤버변수를 private으로 선언하고, 해당 변수에 접근하는 함수를 별도로 정의해서, 안전한 형태로 멤버 변수의 접근을 유도하는 것이 바로 ‘정보은닉'이며, 이는 좋은 클래스가 되기 위한 기본조건이 된다!

### Rectangle.h

```cpp
//
// Created by twalla on 2022/08/29.
//

#ifndef __RECTANGLE_H_
#define __RECTANGLE_H_

#include "Point.h"

class Rectangle {
private:
    Point upLeft;
    Point lowRight;

public:
    bool InitMembers(const Point &ul, const Point &lr); // 좌 상단과 우 하단의 좌표가 뒤바뀌는 것을 검사하는 함수
    void ShowRecInfo() const;
};

#endif // __RECTANGLE_H_
```

### Rectangle.cpp

```cpp
//
// Created by twalla on 2022/08/29.
//

#include <iostream>
#include "Rectangle.h"
using namespace std;

bool Rectangle::InitMembers(const Point &ul, const Point &lr) { // 직사각형 구성 좌표 2개를 받음
    if (ul.GetX() > lr.GetX() || ul.GetY() < lr.GetY()) {
        cout << "잘못된 위치정보 전달" << endl;
        return false;
    }
    upLeft = ul;
    lowRight = lr;
    return true;
}

void Rectangle::ShowRecInfo() const { // const 함수!!
    cout << "좌 상단: " << '[' << upLeft.GetX() << ", ";
    cout << upLeft.GetY() << ']' << endl;
    cout << "우 하단: " << '[' << lowRight.GetX() << ", ";
    cout << lowRight.GetY() << ']' << endl << endl;
}
```

### RectangleFaultFind.cpp

```cpp
//
// Created by twalla on 2022/08/29.
//

#include <iostream>
#include "Point.h"
#include "Rectangle.h"
using namespace std;

int main(void) {
    Point pos1; // 좌표 pos1 생성
    if (!pos1.InitMembers(-2, 4)) { // pos1 좌표가 (-2, 4)라면, InitMembers함수가 "벗어난 범위~~" 출력, false 반환
        // false가 반환되었지만, if 문 바로 뒤에 ! 때문에 true가 되어, "초기화 실패"가 출력됨.
        cout << "초기화 실패" << endl;
    }
    if (!pos1.InitMembers(2, 10)) { // (2, 10)의 경우 좌표 저장 후, true 반환
        cout << "초기화 실패" << endl; // 출력 X
    }

    Point pos2; // 좌표 pos2 생성
    if (!pos2.InitMembers(5, 9)) { // (5, 9)의 경우 좌표 저장 후, true 반환
        cout << "초기화 실패" << endl; // 출력 X
    }

    Rectangle rec; // rec 객체 생성
    if (!rec.InitMembers(pos2, pos1)) { // pos2, pos1 전달 -> 좌 상단, 우 하단 조건 충족
        cout << "직사각형 초기화 실패" << endl; // 출력X
    }
    if (!rec.InitMembers(pos1, pos2)) { // pos2, pos1 전달 -> 좌 상단, 우 하단 조건 불충족 -> "잘못된 위치~~" 출력, false 반환
        cout << "직사각형 초기화 실패" << endl; // 출력
    }

    rec.ShowRecInfo();
    return 0;
}
```

벗어난 범위의 값 전달
초기화 실패
잘못된 위치정보 전달
직사각형 초기화 실패
좌 상단: [2, 10]
우 하단: [5, 9]

## const 함수

```cpp
int GetX() const;
int GetY() const;
void ShowRecInfo() const;
```

→ 이 함수 내에서는 멤버변수에 저장된 값을 변경하지 않겠다!

→ 프로그래머의 실수 최소화!

```cpp
#include <iostream>
using namespace std;

class SimpleClass {
private:
    int num;

public:
    void InitNum(int n) {
        num = n;
    }

    int GetNum() {
        return num; // const 선언이 추가되어야 아래의 컴파일 에러 소멸
    }

    void ShowNum() const {
        cout << GetNum() << endl; // 컴파일 에러 발생!!
    }
};
```

<aside>
🔎 const 함수 내에서는 const가 아닌 함수의 호출이 제한된다!

</aside>

const 함수는 값의 변경 능력을 가진 함수의 호출을 허용하지 않는다.(실제 값의 변경여부에 상관없이!)

### 문제 04-1 [정보은닉과 const]

```cpp
#include <iostream>
using namespace std;

class FruitSeller { // 과일 판매자 클래스 선언
private:
    int APPLE_PRICE; // 판매하는 사과 가격(대문자 -> 변하지 않는 값임을 암시)
    int numOfApples; // 사과 개수
    int myMoney; // 판매자의 돈

public:
    void InitMembers(int price, int num, int money) { // (판매할 사과 가격, 가지고 있는 사과 개수, 가지고 있는 돈)
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

    void ShowSalesResult() const { // 판매 현황 함수
        cout << "남은 사과: " << numOfApples << endl;
        cout << "판매 수익: " << myMoney << endl;
    }
};

class FruitBuyer { // 사과 구매자 클래스 선언
private:
    int myMoney; // 구매자 돈
    int numOfApples; // 구매자가 산 총 사과 개수

public:
    void InitMembers(int money) { // (구매자가 가진 돈)
        myMoney = money;
        numOfApples = 0; // 구매자가 구매한 사과 개수
    }

    void BuyApples(FruitSeller &seller, int money) { // 사과 구매 함수 (판매자 참조자 선언, 구매하기 위해 낸 돈)
        if (money <= 0) {
            cout << "잘못된 정보 입력" << endl;
            return;
        }
        numOfApples += seller.SaleApples(money); // 구매자 가진 사과 개수에, 판매자에게 산 사과 개수를 더함. public -> 함수 호출 어디서나 가능
        myMoney -= money; // 돈은 낸 만큼 감소
    }

    void ShowBuyResult() const { // 구매 결과 함수
        cout << "현재 잔액: " << myMoney << endl;
        cout << "사과 개수: " << numOfApples << endl << endl;
    }
};

int main(void) {
    FruitSeller seller; // seller 객체 생성
    seller.InitMembers(1000, 20, 0); // 사과 가격: 1000, 개수: 20, 돈: 0
    FruitBuyer buyer; // buyer 객체 생성
    buyer.InitMembers(5000); // 돈: 5000
    buyer.BuyApples(seller, 2000); // 과일의 구매!!, seller 객체에게 2000원 지불

    cout << "과일 판매자의 현황" << endl;
    seller.ShowSalesResult();
    cout << "과일 구매자의 현황" << endl;
    buyer.ShowBuyResult();
    return 0;
}
```