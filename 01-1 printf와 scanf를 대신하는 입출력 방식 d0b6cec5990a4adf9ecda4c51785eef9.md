# 01-1 printf와 scanf를 대신하는 입출력 방식

---

## 문자열 “Hello World!” 출력

```cpp
#include <iostream> // 헤더파일 선언문 -> std, cout, endl 등을 사용할 수 있게 함.

int main(void) {
    int num = 20;
    std::cout << "Hello World!" << std::endl;
    std::cout << "Hello " << "World!" << std::endl;
    std::cout << num << ' ' << 'A';
    std::cout << ' ' << 3.14 << std::endl;
    return 0;
}
// << 연산자를 이용한 std::endl의 출력은 개행으로 이어진다.
```

## scanf를 대신하는 데이터의 입력

```cpp
#include <iostream> // 헤더파일 선언문 -> 키보드로부터의 데이터 입력에도 헤더파일 선언문이 필요함.

int main(void) {
    int val1;
    std::cout << "첫 번째 숫자 입력: ";
    std::cin >> val1;

    int val2;
    std::cout << "두 번째 숫자 입력: ";
    std::cin >> val2;

    int result = val1 + val2;
    std::cout << "덧셈 결과: " << result << std::endl;
    return 0;
}
// 키보드로부터의 데이터 입력에는 std::cin 과 >> 연산자가 사용됨.
// 변수 선언은 어디서나 가능 (C의 경우, 항상 제일 먼저 등장)
```

변수의 자료형을 double로 선언해보자.

```cpp
#include <iostream> // 헤더파일 선언문 -> 키보드로부터의 데이터 입력에도 헤더파일 선언문이 필요함.

int main(void) {
    double val1;
    std::cout << "첫 번째 숫자 입력: ";
    std::cin >> val1;

    double val2;
    std::cout << "두 번째 숫자 입력: ";
    std::cin >> val2;

    double result = val1 + val2;
    std::cout << "덧셈 결과: " << result << std::endl;
    return 0;
}
// 키보드로부터의 데이터 입력에는 std::cin 과 >> 연산자가 사용됨.
// 변수 선언은 어디서나 가능 (C의 경우, 항상 제일 먼저 등장)
```

## BetweenAdder.cpp

```cpp
#include <iostream> // 헤더파일 선언문

int main(void) {
    int val1, val2;
    int result = 0;
    std::cout << "두 개의 숫자 입력: ";
    std::cin >> val1 >> val2; // 두 개의 정수를 받아서 val1, val2에 순서대로 저장할 것을 명령
    // 두 변수의 경계는 탭, 스페이스 바, Enter 키의 입력과 같은 공백에 의해 나누어 짐.

    if (val1 < val2) {
        for (int i = val1 + 1; i < val2; i++) { // for문의 초기화 문장 내에서 변수 선언 가능
            result += i;
        }
    }
    else {
        for (int i = val2 + 1; i < val1; i++) {
            result += 1;
        }
    }

    std::cout << "두 수 사이의 정수 합: " << result << std::endl;
    return 0;
}
```

## 배열 기반의 문자열 입출력

```cpp
#include <iostream> // 헤더파일 선언문

int main(void) {
    char name[100];
    char lang[200];

    std::cout << "이름은 무엇입니까? ";
    std::cin >> name; // 배열에 문자열 저장을 명령

    std::cout << "좋아하는 프로그래밍 언어는 무엇인가요? ";
    std::cin >> lang;

    std::cout << "내 이름은 " << name << "입니다.\n";
    std::cout << "제일 좋아하는 언어는 " << lang << "입니다." << std::endl;
    return 0;
}
```

## 문제 01-1 [C++ 기반의 데이터 입출력]

### 문제 1

사용자로부터 총 5개의 정수를 입력받아서, 그 합을 출력하는 프로그램을 작성해보자.

```cpp
#include <iostream>

int main(void) {
    int a, b, c, d, e, result;
    std::cout << "1번째 정수 입력: ";
    std::cin >> a;
    std::cout << "2번째 정수 입력: ";
    std::cin >> b;
    std::cout << "3번째 정수 입력: ";
    std::cin >> c;
    std::cout << "4번째 정수 입력: ";
    std::cin >> d;
    std::cout << "5번째 정수 입력: ";
    std::cin >> e;
    result = a + b + c + d + e;
    std::cout << "합계: " << result;
    return 0;
}
```

### 문제 2

사용자로부터 이름과 전화번호를 문자열의 형태로 입력 받아서, 입력 받은 데이터를 그대로 출력하는 프로그램을 작성해보자.

```cpp
#include <iostream>

int main(void) {

    char name[100];
    char num[100];

    std::cout << "이름이 무엇입니까? ";
    std::cin >> name;

    std::cout << "전화번호가 무엇입니까? ";
    std::cin >> num;

    std::cout << "이름: " << name << std::endl;
    std::cout << "번호: " << num << std::endl;
		
		return 0;
}
```

### 문제 3

숫자 하나를 입력 받아서 그 숫자에 해당하는 구구단을 출력하는 프로그램을 작성해보자.

```cpp
#include <iostream>

int main(void) {

    int num;

    std::cin >> num;

    for (int i = 1; i < 10; i++) {
        std::cout << num << " * " << i << " = " << num*i << std::endl;
    }

    return 0;
}
```

### 문제 4

판매원들의 급여 계산 프로그램을 작성해보자.

```cpp
#include <iostream>

int main(void) {
    int sale_price = 0;
    while (sale_price != -1) {
        std::cout << "판매 금액을 만원 단위로 입력(-1 to end): ";
        std::cin >> sale_price;
        if (sale_price == -1) {
            std::cout << "프로그램을 종료합니다.";
            return 0;
        }
        else {
            std::cout << "이번 달 급여: " << 50 + (sale_price * 0.12) << "만원" << std::endl;
        }
    }
}
```