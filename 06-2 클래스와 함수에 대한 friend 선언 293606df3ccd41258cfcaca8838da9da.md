# 06-2 클래스와 함수에 대한 friend 선언

---

## 클래스의 friend 선언

friend 선언은 private 멤버의 접근을 허용하는 선언이다. friend 선언은 클래스 내 어디든 위치할 수 있다.

```cpp
#include <iostream>
#include <cstring>
using namespace std;

class Girl; // Girl이라는 이름이 클래스의 이름임을 알림

class Boy {
private:
    int height;
    friend class Girl; // Girl 클래스에 대한 friend 선언
public:
    Boy(int len) : height(len) {} // 생성자
    void ShowYourFriendInfo(Girl &frn);
};

class Girl {
private:
    char phNum[20];
public:
    Girl(char * num) { // 생성자
        strcpy(phNum, num);
    }
    void ShowYourFriendInfo(Boy &frn);
    friend class Boy;
};

void Boy::ShowYourFriendInfo(Girl &frn) {
    cout << "Her phone number: " << frn.phNum << endl;
}

void Girl::ShowYourFriendInfo(Boy &frn) {
    cout << "His height: " << frn.height << endl;
}

int main(void) {
    Boy boy(170);
    Girl girl("010-1234-5678");
    boy.ShowYourFriendInfo(girl);
    girl.ShowYourFriendInfo(boy);
    return 0;
}
```

<aside>
🔎 friend 선언은 필요한 상황에서 극히 소극적으로 사용해야 한다.

</aside>

## 함수의 friend 선언

전역 함수를 대상으로도, 클래스의 멤버함수를 대상으로도 friend 선언이 가능하다. friend로 선언된 함수는 자신이 선언된 클래스의 private 영역에 접근이 가능하다.

```cpp
#include <iostream>
using namespace std;

class Point; // Point가 클래스의 이름임을 선언

class PointOP {
private:
    int opcnt;
public:
    PointOP() : opcnt(0) {} // 생성자
    Point PointAdd(const Point&, const Point&);
    Point PointSub(const Point&, const Point&);
    ~PointOP() { // 소멸자
        cout << "Operation times: " << opcnt << endl;
    }
};

class Point {
private:
    int x;
    int y;
public:
    Point(const int &xpos, const int &ypos) : x(xpos), y(ypos) {} // 생성자
    friend Point PointOP::PointAdd(const Point &, const Point &); // PointOP 클래스의 멤버함수에 대해 friend 선언
    friend Point PointOP::PointSub(const Point &, const Point &);
    friend void ShowPointPos(const Point&); // 전역함수에 대해 friend 선언
};

Point PointOP::PointAdd(const Point & pnt1, const Point & pnt2) { // 반환형은 Point 객체, 인자로 전달받은 Point 객체를 참조자 선언, const 선언
    opcnt++;
    return Point(pnt1.x+pnt2.x, pnt1.y+pnt2.y); // 두 객체의 좌표를 서로 더한 후, Point 객체 반환
    // PointAdd 함수는 PointOP 클래스에서 선언된 멤버 함수지만, Point 클래스의 friend로 선언됨
    // -> Point의 private 멤버 변수 x, y에 접근 가능
}

Point PointOP::PointSub(const Point & pnt1, const Point & pnt2) {
    opcnt++;
    return Point(pnt1.x-pnt2.x, pnt1.y-pnt2.y);
}

int main(void) {
    Point pos1(1, 2); // Point 객체 pos1 생성
    Point pos2(2, 4); // Point 객체 pos2 생성
    PointOP op; // PointOP 객체 op 생성

    ShowPointPos(op.PointAdd(pos1, pos2)); // op의 멤버함수 PointAdd 호출 -> 더한 후, Point 객체 반환 -> ShowPointPos 함수 호출
    ShowPointPos(op.PointSub(pos2, pos1));
    return 0;
}

void ShowPointPos(const Point& pos) { // 인자로 받은 Point 객체를 참조자, const 선언
    cout << "x: " << pos.x << ", "; // ShowPointPos함수가 Point 클래스의 friend로 선언됨 -> private 멤버 x, y에 접근 가능
    cout << "y: " << pos.y << endl;
}
```

x: 3, y: 6
x: 1, y: 2
Operation times: 2