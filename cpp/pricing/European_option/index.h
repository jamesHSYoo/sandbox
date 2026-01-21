class CIndex{
    public:
    double m_spot;
    double m_vol;
    double m_dividend;

    public:
    CIndex();
    CIndex(double spot, double vol, double dividend);
    ~CIndex();

    void get_spot();
    void get_vol();
    void get_dividend();
};