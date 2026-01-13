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

    do{
        for(i = 0 ; i < nparameter ; i++){
            for(j = 0 ; j < nparameter ; j++){
                smatrix[i][j] = 0.0;
            }
            known[i] = unknown[i] = 0.0;
        }

        for(i = 0 ; i < nparameter ; i++){
            for(j = 0 ; j < nparameter ; j++){
                for(m = 0 ; m < n_x ; m++){
                    for(n = 0 ; n < n_y ; n++){
                        xvalue = log(S * exp(cc * v_y[n]) / v_x[m]);
                        guess[i] += h;
                        faph = object_func(nparameter, guess, xvalue, v_y[n]);
                        guess[i] -= 2.0 * h;
                        famh = object_func(nparameter, guess, xvalue, v_y[n]);
                        guess[i] += h;

                        guess[j] += h;
                        fbph = object_func(nparameter, guess, xvalue, v_y[n]);
                        guess[j] -= 2.0 * h;
                        fbmh = object_func(nparameter, guess, xvalue, v_y[n]);
                        guess[j] += h;

                        df1 = (faph - famh) / (2.0 * h);
                        df2 = (fbph - fbmh) / (2.0 * h);
                        smatrix[i][j] += df1 * df2;
                    }
                }
            }
        }
        for(i = 0 ; i < nparameter ; i++){
            for(j = 0 ; j < nparameter ; j++){
                smatrix[i][j] = smatrix[j][i];
            }
        }

        for(i = 0 ; i < nparameter ; i++){
            smatrix[i][i] = smatrix[i][i] * (1.0 + lambda);
            for(m = 0 ; m < n_x ; m++){
                for(n = 0 ; n < n_y ; n++){
                    xvalue = log(S * exp(cc * v_y[n]) / v_x[m]);
                    guess[i] += h;
                    faph = object_func(nparameter, guess, xvalue, v_y[n]);
                    guess[i] -= 2.0 * h;
                    famh = object_func(nparameter, guess, xvalue, v_y[n]);
                    guess[i] += h;
                    
                    df1 = (faph - famh) / (2.0 * h);
                    known[i] -= df1 * perr[m][n];
                }
            }
        }

        gaussian_elimination(smatrix, known, unknown, nparameter);

        for(i = 0 ; i < nparameter ; i++){
            tguess[i] = guess[i] + unknown[i];
        }
        error = 0.0;
        for(i = 0 ; i < n_x ; i++){
            for(j = 0 ; j < n_y ; j++){
                xvalue = log(S * exp(cc * v_y[j]) / v_x[i]);
                fx_value = object_func(nparameter, tguess, xvalue, v_y[j]);
                tperr[i][j] = (fx_value - m_ref[i][j]);
                error += tperr[i][j] * tperr[i][j];
            }
        }

        if(iter != 0 && error > olderror){
            lambda *= 10.0;
        }else{
            lambda /= 10.0;
            for(i = 0 ; i < nparameter ; i++){
                guess[i] = tguess[i];
            }

            for(i = 0 ; i < n_x ; i++){
                for(j = 0 ; j < n_y ; j++){
                    perr[i][j] = tperr[i][j];
                } 
            }
            tmperror = olderror;
            olderror = error;
        }
        if(error < minerror){
            for(i = 0; i < nparameter ; i++){
                minguess[i] = guess[i];
            }
            minerror = error;
        }

        cout << iter << " 번째" << endl; 
        for(i = 0 ; i < nparameter ; i++){
            cout << "p[" << i << "] : " << guess[i] << endl; 
        }
        cout << "error : " << minerror << endl;
        iter++;
    }while(error > tolerance && fabs(tmperror - error) > tolerance && iter <1000);

    for(i = 0 ; i < nparameter ; i++){
        parameter[i] = guess[i];
    }
    cout << iter << " 번 실행 후 최적해 구함" << endl;

    for(i = 0 ; i < n_x ; i++){
        delete perr[i];
        delete tperr[i];
    }

    delete[] perr;
    delete[] tperr;
    for(i = 0 ; i < nparameter; i++){
        delete smatrix[i];
    }

}

double implied_volatility_function(int nparameter, double* parameter, double x, double t){
    int i;
    double imvol;
    double* p;
    p = new double[nparameter];
    for(i = 0 ; i < nparameter ; i++){
        p[i] = parameter[i];
    }

    imvol = p[0] + p[2] * exp(p[1] * t) + p[3]*x + p[4]*x*x + p[5]*x*x*x + p[6]*x*x*x*x;
    delete[] p;
    return imvol;
}

void implied_volatility(double S, double cc, int n_x, double* v_x, int n_y, double* v_y, double** mat, int nparameter, double* parameter){
    int i, j;
    double xvalue;
    for(i = 0 ; i < n_x ; i++){
        for(j = 0 ; j < n_y ; j++){
            xvalue = log(S * exp(cc * v_y[j]) / v_x[i]);
            mat[i][j] = implied_volatility_function(nparameter, parameter, xvalue, v_y[j]);
        }
    }
}