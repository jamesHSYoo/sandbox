#include<iostream>
using namespace std;

int main()
{   
    try
    {
        int input;
        cout << "정수 하나를 입력해주세요 : ";
        cin >> input;
    
        if(input > 0)
        {
            cout << "throw 1" << endl;
            throw 1;
            cout << "after throw 1" << endl;
        }        
        
        if(input < 0)
        {
            cout << "throw -1.0f" << endl;
            throw -1.0f;
            cout << "after throw -1.0f" << endl;
        }        

        if(input == 0)
        {
            cout << "throw Z" << endl;
            throw "Z";
            cout << "after throw Z" << endl;
        }        
    }
    catch(int a)
    {
        cout << "catch " << a << endl;
    }
    catch(float b)
    {
        cout << "catch " << b << endl;
    }
    catch(char c)
    {
        cout << "catch " << c << endl;
    }

    return 0;
}