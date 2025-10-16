#define _CRT_SECURE_NO_DEPRECATE

void gaussian_elimination(double **smatrix, double *known, double *unknow, int n_eqns);
void cholesky_decomposition(double **L, double **A, int ncol);
void cholesky_elimination(double **L, double *UV, double *KV, int ncol);
void cholesky_solver(double **A, double *UV, double *KV, int ncol);