import numpy as np
import time

from datetime import date


def calculate_1_asset_mc():
    start = time.time()

    n = 100000  # 시뮬레이션 횟수
    r = 0.0165  # 이자율

    vol = 0.1778  # 변동성

    # 조기상환 평가일
    n0 = date.toordinal(date(2018, 3, 23))
    n1 = date.toordinal(date(2018, 9, 19))
    n2 = date.toordinal(date(2019, 3, 20))
    n3 = date.toordinal(date(2019, 9, 19))
    n4 = date.toordinal(date(2020, 3, 19))
    n5 = date.toordinal(date(2020, 9, 21))
    n6 = date.toordinal(date(2021, 3, 19))

    # 조기상환일 벡터
    check_day = np.array([n1 - n0, n2 - n0, n3 - n0, n4 - n0, n5 - n0, n6 - n0])

    # 1년 일수
    one_year = 365

    # 만기 상환일
    tot_date = n6 - n0

    # 시간 격자 간격
    dt = 1 / one_year

    # 주가 벡터
    S = np.zeros([tot_date + 1, 1])

    # 기초 자산 초깃값
    S[0] = 100.0

    # 조기행사 가격 벡터
    strike_price = np.array([0.95, 0.95, 0.95, 0.90, 0.90, 0.85]) * S[0]

    # 조기상환 횟수
    repay_n = len(strike_price)

    # 조기 행사 시 받게 되는 이자율 벡터
    coupon_rate = np.array([0.022, 0.044, 0.066, 0.088, 0.11, 0.132])

    # 조기 상환 시 페이오프 벡터
    payment = np.zeros([repay_n, 1])

    # 액면금액
    face_value = 10 ** 4

    # 전체 페이오프 벡터
    tot_payoff = np.zeros([repay_n, 1])

    # 페이오프 벡터
    payoff = np.zeros([repay_n, 1])

    # 할인된 페이오프 벡터
    discount_payoff = np.zeros([repay_n, 1])

    # 낙인 배리어
    kib = 0.65 * S[0]

    # 더미 이자율
    dummy = 0.132

    # 조기 상환 시 페이오프 벡터 생성
    payment = np.array([face_value * (1 + coupon_rate[i]) for i in range(repay_n)])

    # ELS 가격 결정 Using Monte Carlo
    for i in range(n):
        # 만기 상환일 만큼의 랜덤 넘버 생성

        if i % 100 == 0:
            print("%d - th Simulation" % i)

        z = np.random.normal(0, 1, size=[tot_date, 1])
        # 임의의 주가 경로 생성
        for j in range(tot_date):
            S[j + 1] = S[j] * np.exp((r - 0.5 * vol ** 2) * dt + vol * z[j] * np.sqrt(dt))

        # 조기상환일 체크하여 페이오프 결정
        S_checkday = S[check_day]
        payoff = np.zeros([repay_n, 1])

        repay_event = 0
        for j in range(repay_n):
            if S_checkday[j] >= strike_price[j]:
                payoff[j] = payment[j]
                # 조기 상환 된 상태
                repay_event = 1
                break

        # 조기상환 되지 않고 만기까지 온 경우
        if repay_event == 0:
            if min(S) > kib:   # 낙인 배리어 아래로 내려간 적이 없는 경우
                payoff[-1] = face_value*(1+dummy)
            else:              # 낙인 배리어 아래로 내려간 적이 있는 경우
                payoff[-1] = face_value*(S[-1]/S[0])
        tot_payoff = tot_payoff + payoff

    # 모든 시뮬레이션의 페이오프의 평균을 구함
    mean_payoff = tot_payoff/n

    # 페이오프를 무위험 이자율로 할인하여 현재 가격을 구함
    for j in range(repay_n):
        discount_payoff[j] = mean_payoff[j] * np.exp(-r*check_day[j] / one_year)

    print("Working time : %f" %(time.time() - start))
    # ELS 가격 구함
    return np.sum(discount_payoff)


if __name__ == '__main__':
    print(calculate_1_asset_mc())