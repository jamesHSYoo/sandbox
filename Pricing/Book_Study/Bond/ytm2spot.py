def get_spot_from_ytm(ytm_tenors, ytm_rates, currency):

    coupon_tenor = 0
    stndx = 0
    if currency == 'KRW':
        coupon_tenor = 2
        stndx = 2
    else:
        coupon_tenor = 4
        stndx = 1

    # 저장할 스팟커브 리스트
    spot_rate = []

    # 지급 주기(월 환산)
    ir_freq = 12 // coupon_tenor

    nterm = len(ytm_tenors)
    max_tenor = ytm_tenors[-1]
    max_n = divmod(max_tenor, ir_freq)[0]

    return None









if __name__ == '__main__':
    test_ytm_tenors = [3, 6, 12, 24, 36, 48, 60]
    test_ytm_rates = [0.00138497, 0.00122494, 0.0012993, 0.00165278, 0.0021181, 0.00292553, 0.00397573]
    test_currency = 'KRW'

    result = get_spot_from_ytm(test_ytm_tenors, test_ytm_rates, test_currency)
