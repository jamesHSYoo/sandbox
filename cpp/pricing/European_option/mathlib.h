#define _CRT_SECURE_NO_DEPRECATE

double N(double z);

double normdistrand();

double inverse_normal_cumulative_distribution_function(double p); 

double normdistrand_BoxMuller();

void normal_distribution_goodness_fit_test(unsigned long nrand, double* randnum);

void triangonal_elimination(double **smat, double *known, double *unknown, int n_eqs);