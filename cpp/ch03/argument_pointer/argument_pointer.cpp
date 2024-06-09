#include<iostream>

using namespace std;

void change_negative(int *_val)  // 포인터를 매개변수로 사용
{
    if(*_val > 0)
    {
        *_val = -(*_val);
    }
}

int main()
{
    int a = 3, b = -3;

    cout << "a value : " << a << ", a address : " << &a << endl;
    cout << "b value : " << b << ", b address : " << &b << endl;

    change_negative(&a);  // a변수의 주소값 전달
    change_negative(&b);  // b변수의 주소값 전달

    // 포인터를 이용하여 전달 하게 되면 원본의 값이 바뀌는걸 확인 할 수 있음
    cout << "change negative - a : " << a << endl;
    cout << "change negative - b : " << b << endl;
    return 0;
}

