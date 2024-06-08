#include<iostream>

using namespace std;

int main()
{
    int int_value = 123;

    int *int_pt_value  = &int_value;
    int **int_pt_pt_value = &int_pt_value;
    int ***int_pt_pt_pt_value = &int_pt_pt_value;

    cout << "----Value display----" << endl;

    cout << "*int_pt_value = " << *int_pt_value << endl;
    cout << "*int_pt_pt_value = " << *int_pt_pt_value << endl;
    cout << "*int_pt_pt_pt_value = " << *int_pt_pt_pt_value << endl;

    cout << "---------------------" << endl;

    cout << "----pointer display----" << endl;

    cout << "*int_pt_value = " << int_pt_value << endl;
    cout << "*int_pt_pt_value = " << int_pt_pt_value << endl;
    cout << "*int_pt_pt_pt_value = " << int_pt_pt_pt_value << endl;

    cout << "---------------------" << endl;

    return 0;
}