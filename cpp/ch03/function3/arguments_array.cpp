#include<iostream>

using namespace std;

float average(float *_array, int _count)
{
    float sum = 0;
    for(int i = 0 ; i < _count ; i++){
        sum += *(_array + i);
    }
    return (sum / _count);
}

int main()
{
    int count = 5;
    float *score = new float[5];

    for(int i = 0 ; i < count ; i++)
    {
        *(score + i) = 90.0 + i;
    }

    int result = average(score, 5);

    cout << " Average : " << result << endl; 
}