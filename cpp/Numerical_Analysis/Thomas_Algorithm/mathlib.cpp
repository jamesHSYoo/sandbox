#include <iostream>

#include "mathlib.h"

using namespace std;

void triangonal_elimination(double **smat, double *known, double *unknown, int n_eqs){
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