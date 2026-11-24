#pragma once

#include <string>

using std::string;

class CProduct{
public:
    double m_strike;
    double m_maturity;
    double m_correlation;
    string m_option_type;
    
public:
    CProduct();
    CProduct(string option_type, double strike, double maturity, double correlation);

    ~CProduct();

    void get_strike();
    void get_maturity();
    void get_correlation();
};