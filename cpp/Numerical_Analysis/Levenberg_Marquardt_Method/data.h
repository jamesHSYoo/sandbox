#define _CRT_SECURE_NO_DEPRECATE

void read_market_vol(char *filename, int n_strike, double* v_strike, int n_maturity, double* v_maturity, double** m_vol);

void save_vol(char* filename, int n_strike, double* v_strike, int n_maturity, double* v_maturity, double** vol);