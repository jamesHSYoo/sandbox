#include<iostream>
#include<iomanip>

#include "mathlib.h"

using namespace std;

int main(){
    double solution;
    cout << setprecision(30);

    solution = bisection_method();

    cout << "bisection method 로 찾은 해 : " << solution << endl;
}