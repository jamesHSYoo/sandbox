class CIndex;
class CYield;
class CProduct;

class CPrice{
public: 
    double m_price;

public:
    CPrice();
    ~CPrice();
    void spread_option_price(CIndex &index1, CIndex &index2, CYield &yield, 
                            CProduct &product);
    void simulation_spread_option_price(CIndex index1, CIndex index2,
                                        CYield &yield, CProduct &product, int n_sim);
    void binomial_tree_spread_option_price(CIndex &index1, CIndex &index2, 
                                        CYield &yield, CProduct &product, int n_step);
    void trinomial_tree_spread_option_price(CIndex &indexl, CIndex &index2,
        CYield &yield, CProduct &product, int n_step);
    void imlicit_fdm_spread_option_price(CIndex &index1, CIndex &index2,
        CYield &yield, CProduct &product, int rcstep, int n_spot);
};