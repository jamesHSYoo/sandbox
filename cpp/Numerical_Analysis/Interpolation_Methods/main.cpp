#include<iostream>

#include"mathlib.h"

using namespace std;

int main(){

    int i, n_days;
    double* tenors;
    double* rates;

    n_days = 8;

    tenors = new double[n_days];
    rates = new double[n_days];

    i = 0;
    tenors[i] = 1.0;
    rates[i] = 2.542;

    tenors[++i] = 91.0;
    rates[i] = 2.827;
    
    tenors[++i] = 182.0;
    rates[i] = 2.989;

    tenors[++i] = 274.0;
    rates[i] = 3.141;
    
    tenors[++i] = 366.0;
    rates[i] = 3.275;
    
    tenors[++i] = 548.0;
    rates[i] = 3.460;
    
    tenors[++i] = 732.0;
    rates[i] = 3.615;

    tenors[++i] = 1099.0;
    rates[i] = 3.808;

    double tenor;
    double rate;

    tenor = 915.0;
    rate = cubicspline_interpolation(n_days, tenors, rates, tenor);

    cout << "zero rate 의 선형보간 결과값 : " << rate << endl;
    
    delete[] tenors;
    delete[] rates;
    return 0;

}