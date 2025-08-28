#include<iostream>

using namespace std;

void swap(int a, int b)
{
    cout << "[Swap func] before swap, a :" << a << ", b : " << b << endl;
    int temp = a;
    a = b;
    b = temp;
    cout << "[Swap func] after swap, a :" << a << ", b : " << b << endl;
} 

// 이방식으로 하면 call by value 가 됨 call by reference 는 해당 폴더로 가서 해보면 됨
void swap1(int *ref_a, int *ref_b)  // 
{
    cout << "[Swap1 func] before swap1, ref_a :" << *ref_a << ", ref_b : " << *ref_b << endl;
    cout << "[Swap1 func] before swap1, &ref_a :" << &ref_a << ", &ref_b : " << &ref_b << endl;

    int *temp = ref_a;
    ref_a = ref_b;
    ref_b = temp;
/*
    int *temp = ref_a;  temp 는 ref의 값이 저장된 주소를 바라보고 있음. *temp(temp 값의 주소) = ref_a값 주소
    *ref_a = *ref_b;    ref_a의 값이 ref_b의 값으로 변경됨 즉, ref_a=10이 된 것임. ref_a의 주소는 변화없음
    *ref_b = *temp;     *temp 가 ref값이 저장된 주소를 바라보고 있으므로 이미 ref_a = temp = 10이므로 값의 변화가 없어서 결과값으로 모두 10이 나온것

*/

    cout << "[Swap1 func] after swap1, ref_a :" << *ref_a << ", ref_b : " << *ref_b << endl; 
    cout << "[Swap1 func] after swap1, &ref_a :" << &ref_a << ", &ref_b : " << &ref_b << endl << endl; 

}

int main()
{
    int a = 5;
    int b = 10;
    cout << "[main] before swap, a : " << a << ", b : " << b << endl;

    swap(a, b);

    cout << endl << "[main] after swap, a :" << a << ", b : " << b << endl;

    cout << "---------------- Another Case ----------------" << endl;

    int a1 = 5;
    int b1 = 10;
    cout << "[main] before swap1, a1 : " << a1 << ", b1 : " << b1 << endl;
    cout << "[main] before swap1, &a : " << &a1 << ", &b : " << &b1 << endl << endl;

    swap1(&a1, &b1);
    cout << "[main] after swap1, a1 : " << a1 << ", b1 : " << b1 << endl;
    cout << "[main] after swap1, &a : " << &a1 << ", &b : " << &b1 << endl << endl;
    return 0;

   /*
   [main] before swap, a : 5, b : 10
   [Swap func] before swap, a :5, b : 10
   [Swap func] after swap, a :10, b : 5
   
   [main] after swap, a :5, b : 10
   ---------------- Another Case ----------------
   [main] before swap1, a1 : 5, b1 : 10
   [main] before swap1, &a : 0x16b9669d0, &b : 0x16b9669cc
   
   [Swap1 func] before swap1, ref_a :5, ref_b : 10
   [Swap1 func] before swap1, &ref_a :0x16b966968, &ref_b : 0x16b966960
   [Swap1 func] after swap1, ref_a :10, ref_b : 5
   [Swap1 func] after swap1, &ref_a :0x16b966968, &ref_b : 0x16b966960
   
   [main] after swap1, a1 : 5, b1 : 10
   [main] after swap1, &a : 0x16b9669d0, &b : 0x16b9669cc      // 주소값이 복사된게 들어갔음....
   */
}