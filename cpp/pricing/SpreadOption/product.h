#pragma once

#include <string>

using std::string;

class CProduct{
public:
    double m_strike;
    double m_maturity;
    string m_option_type;
    
public:
    CProduct();
    CProduct(string option_type, double strike, double maturity);

    ~CProduct();

    void get_strike();
    void get_maturity();
};