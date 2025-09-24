#include <iostream>

using namespace std;

void swap_pointer(int *a, int *b) //  주소에 의한 호출 -> p147
{
    cout << "[Swap func] before swap_pointer, a : " << a << ", b : " << b << endl;
    cout << "[Swap func] before swap_pointer, &a : " << &a << ", &b : " << &b << endl
         << endl;

    int temp = *a;
    *a = *b;
    *b = temp;
    cout << "[Swap func] after swap_pointer, a : " << a << ", b : " << b << endl;
    cout << "[Swap func] after swap_pointer, &a : " << &a << ", &b : " << &b << endl
         << endl;
}

int main()
{
    int a = 5;
    int b = 10;
    cout << "[main] before swap_pointer, a : " << a << ", b : " << b << endl;
    cout << "[main] before swap_pointer, &a : " << &a << ", &b : " << &b << endl
         << endl
         << endl;

    swap_pointer(&a, &b);

    cout << "[main] after swap_pointer, a :" << a << ", b : " << b << endl;
    cout << "[main] after swap_pointer, &a : " << &a << ", &b : " << &b << endl
         << endl
         << endl;

    return 0;
}