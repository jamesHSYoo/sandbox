#include<iostream>

using namespace std;

int main()
{
    int *pt_int_value = new int;    // 동적 메모리 할당

    *pt_int_value = 100;

    cout << "저장한 100을 보고 싶을 때 : " << *pt_int_value << endl;
    cout << "저장한 100의 메모리 주소를 보고 싶을 때 "<< pt_int_value << endl;

    delete pt_int_value;     // 동적 메모리 해제

    return 0;
}



