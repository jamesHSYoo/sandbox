#include <cmath>
#include <chrono> // 타이머 기능을 위해 필요
#include <fstream>

#include <iostream>

using namespace std;

#include "index.h"
#include "mathlib.h"
#include "yield.h"
#include "product.h"
#include "price.h"

CPrice::CPrice(){
    m_price = 0.0;
}
CPrice::~CPrice(){

}

void CPrice::spread_option_price(CIndex &index1, CIndex &index2,
                            CYield &yield, CProduct &product){

    string option_type = product.m_option_type;
    double rho = product.m_correlation;
    double X = product.m_strike;
    double T = product.m_maturity;
    double S1 = index1.m_spot;
    double q1 = index1.m_dividend;
    double sigma1 = index1.m_vol;
    double S2 = index2.m_spot;
    double q2 = index2.m_dividend;
    double sigma2 = index2.m_vol;
    double r = yield.m_riskfree;


    int iop;
    double F, S, sigma, d1, d2;

    F = S2*exp(-q2*T)/(S2*exp(-q2*T) + X*exp(-r*T));
    sigma = sqrt(sigma1 * sigma1 + pow((sigma2*F), 2) - 2*rho * sigma1 * sigma2 * F);
    S = S1 * exp(-q1 * T)/(S2 * exp(-q2 * T) + X * exp(-r * T));
    d1 = ( log(S) * 0.5 * sigma * sigma * T )/( sigma * sqrt(T));
    d2 = d1 - sigma * sqrt(T);
    iop = -1;
    if(option_type == "call" || option_type == "Call" ) iop = 1;
    m_price = (S2 * exp(-q2 * T) + X * exp(-r * T)) * iop * (S * N(iop * d1) - N(iop * d2));
}