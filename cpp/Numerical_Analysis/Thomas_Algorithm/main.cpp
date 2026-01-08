#include <iostream>

#include "mathlib.h"

using namespace std;

int main(){

    int i, n_eq;
    double **smatrix;
    double *known_values;
    double *unknown_values;

    n_eq = 4;
    smatrix = new double*[n_eq];
    for(i = 0 ; i < n_eq ; i++) smatrix[i] = new double[n_eq];

    known_values = new double[n_eq];
    unknown_values = new double[n_eq];

    smatrix[0][0] = 2; smatrix[0][1] = -1;
    smatrix[0][2] = 0; smatrix[0][3] = 0;

    smatrix[1][0] = -1; smatrix[1][1] = 2;
    smatrix[1][2] = -1; smatrix[1][3] = 0;

    smatrix[2][0] = 0; smatrix[2][1] = -1;
    smatrix[2][2] = 2; smatrix[2][3] = -1;

    smatrix[3][0] = 0; smatrix[3][1] = 0;
    smatrix[3][2] = -1; smatrix[3][3] = 2;

    known_values[0] = 1;
    known_values[1] = 0;
    known_values[2] = 0;
    known_values[3] = 1;

    triangonal_elimination(smatrix, known_values, unknown_values, n_eq);

    for(i = 0 ; i < n_eq; i++){
        cout << "x_" << i << " : " << unknown_values[i] << endl;
    }

    for(i = 0 ; i < n_eq ; i++){
        delete smatrix[i];
    }

    delete[] smatrix;
    delete[] known_values; 
    delete[] unknown_values;
    return 0;
}