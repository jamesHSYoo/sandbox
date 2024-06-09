#include<iostream>

using namespace std;

int main()
{
    int customer_num = 5;

    cout << "오늘의 손님 수 : " << customer_num << endl;
    //cin >> customer_num;  // 손님 수를 사용자로부터 입력 받음 -> 원래는 입력받게 해야되는데 mac에서 잘 안되서 그냥 일단 입력 받았다고 하고다음의 코드 실행
    
    string *bread = new string[customer_num];

    for(int i = 0 ; i < customer_num ; i++)
    {
        *(bread + i)= "빵_" + to_string(i); 
    }

    cout << endl << "생산된 빵" << endl;

    for(int i = 0 ; i < customer_num ; i++)
    {
        cout << *(bread + i) << endl;
    }

    delete[] bread;

    return 0;
}