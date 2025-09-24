#include<iostream>

using namespace std;

void change_negative(int _val)
{   
    if(_val > 0)
    {
        _val = (-1) * _val;
    }
}


int main()
{       
    int a = 3, b = -3;

    cout << "a : " << a << endl;
    cout << "b : " << b << endl;

    change_negative(a);
    change_negative(b);

    cout << "change negative - a : " << a << endl;
    cout << "change negative - b : " << b << endl;
    // main 에서 change_negative 함수를 호출하여 넣었던 a, b 변수는 _val 매개변수로 복사된다. 그러므로 함수 내부의 _val 변수값만 음수로 만들 뿐 a, b변수는 영향이 없다. 


    return 0;
}