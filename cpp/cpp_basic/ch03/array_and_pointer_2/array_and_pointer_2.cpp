#include<iostream>

using namespace std;

int main()
{
    int array[5] = {1, 2, 3, 4, 5};

    int *pointer_array = array;

    cout << "array : " << array << endl;
    cout << "pointer_array : " << pointer_array << endl << endl;

    cout << "Size of array : " << sizeof(array) << endl;     // 배열 전체의 크기 인 20 byte(4 byte * 5) 출력
    cout << "Size of pointer_array : " << sizeof(pointer_array) <<endl;  // 포인터 변수의 크기 8 byte 출력

    return 0;
}