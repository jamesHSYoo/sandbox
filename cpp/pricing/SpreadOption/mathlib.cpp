#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>

#include "mathlib.h"

#define EPS 1.2e-7
#define PI 3.14159265358979323846264338327950288419716939937510582097

using namespace std;

double N(double z){

    double a1 = 0.31938153;
    double a2 = -0.356563782;
    double a3 = 1.781477937;
    double a4 = -1.821255978;
    double a5 = 1.330274429;
    double r = 0.2316419;
    double c = 1 / sqrt(2 * PI);

    if(z > 100) return 1.0;
    else if(z < -100.0) return 0.0;

    double x = fabs(z);
    double k = 1.0 / (1.0 + r * x);
    double b = c * exp((-z * z) / 2.0);
    double nv = ((((a5 * k + a4) * k + a3) * k + a2) * k + a1) * k;
    nv = 1.0 - b * nv;
    if(z < 0.0) nv = 1.0 - nv;
    return nv;
}

double normdistrand(){
    double rnd = 0;
    for(int i = 0; i < 12; i++){
        rnd += rand() / ((double) RAND_MAX);
    }    
    rnd -= 0.6;
    return rnd;
}

double normdistrand_BoxMuller(){

    double u1, u2, z1, z2;
    static int iset = 0;
    static double gset;
    if(iset == 0){
        do{
            u1 = rand() / ((double) RAND_MAX);
            u2 = rand() / ((double) RAND_MAX);
            z1 = sqrt(-2 * log(u1)) * cos(2 * PI * u2);
            z2 = sqrt(-2 * log(u1)) * sin(2 * PI * u2);
        }
        while(u1 == 0.0);
        gset = z2;
        iset = 1;
        return z1;
    }
    else{
        iset = 0;
        return gset;
    }
}

void tridiagonal_elimination(double **smat, double *known, double *unknown, int n_eqs){
    double ratio, sum;
    int i, j, k;

    for(k = 0; k <n_eqs-1; k++){
        if(smat[k][k] == 0.){
            cout << "Matrix is simngular in tridiagonal_elimination()" << endl;
            exit(0);
        }
        ratio = -smat[k+1][k] / smat[k][k];
        if(k == n_eqs - 2){ // 
            for(j = k ; j <= k+1 ; j++){
                if(smat[k][j] == 0) continue;
                smat[k+1][j] += ratio * smat[k][j];
            }
        }
        else{
            for(j = k ; j <= k + 2 ; j++){
                if(smat[k][j] == 0) continue;
                smat[k+1][j] += ratio * smat[k][j];
            }
        }
        known[k + 1] += ratio * known[k];
    }
    unknown[n_eqs - 1] = known[n_eqs - 1] / smat[n_eqs - 1][n_eqs - 1];

    for(i = n_eqs - 2 ; i >= 0 ; i--){
        sum = smat[i][i + 1] * unknown[i+1];
        unknown[i] = (known[i] - sum) / smat[i][i];
    }
}

void cholesky_decomposition(double **L, double **A, int ncol){
    // A : in, L : out, ncol : size of matrix
    int i, j, k;
    double sum;

    for(i = 0 ; i < ncol ; i++){
        for(j = 0 ; j < ncol ; j++) L[i][j] = 0.0;
    }
    L[0][0] = sqrt(A[0][0]);

    for(i = 0 ; i < ncol ; i++){
        L[i][0] = A[i][0] / L[0][0];
        for(j = 0 ; j <= i; j++){
            sum = 0.0;
            if(j != i){
                for(k = 0 ; k < j ; k++) sum+= L[i][k] * L[j][k];
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
            else{
                for(k = 0 ; k < i ; k++ ) sum += pow(L[j][k], 2);
                L[i][j] = sqrt(A[i][j] - sum);    
            }
        }
    }
}
