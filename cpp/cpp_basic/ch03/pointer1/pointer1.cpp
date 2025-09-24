#include<iostream>
using namespace std;

int main()
{
    char char_value = 'A';
    int int_value = 123;
    double double_value = 123.456;

    char *char_pointer_value = &char_value;
    int *int_pointer_value = &int_value;
    double *double_pointer_value = &double_value;

    // 데이터 출력
    cout << "char_value = " << char_value << endl;
    cout << "int_value = " << int_value << endl;
    cout << "double_value = " << double_value << endl;

    cout << endl;

    // 역참조연산자로 포인터 변수가 가르키는 데이터 출력
    cout << "*char_pointer_value = " << *char_pointer_value << endl;
    cout << "*int_pointer_value = " << *int_pointer_value << endl;
    cout << "*double_pointer_value = " << *double_pointer_value << endl;

    cout << endl;

    // 역참조 연산자로 원본 데이터 엎어쓰기
    *char_pointer_value = 'Z';
    *int_pointer_value = 321;
    *double_pointer_value = 654.321;

    cout << "char_value = " << char_value << endl;
    cout << "int_value = " << int_value << endl;
    cout << "double_value = " << double_value << endl;

    // *를 제거 하여 출력해보면 각각의 값이 저장된 메모리의 주소를 출력 할 수 있음
    cout << "*char_pointer_value = " << char_pointer_value << endl;
    cout << "*int_pointer_value = " << int_pointer_value << endl;
    cout << "*double_pointer_value = " << double_pointer_value << endl;

    return 0;
}