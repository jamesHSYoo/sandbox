#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

#include "data.h"
 
int main(){

    // 비선형 파라미터 추정
    int i ; 
    int n_maturity, n_strike;   // 행사가격 수량, 잔존만기 수량
    double riskfreerate, dividend, S, carrycost;  // 무위험금리, 배당률, 기초자산, carry cost

    double* v_strike;    // 행사가격
    double* v_maturity;  // 잔존만기
    double** m_vol;      // market vol

    int n_parameter;    // 미지 파라미터
    double* parameter;  // 파라미터

    // display points 
    cout << setprecision(30);

    n_strike = 5;
    n_maturity = 6;
    
    v_strike = new double[n_strike];
    v_maturity = new double[n_maturity];
    m_vol = new double*[n_strike];
    for(i = 0 ; i < n_strike ; i++){
        m_vol[i] = new double[n_maturity];
    }

    char* filename = (char *)"marketvol.txt";

    read_market_vol(filename, n_strike, v_strike, n_maturity, v_maturity, m_vol);

    return 0;
}