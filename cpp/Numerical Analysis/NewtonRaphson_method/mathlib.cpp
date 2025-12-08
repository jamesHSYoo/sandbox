#include<iostream>
#include<math.h>

using namespace std;

double nonlinear_function(double x)
{
    return exp(0.5 * x) - 5.0;
}

double newtonraphson_method()
{
    double fx, fxprime;
    double x, dx, error_tolerance, error;
    int iter;

    iter = 0;
    error_tolerance = 1.0e-15;
    error = 10;
    x = 5.0;
    dx = 0.001;

    while(error > error_tolerance && iter < 100)
    {
        fx = nonlinear_function(x);
        fxprime = (nonlinear_function(x + dx) - nonlinear_function(x - dx)) / (2.0 * dx);
        x = x - fx / fxprime;
        error = fabs(fx);
        iter++;
    }
    if(iter == 100)
    {
        cout << "허용 오차범위는 불만족하나, 가장 근사한 값은 " << x << "입니다." << endl;
    }
    else
    {
        cout << "NewtonRaphon method 계산 횟수 : " << (iter) << endl;
    }
    return x;
}