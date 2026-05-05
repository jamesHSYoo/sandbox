#include <cmath>
#include <time.h>
#include <fstream>

#include <iostream>
using namespace std;

#include "index.h"
#include "yield.h"
#include "product.h"
#include "price.h"
#include "mathlib.h"

CPrice::CPrice()
{
    m_price = 0.0;
}

CPrice::~CPrice()
{}

void CPrice::black_scholes_option_price(CIndex &index, CYield &yield, CProduct &product){
    string option_type  = product.m_option_type;
    double S = index.m_spot;
    double X = product.m_strike;

    double r = yield.m_riskfree;
    double q = index.m_dividend;
    double sigma = index.m_vol;
    double T = product.m_maturity;

    int iop;
    double d1, d2;

    if(option_type == "Call" || option_type == "call" ) iop = 1;
    d1 = ( log(S/X) + (r -q + (sigma*sigma)/2)*T )/(sigma*sqrt(T));
    d2 = d1 - sigma*sqrt(T);
    // Black-Sholes 옵션가격 결정식
    m_price = iop*( S*exp(-q*T)*N(iop*d1) - X*exp(-r*T)*N(iop*d2) );
}

void CPrice::simulation_european_option_price(CIndex &index, CYield &yield, CProduct &product, int n_sim)
{
    string optiontype = product.m_option_type;
    double S= index.m_spot;
    double X= product.m_strike;
    double r = yield.m_riskfree;
    double q= index.m_dividend;
    double sigma= index.m_vol;
    double T= product.m_maturity;

    int i, iop;
    double St, price, mudt, ssqrtdt;

    long idum = clock();
    price = 0.0;
    mudt = (r-q-0.5*sigma*sigma)*T;
    ssqrtdt = sigma*sqrt(T);

    iop = -1;
    if(optiontype == "Call" || optiontype == "call" ) iop = 1;
    srand((unsigned) time(NULL)); // Random Seed 초기화
    for(i=0; i<n_sim; i++){
        St = S * exp(mudt + ssqrtdt*normdistrand_BoxMuller()); // 주가생성
        price+= max(iop*(St-X), 0.0); // 만기 Payoff
    }
    m_price = (price/n_sim)*exp(-r*T); // 만기 Payoff의 평균을 현가
}

void CPrice::binomial_tree_european_option_price(CIndex &index, CYield &yield, CProduct &product, int n_step)
{
    string optiontype= product.m_option_type;
    double S= index.m_spot;
    double X= product.m_strike;

    double r = yield.m_riskfree;
    double q = index.m_dividend;
    double sigma = index.m_vol;
    double T = product.m_maturity;
    int i, j, iop;
    double up, down, dfactor, Pu, Pd, dt;
    dt = T/n_step;
    up = exp(sigma*sqrt(dt));
    down = 1.0/up;
    Pu = (exp((r-q)*dt)-down)/(up-down); // up 확률
    Pd = 1.0 - Pu; // down 확률
    double *Sp, *CV;
    Sp = new double[n_step+1];
    CV = new double[n_step+1];
    // Tree 주가 생성
    Sp[0] = S*pow(up, n_step);
    for(i=1; i<=n_step; i++) Sp[i] = Sp[i-1]*down*down;
    iop = -1;
    if(optiontype == "Call" || optiontype == "call" ) iop = 1;
    // 만기시점 옵션 Payoff
    for(i=0; i<=n_step; i++) CV[i] = max(iop*(Sp[i]-X), 0.0);
    dfactor = exp(-r*dt);
    // Tree의 만기에서부터 Backward Induction 실행하여 현재가치 계산
    for(i=n_step-1; i>=0; i--){
    for(j=0; j<=i; j++) CV[j] = (Pu*CV[j] + Pd*CV[j+1])*dfactor;
    }
    m_price = CV[0]; // 옵션의 현재가치
    delete[] Sp;
    delete[] CV;
}


void CPrice::lognormal_binomial_tree_european_option_price(CIndex &index,CYield &yield, CProduct &product, int n_step)
{
    string optiontype= product.m_option_type;
    double S= index.m_spot;
    double X= product.m_strike;
    double r = yield.m_riskfree;
    double q = index.m_dividend;
    double sigma= index.m_vol;
    double T= product.m_maturity;
    int i, j, iop;

    double dx, nu, dfactor, Pu, Pd, dt;

    dt = T/n_step;
    nu = r - q - 0.5*sigma*sigma;
    dx = sqrt(sigma*sigma*dt + nu*nu*dt*dt);

    Pu = 0.5+0.5*nu*dt/dx; // up 확률
    Pd = 1.0 - Pu; // down 확률

    double *Sp, *CV;
    Sp = new double[n_step+1];
    CV = new double[n_step+1];
    // Tree 주가 생성
    for(i=0; i<=n_step; i++) Sp[i] = S*exp((n_step-2*i)*dx); // Tree 주가 생성
    iop = -1;
    if(optiontype == "Call" || optiontype == "call" ) iop = 1;
    // 만기시점 옵션 Payoff
    for(i=0; i<=n_step; i++) CV[i] = max(iop*(Sp[i]-X), 0.0);
    dfactor = exp(-r*dt);
    //Tree 의 만기에서부터 Backward Induction 실행하여 현재가치 계산
    for(i=n_step-1; i>=0; i--){
    for(j=0; j<=i; j++) CV[j] = (Pu*CV[j] + Pd*CV[j+1])*dfactor;
    }
    m_price = CV[0]; // 옵션의 현재가치
    delete[] Sp;
    delete[] CV;
}

void CPrice::trinomial_tree_european_option_price(CIndex &index, CYield &yield,
CProduct &product, int n_step)
{
    string optiontype = product.m_option_type;
    double S = index.m_spot;
    double X = product.m_strike;
    double r = yield.m_riskfree;
    double q = index.m_dividend;
    double sigma = index.m_vol;
    double T = product.m_maturity;

    int i, j, iop, nstep;
    double dx, nu, dfactor, Pu, Pm, Pd, dt;

    dt = T/n_step;
    dx = sigma*sqrt(3.0*dt);
    nu = r - q - 0.5*sigma*sigma;

    Pu = 0.5*( (sigma*sigma*dt+nu*nu*dt*dt)/(dx*dx) + nu*dt/dx ); // up 확률
    Pd = 0.5*( (sigma*sigma*dt+nu*nu*dt*dt)/(dx*dx) - nu*dt/dx ); // down 확률
    Pm = 1 - Pu - Pd; // middle 확률
    double *Sp, *CV;
    nstep = 2* n_step + 1;
    Sp = new double[nstep];
    CV = new double[nstep];

    for(i=0; i<nstep; i++) Sp[i] = S*exp((n_step-i)*dx); // Tree 주가 생성
    iop = -1;
    if(optiontype == "Call" || optiontype == "call" ) iop = 1;
    for(i=0; i<nstep; i++) CV[i] = max(iop*(Sp[i]-X), 0.0); // 만기 Payoff
    dfactor = exp(-r*dt);
    // Tree의 만기에서부터 Backward Induction 실행하여 현재가치 계산
    for(i=n_step-1; i>=0; i--){
        for(j=0; j<2*i+1; j++)
            CV[j] = (Pu*CV[j] + Pm*CV[j+1] + Pd*CV[j+2])*dfactor;
    }
    m_price = CV[0]; // 옵션의 현재가치
    delete[] Sp;
    delete[] CV;
}

void CPrice::implicit_fdm_european_option_price(CIndex &index, CYield &yield, CProduct &product, int n_step, int n_spot)
{
    string optiontype = product.m_option_type;
    double S= index.m_spot;
    double X= product.m_strike;
    double r = yield.m_riskfree;
    double q= index.m_dividend;
    double sigma= index.m_vol;
    double T= product.m_maturity;
    int i, j, t, iop;
    if((n_spot%2)==0) n_spot = n_spot+1;
    double *Sp = new double[n_spot];
    double *CV = new double[n_spot];
    double dt, dx, edx;
    dt= T/n_step;
    dx= sigma*sqrt(3.0*dt);
    edx= exp(dx);
    Sp[0]= S*exp((n_spot-1)/2 * dx);
    for(i=1; i<n_spot; i++) Sp[i] = Sp[i-1]/edx;
    Sp[(n_spot-1)/2] = S;

    iop = -1;
    if(optiontype == "Call" || optiontype == "call" ) iop = 1;
    double Pu, Pm, Pd, nu;
    nu = r - q - 0.5*sigma*sigma;
    Pu = -0.5*dt*(sigma*sigma/(dx*dx) + nu/dx);
    Pm = 1.0 + dt*(sigma*sigma/(dx*dx) + r);
    Pd = -0.5*dt*(sigma*sigma/(dx*dx) - nu/dx);
    double **smatrix, **tmp, *known_value, *unknown_value;
    smatrix = new double*[n_spot-2]; // row create
    tmp = new double*[n_spot-2]; // row create
    known_value = new double[n_spot-2];
    unknown_value = new double[n_spot-2];
    for(i=0; i<n_spot-2; i++){
        smatrix[i] = new double[n_spot-2]; // column create
        tmp[i] = new double[n_spot-2]; // column create
    } 
    
    for(i=0; i<n_spot-2; i++){
        for(j=0; j<n_spot-2; j++)smatrix[i][j] = 0.0;
    }

    double bu, bd;
    if(iop==1){// call 옵션
    bu = Sp[0] - Sp[1]; // S가 충분히 크면 Delta = 1 이므로
    bd = 0.0; // S가 충분히 작으면 Delta = 0
    }
    else{// put 옵션
    bu = 0.0; // S가 충분히 크면 Delta = 0
    bd = -(Sp[n_spot-2] - Sp[n_spot-1]); // S가 충분히 작으면 Delta = -1
    }
    // 0~n_spot-3 는 n_spot-2

    smatrix[0][0]= Pm;
    smatrix[0][1] = Pd;
    for(i=1; i<n_spot-3; i++){
    smatrix[i][i-1] = Pu;
    smatrix[i][i] = Pm;
    smatrix[i][i+1] = Pd;
    }
    smatrix[n_spot-3][n_spot-4] = Pu;
    smatrix[n_spot-3][n_spot-3] = Pm;
    
    // 만기시점에서의 경계조건(Terminal Boundary Condition) 부여
    for(i=0; i<n_spot; i++) CV[i] = max(iop*(Sp[i]-X), 0.0);
    // 만기에서부터 Backward Induction 실행하여 현재가치 계산
    for(t=n_step-1; t>=0; t--){
        for(i=0; i<n_spot-2; i++){
            for(i=0; j<n_spot-2; j++) tmp[i][j] = smatrix[i][j];
            known_value[i] = CV[i+1];
        }
        CV[0]= bu; // 경계조건적용
        CV[n_spot-1] = bd; // 경계조건적용
        known_value[0] -= Pu*CV[0];
        known_value[n_spot-3] -= Pd*CV[n_spot-1];
        //t-1 시점 미지값 계산
        tridiagonal_elimination(tmp, known_value, unknown_value, n_spot-2);
        for(i=0; i<n_spot-2; i++) CV[i+1] = unknown_value[i];
    }
    m_price = CV[(n_spot-1)/2];
    delete[] Sp;
    delete[] CV;
    for(i=0; i<n_spot-2; i++) 
    {
        delete[] smatrix[i];
        delete[] tmp[i];
    }
        delete[] smatrix;
        delete[]  tmp;
        delete[]  known_value;
        delete[]  unknown_value;
}