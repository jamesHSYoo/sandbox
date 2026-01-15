#define _CRT_SECURE_NO_DEPRECATE

double linear_interpolation(int n_data, double* tenors, double* rates, int x);

void set_system_matrix(int n_data, double** smatrix, double* known, double* xdata, double* ydata);

double tridiagonal_elimination(double** Smat, double* known, double* unknown, int n_eqs);

double cubicspline_interpolation(int n_data, double* xdata, double *ydata, int x);