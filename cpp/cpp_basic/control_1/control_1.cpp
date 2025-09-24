#include<iostream>

using namespace std;

int main()
{
    int i, sum;
    sum = 0;

    for(i=1; i<=10;i++)
    {
        sum+=i;
    }
    cout<<"Sum from 1 to 10 : "<< sum << endl;
    return 0;
}