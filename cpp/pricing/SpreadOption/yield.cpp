#include <iostream>
using namespace std;
#include "yield.h"
CYield::CYield()
{
m_riskfree = 0.05;
}
CYield::CYield(double riskfree)
{
    m_riskfree = riskfree;
}
CYield::~CYield(){

}
void CYield::get_riskfree()
{
    cout << "무위험이자율(%) : ";
    cin>> m_riskfree;
    m_riskfree /= 100.0;
}