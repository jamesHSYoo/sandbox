#include <iostream>

#include "mathlib.h"

using namespace std;

int main(){

    int i, ncol;
    double **A;
    double *UV;
    double *KV;

    ncol = 3;
    A = new double*[ncol];
    for(i = 0 ; i < ncol ; i++) A[i] = new double[ncol];
    UV = new double[ncol];
    KV = new double[ncol];

    A[0][0] = 4.0; A[0][1] = -4.0 ; A[0][2] = 8.0;
    A[1][0] = -4.0; A[1][1] = 5.0 ; A[1][2] = -11.0;
    A[2][0] = 8.0; A[2][1] = -11.0 ; A[2][2] = 32.0;

    KV[0] = 1.0;
    KV[1] = 1.5;
    KV[2] = 2.0;

    cholesky_solver(A, UV, KV, ncol);
    gaussian_elimination(A, KV, UV, ncol);
    cout << "가우스 소거법을 이요한 연립방정식의 해는 " << endl;

    for(i = 0 ; i < ncol ; i++) cout << "x_" << i+1 << " : " << UV[i] << endl;

    for(i = 0 ; i < ncol ; i++){
        delete[] A[i];
    }
    delete[] A;
    delete[] UV;
    delete[] KV;
}