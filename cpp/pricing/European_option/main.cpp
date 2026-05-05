#include <iostream>
#include "index.h"
#include "mathlib.h"
#include "yield.h"
#include "product.h"
#include "price.h"

using namespace std;

int main(){

    double S, X, r, q, sigma, T;
    int n_step, n_spot;
    unsigned long n_sim;

    S = 100.0;
    X = 110.0;
    r = 0.05;
    q = 0.01;
    sigma = 0.3;
    T = 1.0;

    n_step = 200;
    n_sim = 30000;
    n_spot = 400;

    CIndex index(S, sigma, q);
    CYield yield(r);
    CProduct eoption("Call", X, T);
    CPrice price;

    price.black_scholes_option_price(index, yield, eoption);
    cout<<"해석해에 의한 옵션가격: "<<price.m_price<<endl;
    price.simulation_european_option_price(index, yield, eoption, n_sim);
    cout<<"시뮬레이션에 의한 옵션:4격: "<<price.m_price<<endl;
    price.binomial_tree_european_option_price(index, yield, eoption, n_step);
    cout<<"Binomial Tree에 의한 옵션가격: "<<price.m_price<<endl;
    price.lognormal_binomial_tree_european_option_price(index, yield, eoption, n_step),
    cout<<"로그정규분포 적용 Binomial Tree에 의한 옵션가격: "<<price.m_price<<endl;
    price.trinomial_tree_european_option_price(index, yield, eoption, n_step);
    cout<<"Trinomial Tree에 의한 옵션가격: "<<price.m_price<<endl;
    price.implicit_fdm_european_option_price(index, yield, eoption, n_step, n_spot);
    cout<<"Implicit FDM에 의한 옵션가격: "<<price.m_price<<endl;
}