#include <iostream>

#include "mathlib.h"

using namespace std;

void gaussian_elimination(double **smatrix, double *known, double *unknown, int n_eqns){

    double ratio, sum, maxs, tmp;

    int i, j, k, maxi;

    for(k = 0 ; k < n_eqns - 1 ; k++){

        maxs = fabs(smatrix[k][k]);
        maxi = k;
        for(i = k+1 ; i < n_eqns ; i++){
            if(maxs < fabs(smatrix[i][k])){
                maxi = i;
            }
        }
        if(maxi != k){
            for(i = 0 ; i < n_eqns ; i++){
                tmp = smatrix[k][i];
                smatrix[k][i] = smatrix[maxi][i];
                smatrix[maxi][i] = tmp;
            }
            tmp = known[k];
            known[k] = known[maxi];
            known[maxi] = tmp;
        }
        for(i = k + 1 ; i < n_eqns ; i++){
            if(smatrix[i][k] == 0.) continue;
            ratio = -smatrix[i][k] / smatrix[k][k];
            for(j = k+1; j < n_eqns ; j++){
                if(smatrix[k][j] == 0.) continue;
                smatrix[i][j] += ratio * smatrix[k][j];
            }
            known[i] += ratio * known[k];
        }
    }

    unknown[n_eqns-1] = known[n_eqns - 1]/smatrix[n_eqns-1][n_eqns-1];
    for(i = n_eqns-2 ; i >= 0; i--){
        sum = 0;
        for(j = i + 1 ; j < n_eqns ; j++){
            sum += smatrix[i][j] * unknown[j];
        }
        unknown[i] = (known[i] - sum) / smatrix[i][i]; 
    }
}

void cholesky_elimination(double **L, double *UV, double *KV, int ncol){
    // A : in, L : out, ncol : size of matrix
    int i, j, k;
    double sum;

    for(i = 0 ; i < ncol ; i++){
        for(j = 0 ; j < ncol ; j++) L[i][j] = 0.0;
    }





}
