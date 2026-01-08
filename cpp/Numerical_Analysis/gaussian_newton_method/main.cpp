#include<iostream>
#include<iomanip>
#include<math.h>

#include "mathlib.h"
#include "nonlinearsolver.h"

using namespace std;

int main(){

    int i, n_data;
    double *mx, *my;

    int n_parameter;
    double *parameter;
    
    cout << setprecision(15);

    n_data = 10;

    mx = new double[n_data];
    my = new double[n_data];

    for(i = 0; i < n_data; i++){
        mx[i] = 1.0 + 0.2 * i;
        my[i] = 1.561*mx[i] - 0.725*mx[i]*mx[i] - 0.532*exp(-0.288*mx[i]);
    }

    n_parameter = 4;
    parameter = new double[n_parameter];
    for(i = 0 ; i < n_parameter ; i++){
        parameter[i] = 1.0;
    }

    gauss_newton_parameter_solver(n_data, mx, my, n_parameter, parameter, fx_function);

    for(i = 0 ; i < n_parameter ; i++){
        cout << "p[" << i <<"] : " << parameter[i] << endl;
    }
    delete[] parameter;
    delete[] mx;
    delete[] my;
}