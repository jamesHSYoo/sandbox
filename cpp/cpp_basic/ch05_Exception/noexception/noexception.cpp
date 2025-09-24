#include<iostream>

using namespace std;

void real_noexception() noexcept // 예외를 떨어뜨리지 않음을 명시
{   
    cout << "real_noexcept" << endl;
}

void fake_noexcept() noexcept
{
    cout << "fake_noexcept" << endl;
    throw -1;
}

int main()
{
    real_noexception();
    try
    {
        fake_noexcept();
    }
    catch(int exec)
    {
        cout << "catch "<< exec << endl;
    }
    return 0;
}