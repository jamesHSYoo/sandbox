#include<iostream>
#include<cmath>

#include "mathlib.h"

using namespace std;

#define EPSILON 1e-10

double linear_interpolation(int n_data, double* tenors, double* rates, int x){
    int i;
    double y;
    if((tenors[0] > x) || (abs(tenors[n_data-1] - x) < EPSILON)){
        return rates[0];
    }
    else if((tenors[n_data-1] < x) || (abs(tenors[n_data-1] - x) < EPSILON)){
        return rates[n_data-1];
    }

    for(i = 0 ; i < n_data ; i++){
        if(tenors[i] > x){
            y = rates[i-1] + (rates[i] - rates[i-1])/(tenors[i] - tenors[i-1]) * (x - tenors[i-1]);
            break;
        }
        else{
            continue;
        }
    }
    return y;
}