#include <iostream>
using namespace std;

#include "product.h"

CProduct::CProduct()
{
    m_strike = 105.0;
    m_maturity = 1.0;
    m_option_type = "call";
}
CProduct::CProduct(string option_type, double strike, double maturity, double correlation)
{
m_strike = strike;
m_maturity = maturity;
m_option_type = option_type;
m_correlation = correlation;
}
CProduct::~CProduct()
{}
void CProduct::get_strike()
{
    cout<<"행사가격 : ";
    cin>>m_strike;
}
void CProduct::get_maturity()
{
    cout <<  "잔촌만기 : ";
    cin>>m_maturity;
}
void CProduct::get_correlation()
{
    cout << "상관계수 : ";
    cin >> m_correlation;
}