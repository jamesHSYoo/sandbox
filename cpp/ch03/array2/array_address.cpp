#include<iostream>

using namespace std;

int main()
{
    int lotto[45] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,32,33,34,35,36,37,38,39,40,41, 42, 43, 44, 45 };

    cout << "각 값이 저장된 메모리 주소를 보자" << endl;
    cout << "lotto[0] address : " << &lotto[0] << endl;
    cout << "lotto[1] address : " << &lotto[1] << endl;
    cout << "lotto[2] address : " << &lotto[2] << endl;
    cout << "lotto[3] address : " << &lotto[3] << endl;
    cout << "lotto[4] address : " << &lotto[4] << endl;
    cout << "lotto[5] address : " << &lotto[5] << endl;
    cout << "lotto[6] address : " << &lotto[6] << endl;

    cout << endl;
    cout << "Pointer Approaching to display value" << endl;

    cout << "lotto[0] address : " << *(lotto + 0) << endl;
    cout << "lotto[1] address : " << *(lotto + 3) << endl;
    cout << "lotto[2] address : " << *(lotto + 20) << endl;
    cout << "lotto[3] address : " << *(lotto + 25) << endl;
    cout << "lotto[4] address : " << *(lotto + 28) << endl;
    cout << "lotto[5] address : " << *(lotto + 40) << endl;
    cout << "lotto[6] address : " << *(lotto + 44) << endl;

    return 0;
}