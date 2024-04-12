#include<iostream>

using namespace std;

int main()
{
    cout << "아스키 코드 출력하기[32 ~ 126] : \n" << endl;


    for(char i  = 32 ; i <= 126 ; i++)
    {
        cout << i << ((i % 16 == 15) ? '\n' : ' ');
    }
}