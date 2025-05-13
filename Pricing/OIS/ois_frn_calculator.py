import datetime
import numpy as np
import math


def calculate_ois_frn(valuation_date : str, principle_amount : float, 
                    begin_dates : np.array, end_dates : np.array, settle_dates : np.array,
                    multiplier : float, spread : float, day_count_convention : int,
                    calculation_type : int, coupon_period_type : int, shift_days : int,
                    riskfree_rates : np.array, riskfree_tenors : np.array,
                    discount_rates : np.array, discount_tenors : np.array,
                    holidays : np.array, fixing_dates : np.array, fixing_rates : np.array,
                    ):
    settle_residuals = get_residuals(valuation_date, settle_dates, day_count_convention)
    

    return 0

def get_residuals(valuation_date : str, target_dates : np.array, day_cnt_conv : int):

    val_dt = datetime.datetime.strptime(valuation_date, '%Y%m%d')

    result_residuals = np.array([])
    for target_date in target_dates:
        date = datetime.datetime.strptime(target_date, '%Y%m%d')
        residual = 0
        np.append(result_residuals, get_residual_by_dcc(val_dt, date, day_cnt_conv))
    return result_residuals

def get_residual_by_dcc(start_date : datetime, end_date : datetime, dcc_type : int):

    ## TODO : 나머지 타입에 대한 코드 필요
    if dcc_type == 2: # ACT/360
        return ((end_date - start_date).days)/360 
    else :
        return 0

def get_rate_by_residuals(rates : np.array, tenors : np.array, target_tenors : np.array):

    result_rates = np.array([])
    
    for target_tenor in target_tenors:
        np.append(result_rates, get_rate_using_interpolation(rates, tenors, target_tenor))

    return result_rates

def get_rate_using_interpolation(target_rates : np.array, target_tenors : np.array, selected_tenor : np.array):
    if len(target_tenors) == 1:
        return target_rates[0]
    if target_tenors[-1] <= selected_tenor:
        return target_rates[-1]

    for i, tenor in enumerate(target_tenors):
        if tenor == selected_tenor:
            return target_rates[i]
        else:
            if tenor > selected_tenor:
                return target_rates[i-1] + (selected_tenor - target_tenors[i-1]) \
                       / (target_tenors[i] - target_tenors[i-1]) * (target_rates[i] - target_rates[i-1])


if __name__ == '__main__':

    valuation_date = '20250324'

    ## 발행정보
    principle_amount = 1

    begin_dates = np.array(['20241015', '20250115', '20250415', '20250715'])
    end_dates = np.array(['20250115', '20250415', '20250715', '20251015'])
    settle_dates = np.array(['20250115', '20250415', '20250715', '20251015'])

    multiplier = 1
    spread = 0.0091161

    day_count_convention = 2
    """ 1 : ACT/ACT , 2 : ACT/360 , 3 : ACT/365,
        4 : 30/ACT, 5 : 30/360, 6 : 30/365, 
        7 : NL/ACT, 8 : NL/360, 9 : NL/365, 
        10 : E30/ACT, 11 : E30/360, 12 : E30/365 
    """
    calculation_type = 1
    # 1 : Compounding, 2 : Average

    coupon_period_type = 1
    ## 1 : normal, 2 : Observation Shift, 3 : LookBack, 4 : LockOut
    shift_days = 0 # coupon_period_type = 1이 아닌 경우에 입력
    
    ## Market Data
    riskfree_rates = np.array([0.25, 0.5, 0.75, 1.0, 1.5, 2, 2.5, 3.0, 4.0, 5.0, 7.0, 10.0, 15.0, 20.0, 30.0])
    riskfree_tenors = np.array([0.04336696, 0.04225291,0.04109591, 0.0401059, 0.03865859, 0.03782946, 0.03741226, 0.03722419, 0.03718523, 0.03731013, 0.03774396, 0.03847396, 0.039591, 0.03983994, 0.037928])
    discount_rates = np.array([0.25, 0.5, 0.75, 1.0, 1.5, 2, 2.5, 3.0, 4.0, 5.0, 7.0, 10.0, 15.0, 20.0, 30.0])
    discount_tenors = np.array([0.04336696, 0.04225291,0.04109591, 0.0401059, 0.03865859, 0.03782946, 0.03741226, 0.03722419, 0.03718523, 0.03731013, 0.03774396, 0.03847396, 0.039591, 0.03983994, 0.037928])

    holidays = np.array(['20250118','20250119','20250120','20250125','20250126','20250201','20250202','20250208','20250209','20250215','20250216','20250217','20250222','20250223','20250301','20250302','20250308','20250309','20250315','20250316','20250322','20250323','20250329','20250330','20250405','20250406','20250412','20250413','20250419','20250420','20250426','20250427','20250503','20250504','20250510','20250511','20250517','20250518','20250524','20250525','20250526','20250531','20250601','20250607','20250608','20250614','20250615','20250619','20250621','20250622','20250628','20250629','20250704','20250705','20250706','20250712','20250713','20250719','20250720','20250726','20250727','20250802','20250803','20250809','20250810','20250816','20250817','20250823','20250824','20250830','20250831','20250901','20250906','20250907','20250913','20250914','20250920','20250921','20250927','20250928','20251004','20251005','20251011','20251012','20251013'])
    fixing_dates = np.array(['20250115','20250116','20250117','20250121','20250122','20250123','20250124','20250127','20250128','20250129','20250130','20250131','20250203','20250204','20250205','20250206','20250207','20250210','20250211','20250212','20250213','20250214','20250218','20250219','20250220','20250221','20250224','20250225','20250226','20250227','20250228','20250303','20250304','20250305','20250306','20250307','20250310','20250311','20250312','20250313','20250314','20250317','20250318','20250319','20250320','20250321','20250324'])
    fixing_rates = np.array([0.0428,0.0429,0.0429,0.0429,0.043,0.0435,0.0434,0.0434,0.0434,0.0435,0.0435,0.0438,0.0435,0.0433,0.0433,0.0436,0.0435,0.0435,0.0434,0.0432,0.0433,0.0433,0.0437,0.0435,0.0433,0.0434,0.0434,0.0433,0.0433,0.0436,0.0439,0.0439,0.0433,0.0434,0.0435,0.0434,0.0433,0.0432,0.0431,0.043,0.043,0.0432,0.0431,0.0429,0.0429,0.043,0.043])

    price = calculate_ois_frn(valuation_date, principle_amount, 
                                begin_dates, end_dates, settle_dates,
                                multiplier, spread, 
                                day_count_convention, calculation_type, 
                                coupon_period_type, shift_days,
                                riskfree_rates, riskfree_tenors,
                                discount_rates, discount_tenors,
                                holidays, fixing_dates, fixing_rates)
    print(f"FRN Price : {price}")


