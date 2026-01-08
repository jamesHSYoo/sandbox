#include<iostream>

#include<cmath>

#include "nonlinearsolver.h"
#include "mathlib.h"

using namespace std;

void levenberg_marquardt_parameter_solver(double S, double cc, int n_x, 
    double* v_x, int n_y, double* v_y, double** m_ref, int nparameter,
    double* parameter, 
    double object_func(int nparameter, double* parameter, double x, double t)){

    // 비선형 파라미터 추정
    int i, j, m, n, iter;
    double *unknown, *known, *guess, *tguess, *minguess;
    double **smatrix, **perr, **tperr;
    double error, olderror, minerror, tmperror, tolerance, h;
    double fx_value, xvalue;

    iter = 0;
    tolerance = 1.0e-15;
    h = 0.00001;

    perr = new double*[n_x];
    tperr = new double*[n_x];
    for(i = 0; i < n_x; i++){
        perr[i] = new double[n_y];
        tperr[i] = new double[n_y];
    }

    guess = new double[nparameter];
    tguess = new double[nparameter];
    minguess = new double[nparameter];
    unknown = new double[nparameter];
    known = new double[nparameter];
    smatrix = new double*[nparameter];

    for(i = 0 ; i < nparameter ; i++){
        smatrix[i] = new double[nparameter];
        guess[i] = parameter[i];
    }

    double df1, df2, faph, famh, fbph, fbmh, lambda;
    lambda = 0.0001;

    error = 0;
    for(i = 0 ; i < n_x ; i++){
        for(j = 0 ; j < n_y ; j++){
            xvalue = log(S * exp(cc * v_y[j]) / v_x[i]);
            fx_value = object_func(nparameter, guess, xvalue, v_y[j]);
            perr[i][j] = (fx_value - m_ref[i][j]);
            error += perr[i][j] * perr[i][j];
        }
    }

    olderror = error;
    iter = 0;
    tmperror = 0.0;
    minerror = 1.0e10;

}
