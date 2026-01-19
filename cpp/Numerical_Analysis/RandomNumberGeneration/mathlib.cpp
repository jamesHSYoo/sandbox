#include <iostream>

#include "mathlib.h"

#define EPS 1.2e-7
#define PI 3.14159265358979323846264338327950288419716939937510582097

using namespace std;

double normdistrand(){
    double rnd = 0;
    for(int i = 0; i < 12; i++){
        rnd += rand() / ((double) RAND_MAX);
    }    
    rnd -= 0.6;
    return rnd;
}

void normal_distribution_goodness_fit_test(unsigned long nrand, double* randnum){
    unsigned long i;
    double mean = 0;
    double stddev = 0.0;

    for(i = 0 ; i < nrand; i++){
        mean += randnum[i];
    }
    mean = mean / nrand;

    for(i = 0; i < nrand ; i++){
        stddev += pow((randnum[i] - mean), 2.0);
    }
    stddev = stddev / (nrand - 1);
    stddev = sqrt(stddev);
    cout << "평균 : " << mean << endl;
    cout << "표준 편차 : " << stddev << endl;
       
    double mu3 = 0;
    double mu4 = 0; 
    double skewness, kurtosis;
    
    for(i = 0 ; i < nrand ; i++){
        mu3 += pow((randnum[i] - mean), 3.0);
        mu4 += pow((randnum[i] - mean), 4.0);
    }
    skewness = (mu3 / nrand) / (pow(stddev, 3.0));
    kurtosis = (mu4 / nrand) / (pow(stddev, 4.0));

    cout << "왜도 : " << skewness << endl;
    cout << "첨도 : " << kurtosis << endl;
    
    double jarque_bera = nrand * (skewness * skewness + pow( (kurtosis - 3.0), 2.0) / 4.0) / 6.0;

    cout << "Jarque-Bera Test : " << jarque_bera << endl;
}

double inverse_normal_cumulative_distribution_function(double p){
    static const double a[] = { 
        -3.969683028665376e+01, 2.209460984245205e+02,
        -2.759285104469687e+02, 1.383577518672690e+02,
        -3.066479806614716e+01, 2.506628277459239e+00 
    };
    
    static const double b[] = {
        -5.447609879822406e+01, 1.615858368580409e+02,
        -1.556989798598866e+02, 6.680131188771972e+01,
        -1.328068155288572e+01
    };

    static const double c[] = {
        -7.784894002430293e-03, -3.223964580411365e-01,
        -2.400758277161838e+00, -2.549732539343734e+00,
         4.374664141464968e+00,  2.938163982698783e+00
    };

    static const double d[] = {
        7.784695709041462e-03, 3.224671290700398e-01,
        2.445134137142996e+00, 3.754408661907416e+00 
    };

    static const double LOW = 0.02425;
    static const double HIGH = 0.97575;

    double q, r;
    errno = 0;

    if(p < LOW){
        if(p < EPS){
            p = EPS;
        }
        q = sqrt(-2 * log(p));
        return (((((c[0] * q + c[1]) * q + c[2]) * q + c[3]) * q + c[4]) * q + c[5]) / ((((d[0] * q + d[1]) * q + d[2]) * q + d[3]) * q + 1);
    }
    else if(p > HIGH){
        if(p > 1.0 - EPS){
            p = 1.0 - EPS;
        }
        q = sqrt(-2 * log(1 - p));
        return -(((((c[0] * q + c[1]) * q + c[2]) * q + c[3]) * q + c[4]) * q + c[5]) / ((((d[0] * q + d[1]) * q + d[2]) * q + d[3]) * q + 1);
    }
    else{
        q = p - 0.5;
        r = q * q;
        return (((((a[0] * r + a[1]) * r + a[2]) * r + a[3]) * r + a[4]) * r + a[5]) * q / (((((b[0] * r + b[1]) * r + b[2]) * r + b[3]) * r + b[4]) * r + 1);
    }
}

double normdistrand_BoxMuller(){

    double u1, u2, z1, z2;
    static int iset = 0;
    static double gset;
    if(iset == 0){
        do{
            u1 = rand() / ((double) RAND_MAX);
            u2 = rand() / ((double) RAND_MAX);
            z1 = sqrt(-2 * log(u1)) * cos(2 * PI * u2);
            z2 = sqrt(-2 * log(u1)) * sin(2 * PI * u2);
        }
        while(u1 == 0.0);
        gset = z2;
        iset = 1;
        return z1;
    }
    else{
        iset = 0;
        return gset;
    }
}