# 01-2 함수 오버로딩(Function Overloading)

---

## 함수 오버로딩이란?

 함수 오버로딩은 다름 매개 변수를 가진 같은 이름의 여러 함수를 만들 수 있는 C++의 기능이다. C언어에서는 함수의 이름만을 이용해서 호출대상을 찾지만, C++은 호출대상과 매개변수의 선언 두 가지 정보를 함께 이용하기 때문에 오버로딩이 가능하다. 

 함수의 오버로딩이 가능하려면 매개변수의 **자료형** 또는 **개수**가 달라야 한다.

```cpp
void MyFunc(int n) {...}
int MyFunc(int n) {...}
```

 위의 두 함수는 반환형이 다르다. 반환형은 함수 호출 시, 함수를 구분하는 기준이 될 수 없다. 따라서 위와 같은 함수 정의는 컴파일 오류로 이어진다.

## FunctionOverloading.cpp

```cpp
#include <iostream>

void MyFunc(void) {
    std::cout << "MyFunc(void) called" << std::endl;
}

void MyFunc(char c) {
    std::cout << "MyFunc(char c) called" << std::endl;
}

void MyFunc(int a, int b) {
    std::cout << "MyFunc(int a, int b) called" << std::endl;
}

int main(void) {
    MyFunc();
    MyFunc('A');
    MyFunc(12,13);
    return 0;
}
```

[결과]

MyFunc(void) called

MyFunc(char c) called

MyFunc(int a, int b) called 

결과를 보면 각각의 함수들이 구분되어 잘 실행된다.

## 문제 01-2 [함수 오버로딩]

다음 main 함수에서 필요로 하는 swap 함수를 오버로딩 해서 구현해보자.

```
#include <iostream>

void swap(int *a, int *b) {
    int c = 0;
    c = *a;
    *a = *b;
    *b = c;
}

void swap(char *a, char *b) {
    char c = 'A';
    c = *a;
    *a = *b;
    *b = c;
}

void swap(double *a, double *b) {
    double c = 1.1;
    c = *a;
    *a = *b;
    *b = c;
}

int main(void) {
    int num1=20, num2=30;
    swap(&num1, &num2);
    std::cout << num1 << ' ' << num2 << std::endl;

    char ch1='A', ch2='Z';
    swap(&ch1, &ch2);
    std::cout << ch1 << ' ' << ch2 << std::endl;

    double db11 = 1.111, db12 = 5.555;
    swap(&db11, &db12);
    std::cout << db11 << ' ' << db12 << std::endl;
    return 0;
}
```

[결과]

30 20
Z A
5.555 1.111