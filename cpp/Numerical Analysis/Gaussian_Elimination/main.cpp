#include <iostream>

#include "mathlib.h"

using namespace std;

int main(){

    int i, n_eq;

    double **smatrix;      // 행렬
    double *known_value;   
    double *unknown_value;

    n_eq = 4;
    smatrix = new double*[n_eq];
    for(i = 0 ; i < n_eq ; i++){
        smatrix[i] = new double[n_eq];
    }
    known_value = new double[n_eq];
    unknown_value = new double[n_eq];

    smatrix[0][0] = 1; smatrix[0][1] = 1; smatrix[0][2] = 0; smatrix[0][3] = 3;
    smatrix[1][0] = 2; smatrix[1][1] = 1; smatrix[1][2] = -1; smatrix[1][3] = 1;
    smatrix[2][0] = 3; smatrix[2][1] = -1; smatrix[2][2] = -1; smatrix[2][3] = 2;
    smatrix[3][0] = -1; smatrix[3][1] = 2; smatrix[3][2] = 3; smatrix[3][3] = -1;

    known_value[0] = 4;
    known_value[1] = 1;
    known_value[2] = -3;
    known_value[3] = 4;

    gaussian_elimination(smatrix, known_value, unknown_value, n_eq);
    for(i = 0 ; i < n_eq ; i++){
        cout << "x_" << i+1 << " : " << unknown_value[i] << endl;
    }
    delete[] smatrix; 
    delete[] known_value;
    delete[] unknown_value;
}
