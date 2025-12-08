#include<iostream>
#include<math.h>

using namespace std;

double nonlinear_function(double x)
{
    return exp(0.5 * x) - 5.0;
}

double bisection_method()
{
    double xa, xb, xc, fxa, fxc;
    double error_tolerance, error;
    int iter;

    iter = 0;
    error_tolerance = 1.0e-15;
    error = 10;

    xa = -10.0;    // 해의 구간 최소값 
    xb = 10.0;    // 해의 구간 최대값 10

    while(error > error_tolerance && iter < 100)
    {
        xc = (xa + xb)/ 2.0;
        fxa = nonlinear_function(xa);
        fxc = nonlinear_function(xc);

        if(fxa * fxc < 0)       xb = xc;
        else if(fxa * fxc > 0)  xa = xc;
        else
        {
            error = 0.0;
            break;
        }
        error = fabs(xb - xa);
        iter++;
    }
    if(iter == 100)
    {
        cout << "허용 오차범위는 불만족하나, 가장 근사한 값은 " << xc << "입니다." << endl;
    }
    else
    {
        cout << "Bisection method 계산 횟수 : " << (iter) << endl;
    }

    return xc;
}