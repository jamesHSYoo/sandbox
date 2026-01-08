#include <iostream>
#include <math.h>

#include "mathlib.h"
#include "nonlinearsolver.h"

using namespace std;



void gauss_newton_parameter_solver(int nref, double *ref_x, double *ref_y, int nparameter, double *parameter, double object_func(int nparameter, double *parameter, double x))
{
    int i, j, k, iter;
    double *gauss, *unknown, *known, *perr;
    double **smatrix;
    double error, olderror, tmperror, tolerance, h;
    double fx_value;

    iter = 0;
    tolerance = 1.0e-15;
    h = 0.00001;

    perr = new double[nref];
    gauss = new double[nparameter];
    unknown = new double[nparameter];
    known = new double[nparameter];
    smatrix = new double*[nparameter];

    for(i = 0 ; i < nparameter ; i++)
    {
        smatrix[i] = new double[nparameter];
        gauss[i] = parameter[i];
    }    

    error = 0.0;
    for(i = 0 ; i < nref ; i++)
    {
        fx_value = object_func(nparameter, gauss, ref_x[i]);
        perr[i]  = fx_value - ref_y[i];
        error += perr[i] * perr[i];
    }
    olderror = error;

    double df1, df2, faph, famh, fbph, fbmh;

    iter = 0;
    tmperror = 1.0e15;

    do{
        for(i = 0; i < nparameter; i++){
            for(j = 0 ; j < nparameter ; j++){
                smatrix[i][j] = 0.0;
            }
            known[i] = unknown[i] = 0.0;
        }

        for(i = 0; i < nparameter ; i++){
            for(j = i ; j < nparameter ; j++){
                for(k = 0 ; k < nref ; k++){
                    gauss[i] += h;
                    faph = object_func(nparameter, gauss, ref_x[k]);
                    gauss[i] -= 2.0*h;
                    famh = object_func(nparameter, gauss, ref_x[k]);
                    gauss[i] += h;

                    gauss[j] += h;
                    fbph = object_func(nparameter, gauss, ref_x[k]);
                    gauss[j] -= 2.0*h;
                    fbmh = object_func(nparameter, gauss, ref_x[k]);
                    gauss[j] += h;

                    df1 = (faph - famh)/(2.0 * h);
                    df2 = (fbph - fbmh)/(2.0 * h);
                    smatrix[i][j] += df1 * df2;
                }
            }
        }

        for(i = 0 ; i < nparameter ; i++){
            for(j = 0 ; j < i ; j++){
                smatrix[i][j] = smatrix[j][i];
            }
        }

        for(i = 0; i < nparameter ; i++){
            for(k = 0 ; k < nref ; k++){
                gauss[i] += h;
                faph = object_func(nparameter, gauss, ref_x[k]);
                gauss[i] -= 2.0 * h;
                famh = object_func(nparameter, gauss, ref_x[k]);
                gauss[i] += h;
                
                df1 = (faph - famh) / (2.0 * h);
                known[i] -= df1 * perr[k];
            }    
        }

        gaussian_elimination(smatrix, known, unknown, nparameter);

        for(i = 0 ; i < nparameter ; i++){
            gauss[i] += unknown[i];
        }

        tmperror = olderror ; 
        error = 0.0;

        for(i = 0 ; i < nref ; i++){
            fx_value = object_func(nparameter, gauss, ref_x[i]);
            perr[i] = fx_value - ref_y[i];
            error += perr[i] * perr[i];
        }
        olderror = error;
        
        cout << iter << "번째" << endl;
        for(i = 0 ; i < nparameter ; i++){
            cout << "p[" << i << "] : " << gauss[i] << endl; 
        }
        iter++;
    }while(error > tolerance && fabs(tmperror - error) > tolerance && iter < 1000);

    for(i = 0 ; i < nparameter ; i++){
        parameter[i] = gauss[i];
    }

    cout << iter << "번 실행 후 최적해 구함" << endl;

    for(i = 0 ; i < nparameter ; i++){
        delete smatrix[i];
    }
    delete[] unknown;
    delete[] known;
    delete[] gauss;
    delete[] smatrix;
}

double fx_function(int nparameter, double *parameter, double x)
{
    int i;
    double *p;
    p = new double[nparameter];
    for(i = 0 ; i < nparameter ; i++){
        p[i] = parameter[i] ;
    }
    return p[0]*x + p[1]*x*x + p[2]*exp(p[3]*x);
}

