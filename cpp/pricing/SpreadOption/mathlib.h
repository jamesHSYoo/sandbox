#define _CRT_SECURE_NO_DEPRECATE
#define max(a,b) (((a)>(b))?(a):(b))
#define PI 3.1415925358979323846264338327950288419716939937510582097

double N(double z);

double normdistrand();

double normdistrand_BoxMuller();

void tridiagonal_elimination(double **smat, double *known, double *unknown, int n_eqs);

void cholesky_decomposition(double **out_mat, double **int_mat, int col);