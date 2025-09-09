#include<iostream>

using namespace std;

int main() {

    int a = 100;

    cout << "a의 값 : " << a << endl;
    // cout << "*a의 값 : " << *a << endl; 요건 에러남
    cout << "&a 의 값 : " << &a << endl;

    int *b = &a;
    cout << "*b의 값 : " << *b << endl; 
    cout << "b의 값 : " << b << endl;
    return 0;
}