#define _CRT_SECURE_NO_DEPRECATE

void levenberg_marquardt_parameter_solver(double S, double cc, int n_x, 
    double* v_x, int n_y, double* v_y, double** m_ref, int nparameter,
    double* parameter, 
    double object_func(int nparameter, double* parameter, double x, double t));

double implied_volatility_function(int nparameter, double* parameter, double x, double t);

void implied_volatility(double S, double cc, int n_x, double* v_x, int n_y, double* v_y, double** mat, int nparameter, double* parameter);