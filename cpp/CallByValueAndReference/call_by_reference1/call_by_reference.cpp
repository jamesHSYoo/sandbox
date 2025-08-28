#include<iostream>

using namespace std;

void swap(int &a, int &b)
{
    cout << "[Swap func] before swap, a : " << a << ", b : " << b << endl;
    cout << "[Swap func] before swap, &a : " << &a << ", &b : " << &b << endl;

    int temp = a;
    a = b;
    b = temp;
    cout << "[Swap func] after swap, a : " << a << ", b : " << b << endl;
    cout << "[Swap func] after swap, &a : " << &a << ", &b : " << &b << endl;
} 

int main()
{
    int a = 5;
    int b = 10;
    cout << "[main] before swap, a : " << a << ", b : " << b << endl << endl;
    cout << "[main] before swap, &a : " << &a << ", &b : " << &b << endl << endl;

    swap(a, b);

    cout << "[main] after swap, a :" << a << ", b : " << b << endl;
    cout << "[main] after swap, &a : " << &a << ", &b : " << &b << endl << endl;

    return 0;
}