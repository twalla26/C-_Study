# 04-2 캡슐화(Encapsulation)

---

```cpp
#include <iostream>
using namespace std;

class SinivelCap { // 콧물 처치용 캡슐
public:
    void Take() const { // 캡슐 복용 함수
        cout << "콧물이 싹~ 납니다." << endl; // 콧물이 나음
    }
};

class SneezeCap { // 재채기 처치용 캡슐
public:
    void Take() const { // 캡슐 복용 함수
        cout << "재채기가 멎습니다." << endl; // 재채기 나음
    }
};

class SnuffleCap { // 코막힘 처치용 캡슐
public:
    void Take() const { // 캡슐 복용 함수
        cout << "코가 뻥 뚫립니다." << endl; // 코막힘 나음
    }
};

class ColdPatient { // 감기 환자 클래스 -> 캡슐 클래스 객체를 복용할 것임
public:
    void TakeSinivelCap(const SinivelCap &cap) const { // 콧물 처치 캡슐 복용 함수, SinivelCap 참조자 선언! const 함수
        cap.Take();
    }
    void TakeSneezeCap(const SneezeCap &cap) const {
        cap.Take();
    }
    void TakeSnuffleCap (const SnuffleCap &cap) const {
        cap.Take();
    }
};

int main(void) {
    SinivelCap scap; // 캡슐 객체 생성
    SneezeCap zcap;
    SnuffleCap ncap;

    ColdPatient sufferer; // 환자 객체 생성
    sufferer.TakeSinivelCap(scap); // 캡슐 복용
    sufferer.TakeSneezeCap(zcap);
    sufferer.TakeSnuffleCap(ncap);
    return 0;
}
```

콧물이 싹~ 납니다.
재채기가 멎습니다.
코가 뻥 뚫립니다.

위 예제에서 “코감기는 항상 콧물, 재채기, 코막힘을 동반한다.”는 내용을 가정한다면 캡슐화는 무너질 것이다. 만약 이들을 하나의 캡슐로 만들면 복용 과정이 훨씬 간소화될 것이다.

```cpp
#include <iostream>
using namespace std;

class SinivelCap { // 콧물 처치용 캡슐
public:
    void Take() const { // 캡슐 복용 함수
        cout << "콧물이 싹~ 납니다." << endl; // 콧물이 나음
    }
};

class SneezeCap { // 재채기 처치용 캡슐
public:
    void Take() const { // 캡슐 복용 함수
        cout << "재채기가 멎습니다." << endl; // 재채기 나음
    }
};

class SnuffleCap { // 코막힘 처치용 캡슐
public:
    void Take() const { // 캡슐 복용 함수
        cout << "코가 뻥 뚫립니다." << endl; // 코막힘 나음
    }
};

class CONTAC600 { // CONTAC600 캡슐 클래스
private:
    SinivelCap sin; // 캡슐 객체 생성
    SneezeCap sne;
    SnuffleCap snu;

public:
    void Take() const { // 복용 함수 -> 순서 정해짐.
        sin.Take();
        sne.Take();
        snu.Take();
    }
};

class ColdPatient { // 감기 환자 클래스 -> 캡슐 클래스 객체를 복용할 것임
public:
    void TakeCONTAC600(const CONTAC600 &cap) const { // CONTAC600 복용 -> 세개 순서대로 복용
        cap.Take();
    }
};

int main(void) {
    CONTAC600 cap;
    ColdPatient sufferer;
    sufferer.TakeCONTAC600(cap);
    return 0;
}
```

→ ColdPatient 클래스가 매우 간결해짐.

→ 약의 복용 역시 간결해짐.

### 캡슐화에는 정보은닉이 기본적으로 포함된다.

캡슐화는 감싸는 개념이다. 그런데 감쌀 때 이왕이면 멤버변수가 보이지 않게 정보를 은닉해서 감싸는 것이 좋다. 그래서 캡슐화는 기본적으로 정보은닉을 포함하는 개념이라고도 이야기한다.

### 문제 04-2 [다양한 클래스의 정의]

```cpp
#include <iostream>
using namespace std;

class Point {
private:
    int xpos, ypos;
public:
    void Init(int x, int y) {
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
    void Init(int x, int y, int r) {
        center.Init(x, y);
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
    void Init(int xpos1, int ypos1, int rad1, int xpos2, int ypos2, int rad2) {

        if (rad1 > rad2) {
            outterCircle.Init(xpos1, ypos1, rad1);
            innerCircle.Init(xpos2, ypos2, rad2);
        }
        else if (rad1 < rad2) {
            outterCircle.Init(xpos2, ypos2, rad2);
            innerCircle.Init(xpos1, ypos1, rad1);
        }
        else {
            cout << "두 반지름의 길이가 달라야 고리를 만들 수 있습니다." << endl;
        }
    }

    void ShowRingInfo() const {
        cout << "Inner Circle Info..." << endl;
        innerCircle.ShowCircleInfo(); // Circle 클래스의 멤버함수 호출
        cout << "Outter Circle Info..." << endl;
        outterCircle.ShowCircleInfo();
    }
};

int main(void) {
    Ring ring;
    ring.Init(1, 1, 4, 2, 2, 9);
    ring.ShowRingInfo();
    return 0;
}
```

Ring, Circle, Point 클래스 모두 자신의 정보를 출력하기 위한 함수를 멤버에 포함시켜서 캡슐화를 완성하였다.