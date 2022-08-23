#include <iostream>
using namespace std;

int main(void) {
    int num = 10;
    int i = 0;

    cout << "true: " << true << endl; // true != (1을 의미하는 키워드), true를 출력하거나 정수로 형 변환을 할 경우에 1로 변환됨.
    cout << "false: " << false << endl; // false도 마찬가지..

    while (true) { // 무한루프 생성할 때 true or 1 사용
        cout << i++ << ' '; // (cout << i++): i를 출력하면서 +1을 해줌
        if (i > num) // 무한루프를 끝내는 조건문
            break; // 반복문 종료
    }
    cout << endl;

    cout << "sizeof 1: " << sizeof(1) << endl; // sizeof(): 변수, 자료형 등의 실제 byte, 메모리 공간
    cout << "sizeof 0: " << sizeof(0) << endl;
    cout << "sizeof true: " << sizeof(true) << endl;
    cout << "sizeof false: " << sizeof(false) << endl;
    // 정수형은 각각 4byte를 차지하지만, true, false의 불린형은 1byte를 차지한다.
    return 0;
}
