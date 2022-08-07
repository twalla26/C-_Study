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