#include <iostream>
using namespace std;

int val = 10; // 전역변수

int SimpleFunc(void) {
    int val = 20; // 지역변수
    val += 3; // 지역변수 val의 값 3 증가
    ::val += 7; // 전역변수 val의 값 7 증가
}