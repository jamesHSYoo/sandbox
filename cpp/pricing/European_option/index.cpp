#include <iostream>

#include "index.h"

using namespace std;

CIndex::CIndex(){
    m_spot = 100.0;
    m_vol = 0.2;
    m_dividend = 0.03;
}
CIndex::CIndex(double spot, double vol, double dividend)
{
    m_spot = spot;
    m_vol = vol;
    m_dividend = dividend;
}

CIndex::~CIndex()
{}

void CIndex::get_spot()
{
    cout << "기초자산 가격 : ";
    cin>>m_spot;
}
void CIndex::get_dividend()
{
cout <<"배당률(%) : ";
cin>>m_dividend;
m_dividend /= 100.0;
}
void CIndex::get_vol()
    {
    cout<<"변동성(%) : ";
    cin >> m_vol;
    m_vol /= 100.0;
}