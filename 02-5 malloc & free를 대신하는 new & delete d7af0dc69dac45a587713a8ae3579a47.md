# 02-5 malloc & free를 대신하는 new & delete

---

## new & delete

new: HEAP에 메모리를 만들고 그 주소를 반환 → 주소를 반환하기 때문에 new의 값을 저장하는 변수는 포인터 변수여야 한다. new 옆에는 힙에 할당할 메모리의 크기에 해당하는 타입을 적어준다.

delete: 가리키는 주소의 메모리 해제

### C에서는?

```cpp
#include <iostream>
#include <string.h>
#include <stdlib.h> // 문자열 변환, 사 난수 생성, 동적 메모리 관리 등의 함수들을 포함
using namespace std;

char *MakeStrAdr(int len) {
    char *str = (char*)malloc(sizeof(char)*len); // 문자열 저장을 위한 배열을 힙 영역에 할당하고 있다.
    return str;
}

int main(void) {
    char *str = MakeStrAdr(20);
    strcpy(str, "I am so happy~");
    cout << str << endl;
    free(str); // 힙에 할당된 메모리 공간 소멸
    return 0;
}
```

### C++에서는 new와 delete가 malloc, free의 역할을 한다.

```cpp
#include <iostream>
#include <string.h>
using namespace std;

char *MakeStrAdr(int len) {
    // char *str = (char*)malloc(sizeof(char)*len); // 문자열 저장을 위한 배열을 힙 영역에 할당하고 있다.
    char *str = new char[len]; // new를 이용한 동적할당이 훨씬 간결함.
    return str;
}

int main(void) {
    char *str = MakeStrAdr(20);
    strcpy(str, "I am so happy~");
    cout << str << endl;
     // free(str); // 힙에 할당된 메모리 공간 소멸
     delete []str; // 배열의 형태로 할당된 메모리 공간 해제
    return 0;
}
```

### 객체의 생성에는 반드시 new & delete

C++에서는 malloc, free 함수의 호출이 문제가 될 수 있다. 예제를 통해 알아보자.

```cpp
#include <iostream>
#include <stdlib.h>
using namespace std;

class Simple {
public:
    Simple() {
        cout << "I'm simple constructor!" << endl;
    }
};

int main(void) {
    cout << "case 1: ";
    Simple *sp1 = new Simple; // new 연산자로 힙 영역에 변수 할당

    cout << "case 2: ";
    Simple *sp2 = (Simple*)malloc(sizeof(Simple)*1); // malloc 함수 호출을 통해서 힙 영역에 변수 할당

    cout << endl << "end of main" << endl;
    delete sp1;
    free(sp2);
    return 0;
}
```

[결과]

case 1: I'm simple constructor!
case 2:
end of main

<aside>
🔎 new와 malloc 함수의 동작방식에는 차이가 있다.

</aside>

일단 여기까지만 알고 넘어가자!

### 힙에 할당된 변수? 이제 포인터를 사용하지 않아도 접근할 수 있어용.

```cpp
#include <iostream>
using namespace std;

int main(void) {
    int *ptr = new int; // 힙 영역에 변수 할당
    int &ref = *ptr; // 힙 영역에 할당된 변수에 대한 참조자 선언
    ref = 20;
    cout << *ptr << endl; // 20 출력
    return 0;
}
```

참조자의 선언을 통해서, 포인터 연산 없이 힙 영역에 접근했다는 사실에 주목!

### 문제 02-3 [구조체에 대한 new&delete 연산]

```cpp
#include <iostream>
#include <string>
using namespace std;

typedef struct __Point {
    int xpos;
    int ypos;
} Point;

Point& PntAdder(const Point &p1, const Point &p2) { // pptr1, pptr2 참조자 선언!
    Point *pptr = new Point;
    pptr -> xpos = p1.xpos + p2.xpos; // pptr의 xpos에 pptr1, pptr2의 참조자 p1, p2의 xpos 더한 값 저장
    pptr -> ypos = p1.ypos + p2.ypos;
    return *pptr; // pptr 주솟값 반환, 변환형이 참조형임 -> main 함수에서 이 함수의 반환값으로 참조자를 선언할 수 있음.
}

int main(void) {

    Point *pptr1 = new Point; // new: HEAP에 메모리를 만들고 그 주소 반환
    pptr1 -> xpos = 3; // pptr1의 xpos에 3 저장
    pptr1 -> ypos = 30; // pptr1의 ypos에 30 저장

    Point *pptr2 = new Point;
    pptr2 -> xpos = 70; // pptr2의 xpos에 70 저장
    pptr2 -> ypos = 7; // pptr2의 ypos에 7 저장

    Point &pref = PntAdder(*pptr1, *pptr2); // 함수의 반환값으로 참조자 pref 선언!
    cout << "[" << pref.xpos << ", " << pref.ypos << "]" << endl;
}
```