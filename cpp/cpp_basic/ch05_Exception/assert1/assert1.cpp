#include<iostream>
#include<cassert>

using namespace std;

void print_number(int* _pt_int)
{
    assert(_pt_int != NULL);
    cout << *_pt_int << endl;
}

int main()
{
    int a = 100;
    int *b = NULL;
    int *c = NULL;

    b = &a;
    print_number(b);
    print_number(c);
}
