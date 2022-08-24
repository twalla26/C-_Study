#include <iostream>
using namespace std;

// #define: 매크로 정의 -> 컴파일러가 컴파일 전에, 전처리됨.
#define ID_LEN 20
#define MAX_SPD 200
#define FUEL_STEP 2
#define ACC_STEP 10
#define BRK_STEP 10
// 매크로 상수 -> 미리 정의한 매크로 상수명이 쓰이면, 매크로 확장 문자열로 치환함.

struct Car { // Car 구조체 정의
    char gamerID[ID_LEN]; // 소유자 ID
    int fuelGauge; // 연료량
    int curSpeed; // 현재속도

    void ShowCarState() { // 차의 현재 상태 출력 함수
        cout << "소유자ID: " << gamerID << endl; // 위에 선언된 gamerID에 접근
        cout << "연료량: " << fuelGauge << "%" << endl;
        cout << "현재속도: " << curSpeed << "km/s" << endl << endl;
    }

    void Accel() { // 엑셀 함수
        if (fuelGauge <= 0) // 위에 선언된 fuelGauge에 접근
            return; // 엑셀 못 밟음.
        else // 차의 연료량이 있다면,
            fuelGauge -= FUEL_STEP; // 차의 연료량에서 FUEL_STEP(2)을 뺌.

        if (curSpeed + ACC_STEP >= MAX_SPD) { // 만약 차의 현재속도에 엑셀을 밟은 만큼의 속도(10)를 더한 값이 최고 속도(200)보다 크면
            curSpeed = MAX_SPD; // 차의 속도를 최고속도로 맞춤.
            return;
        }

        curSpeed += ACC_STEP; // 차의 현재속도에 엑셀을 밟은 만큼의 속도를 더한 값이 최고 속도보다 작으면,
        // 차의 속도에 ACC_STEP(10)을 더한 값 저장.
    }

    void Break() { // 브레이크 함수
        if (curSpeed < BRK_STEP) { // 차의 속도가 브레이크를 밟으면 줄어드는 속도량(10)보다 작으면
            curSpeed = 0; // 차 속도는 0
            return;
        }

        curSpeed -= BRK_STEP; // 그게 아니라면, 차 속도에서 10을 뺌.
    }

};


int main(void) {
    Car run99 = {"run99", 100, 0}; // run99라는 이름의 Car 구조체 생성
    Car sped77 = {"sped77", 100, 0};
    return 0;
}