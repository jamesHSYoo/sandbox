#include <iostream>
#include <math.h>

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

void cholesky_elimination(double **L, double *UV, double *KV, int ncol){
    
    int i, j;
    double sum;

    for(i = 0 ; i < ncol ; i++) UV[i] = 0.0;

    for(i = 0 ; i < ncol ; i++){
        sum = KV[i];
        for(j = 0 ; j < i ; j++) sum -= L[i][j] * UV[j];
        UV[j] = sum / L[i][i];
    }

    for(i = ncol - 1 ; i >= 0 ; i--){
        sum = UV[i];
        for(j = i + 1 ; j < ncol ; j++) sum -= L[j][i] * UV[j];
        UV[i] = sum / L[i][i];
    }
}

void cholesky_solver(double **A, double *UV, double *KV, int ncol){

    int i, j;
    double **L ; //하삼각 행렬
    L = new double*[ncol];
    for(i = 0 ; i < ncol ; i++) L[i] = new double[ncol];

    cholesky_decomposition(L, A, ncol);

    cout << "하삼각 행렬은" << endl;
    for(i = 0 ; i < ncol ; i++){
        for(j = 0 ; j < ncol ; j++){
            cout << L[i][j] <<"    ";
        }
        cout << endl;
    }

    cout << "상부삼각 행렬은" << endl;
    for(i = 0 ; i < ncol ; i++){
        for(j = 0 ; j < ncol ; j++){
            cout << L[j][i] <<"    ";
        }
        cout << endl;
    }

    cholesky_elimination(L, UV, KV, ncol);

    cout << "춀레스키분해를 이용한 연립방정식의 해는 " << endl;
    for(i = 0 ; i < ncol ; i++) cout << "x_" << i+1 << " : " << UV[i] << endl;
    
    for(i = 0 ; i < ncol ; i++) delete[] L[i];
    
    delete[] L;
}