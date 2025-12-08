#define _CRT_SECURE_NO_DEPRECATE

void gauss_newton_parameter_solver(int nref, double *ref_x, double *ref_y, int nparameter, double *parameter, double object_func(int nparameter, double *parameter, double x));

double fx_function(int nparameter, double *parameter, double x);