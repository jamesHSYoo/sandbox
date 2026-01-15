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

void set_system_matrix(int n_data, double** smatrix, double* known, double* xdata, double* ydata){
    int i, j;
    double* hi;
    hi = new double[n_data - 1];
    for(i = 0 ; i < n_data - 2 ; i++){
        for(j = 0 ; j < n_data - 2 ; j++){
            smatrix[i][j] = 0.0;
        }
        hi[i] = xdata[i + 1] - xdata[i];
    }
    hi[n_data - 2] = xdata[n_data - 1] - xdata[n_data - 2];
    smatrix[0][0] = 2 * (hi[0] + hi[1]);
    smatrix[0][1] = hi[1];
    known[0] = 3 * ((ydata[2] - ydata[1]) / hi[1] - (ydata[1] - ydata[0]) / hi[0]);

    for(i = 1 ; i < n_data - 3 ; i++){
        smatrix[i][i-1] = hi[i];
        smatrix[i][i] = 2 * (hi[i] + hi[i + 1]);
        smatrix[i][i + 1] = hi[i + 1];
        known[i] = 3 *((ydata[i + 2] - ydata[i + 1])/hi[i + 1] - (ydata[i + 1] - ydata[i]) / hi[i]);
    }

    smatrix[n_data - 3][n_data - 4] = hi[n_data - 3];
    smatrix[n_data - 3][n_data - 3] = 2 *(hi[n_data - 3] + hi[n_data - 2]);
    known[n_data - 3] = 3 * ((ydata[n_data - 1] - ydata[n_data - 2]) / hi[n_data - 2] - (ydata[n_data - 2] - ydata[n_data - 3]) / hi[n_data - 3]);

    delete[] hi;
}

double tridiagonal_elimination(double** Smat, double* known, double* unknown, int n_eqs){

    double ratio, sum;

    int i, j, k;

    for(k = 0 ; k < n_eqs - 1 ; k++){
        if(Smat[k][k] == 0.0){
            cout << "Matrix is singular in tridiagonal_elimination()" << endl;
            exit(0);
        }
        ratio = - Smat[k + 1][k] / Smat[k][k];
        if(k == n_eqs - 2){
            for(j = k ; j <= k + 1; j++){
                if(Smat[k][j] == 0.0) continue;
            }
            Smat[k + 1][j] += ratio * Smat[k][j];
        }
        else{
            for(j = k ; j <= k + 2 ; j++){
                if(Smat[k][j] == 0.0) {
                    continue;
                }
                Smat[k + 1][j] += ratio * Smat[k][j];
            }
        }
        known[k + 1] += (ratio * known[k]);
    }
    unknown[n_eqs - 1] = known[n_eqs - 1] / Smat[n_eqs - 1][n_eqs - 1];

    for(i = n_eqs - 2 ; i >= 0 ; i--){
        sum = Smat[i][i + 1] * unknown[i + 1];
        unknown[i] = (known[i] - sum)/Smat[i][i];
    }
}

double cubicspline_interpolation(int n_data, double* xdata, double *ydata, int x){
    int i, n_eq;     
    double** smatrix; // 행렬 선언
    double* known_value; // 기지값
    double* unknown_value; // 미지값

    n_eq = n_data - 2;
    smatrix = new double*[n_eq];
    for(i = 0 ; i < n_eq ; i++){
        smatrix[i] = new double[n_eq];
    }
    known_value = new double[n_eq];
    unknown_value = new double[n_eq];

    set_system_matrix(n_data, smatrix, known_value, xdata, ydata);
    tridiagonal_elimination(smatrix, known_value, unknown_value, n_eq);

    double* ci;
    ci = new double[n_data];
    for(i = 0 ; i < n_eq ; i++){
        ci[i + 1] = unknown_value[i];
    }
    ci[0] = 0.0;           // 자연 경계조건
    ci[n_data - 1] = 0.0;  // 자연 경계조건

    double a, b, d, y, hi, xp;

    if(xdata[0] > x){
        hi = xdata[1] - xdata[0];
        xp = x - xdata[0];
        a = ydata[0];
        b = (ydata[1] - ydata[0]) / hi - hi * (2 * ci[0] + ci[1]) / 3;
        d = (ci[1] - ci[0]) / (3 * hi);
        y = a + b * xp + ci[0] * xp * xp + d * xp * xp * xp;
    }
    else if(xdata[n_data - 1] < x){
        hi = xdata[n_data - 1] - xdata[n_data - 2];
        xp = x - xdata[n_data - 2];
        a = ydata[n_data - 2];
        b = (ydata[n_data - 1] - ydata[n_data - 2]) / hi - hi * (2 * ci[n_data - 2] + ci[n_data - 1]) / 3;
        d = (ci[n_data - 1] - ci[n_data - 2]) / (3 * hi);
        y = a + b * xp + ci[n_data - 2] * xp * xp + d * xp * xp * xp;
    }
    else{
        for(i = 1 ; i < n_data ; i++){
            if(xdata[i] > x){
                hi = xdata[i] - xdata[i - 1];
                xp = x - xdata[i - 1];
                a = ydata[i - 1];
                b = (ydata[i] - ydata[i - 1]) / hi - hi * (2 * ci[i - 1] + ci[i]) / 3;
                d = (ci[i] - ci[i - 1]) / (3 * hi);
                y = a + b * xp + ci[i - 1] * xp * xp + d * xp * xp * xp;
            }
            else{
                continue;
            }
        }
    }
    for(i = 0 ; i < n_eq; i++){
        delete[] smatrix[i];
    }
    delete[] smatrix;
    delete[] known_value;
    delete[] unknown_value;

    return y;
}
