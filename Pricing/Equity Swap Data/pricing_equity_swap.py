import datetime
import math
import numpy as np

np.random.seed(7)
# 사용 할 함수 정의

# 보간법을 이용하여 지정된  tenor 사이의 teminate_time 의 이자율 산출
def get_ir_interpolation(target_tenors, target_rates, selected_tenor):
    try:
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
    except:
        print(f"exception occur at tenor {selected_tenor}")
        
# 두 날짜 차이의 연환산값 산출
def get_year_diff_two_dates(start_date, end_date):
    start = datetime.datetime.strptime(start_date, "%Y-%m-%d")
    end = datetime.datetime.strptime(end_date, "%Y-%m-%d")
    return ((end - start).days) / 365

# 단순히 두 날짜의 차이 산출
def get_diff_two_dates(start_date, end_date):
    start = datetime.datetime.strptime(start_date, "%Y-%m-%d")
    end = datetime.datetime.strptime(end_date, "%Y-%m-%d")
    return ((end - start).days)

def calculate_FRN(val_date, tenors, rates,spread, reset_dates, begin_dates, end_dates, settle_dates, fixing_price_date, fixing_price_value):
    
    discount_tenors = []
    for date in settle_dates:
        diff = get_year_diff_two_dates(val_date, date)
        if diff > 0:
            discount_tenors.append(diff)
        else:
            discount_tenors.append(0)
  
    discount_rates = []
    for i, selected_tenor in enumerate(discount_tenors):
        if selected_tenor == 0:
            discount_rates.append(0)
        else:
            discount_rates.append(get_ir_interpolation(tenors, rates, selected_tenor))

    df=[]
    for selected_tenor, selected_rate in zip(discount_tenors, discount_rates):
        if discount_tenors == 0:
            df.append(0)
        else:
            df.append(1 / math.pow(1+ selected_rate, selected_tenor))

    forward_rates = []
    coupon_num = len(settle_dates)
    
    for i in range(coupon_num):
        if get_year_diff_two_dates(val_date, settle_dates[i]) <= 0:
            forward_rates.append(0)
        elif get_year_diff_two_dates(reset_dates[i],val_date) >= 0:
            idx=fixing_price_date.index(reset_dates[i])
            forward_rates.append(fixing_price_value[idx])
        else:
            forward_rates.append((df[i-1]/df[i]-1)/get_year_diff_two_dates(settle_dates[i-1],settle_dates[i]))
    
    pay_coupon=[0]*len(forward_rates)

    for i, coupon in enumerate(forward_rates):
        if coupon == 0:
            pay_coupon[i] = 0
        else:
            pay_coupon[i] = (coupon + spread)*get_year_diff_two_dates(begin_dates[i],end_dates[i])


    print("Expected Cpn")

    for i, cpn in enumerate(pay_coupon):
        print(f"{i} - th cpn : {cpn}")
    
    result = 0
    for i in range(len(pay_coupon)):
        if i < (len(pay_coupon) -1):
            result += pay_coupon[i] * df[i]
        else:
            result += (1 + pay_coupon[i]) * df[i]

    return result

def calculate_forward_price(today_price, init_price, dividend, volatility, curve_tenors, curve_rates
                      ,n_simul, val_dt, mat_dt):
    maturity_tenor = get_year_diff_two_dates(val_dt, mat_dt)
    #print(f"만기까지 남은 날짜 연환산 : {maturity_tenor}")
    
    maturity_rate = get_ir_interpolation(curve_tenors, curve_rates, maturity_tenor)
    #print(f"만기 tenor에 해당하는 무위험 이자율 : {maturity_rate}")
    
    random_numbers = np.random.normal(0, 1, [n_simul, 1])
    
    dt = maturity_tenor
    
    # 만기 시점에 예상되는 기초자산 가격
    predict_prices = np.zeros(n_simul)
    pay_offs = np.zeros(n_simul)
    
    for i, ran_num in enumerate(random_numbers):
        predict_prices[i] = today_price * np.exp((maturity_rate - dividend - math.pow(volatility, 2)/ 2) * dt + volatility * ran_num * np.sqrt(dt))
        pay_offs[i] = (predict_prices[i] / init_price) - 1
        
    expectation_future = np.average(pay_offs)
    #print(f"Price at {mat_dt} : {expectation_future}")
    
    forward_price = expectation_future * np.exp(- maturity_rate * maturity_tenor)
    #print(f"Forward part present price : {forward_price}")
    
    return forward_price


def calculate_equity_swap(today_price, init_price, dividend, volatility, n_simul, val_dt, mat_dt
                          , spread, reset_dates, begin_dates, end_dates, settle_dates, fixing_price_date, fixing_price_value
                          , curve_tenors, curve_rates):
    forward_price = calculate_forward_price(today_price, init_price, dividend, volatility, curve_tenors, curve_rates
                      ,n_simul, val_dt, mat_dt)
     
    floating_leg_price = calculate_FRN(val_dt, curve_tenors, curve_rates ,spread, reset_dates, begin_dates, end_dates, settle_dates
                                       , fixing_price_date, fixing_price_value)

    #forward part price = -0.0126332067002679 in kiwoom
    return forward_price, floating_leg_price

if __name__ == '__main__':
    import time
    start = time.time()
    ## 발행정보 - Equity(Forward)
    today_price = 316.38
    init_price = 322.21

    dividend = 0.0237
    volatility = 0.16675

    mat_dt = '2023-06-15'

    ## 발행정보 - FRN

    spread = -0.002

    reset_dates = ['2022-06-20','2022-09-20','2022-12-20','2023-03-20']
    begin_dates = ['2022-06-21','2022-09-21','2022-12-21','2023-03-21']
    end_dates = ['2022-09-21','2022-12-21','2023-03-21','2023-06-21']
    settle_dates = ['2022-09-21','2022-12-21','2023-03-21','2023-06-21']

    fixing_price_date = ['2022-06-20']
    fixing_price_value = [0.0199]


    ## Market Data
    curve_tenors = [0.00278,0.25, 0.5, 0.75, 1]
    curve_rates = [0.0176,0.019801,0.023865,0.027499, 0.0308]

    val_dt = '2022-06-21'

    n_simul = 50000
    
    forward_price, floating_leg_price = calculate_equity_swap(today_price, init_price, dividend, volatility, n_simul, val_dt, mat_dt
                          , spread, reset_dates, begin_dates, end_dates, settle_dates, fixing_price_date, fixing_price_value
                          , curve_tenors, curve_rates)
    equity_swap_price = forward_price + floating_leg_price
    
    print(f"Forward leg price = {forward_price}")
    print(f"Floating leg price = {floating_leg_price}")

    print(f"Given Equity Swap price = {equity_swap_price}")
    # forward part price = -0.0126332067002679 in kiwoom
       
    up_pert_curve_rates = [0.0176,0.019801,0.023865,0.027499, 0.0309]
    down_pert_curve_rates = [0.0176,0.019801,0.023865,0.027499, 0.0307]
    
    up_price_forward, up_price_floating = calculate_equity_swap(today_price, init_price, dividend, volatility, n_simul, val_dt, mat_dt
                          , spread, reset_dates, begin_dates, end_dates, settle_dates, fixing_price_date, fixing_price_value
                          , curve_tenors, up_pert_curve_rates)
    
    up_price = up_price_forward + up_price_floating
    down_price_forward, down_price_floating = calculate_equity_swap(today_price, init_price, dividend, volatility, n_simul, val_dt, mat_dt
                          , spread, reset_dates, begin_dates, end_dates, settle_dates, fixing_price_date, fixing_price_value
                          , curve_tenors, down_pert_curve_rates)
    down_price = down_price_forward + down_price_floating
        
    print(f"1Y Tenor pv01 = {(up_price - down_price)/2}")
    print(f"Execute time : {time.time() - start}")