import numpy as np
from datetime import date

# 시뮬레이션 횟수
n = 1000

# 이자율
r = 0.0165

# 기초자산 변동성
x_vol = 0.2662
y_vol = 0.2105
z_vol = 0.2111

n0 = date.toordinal(date(2017, 12, 14))
n1 = date.toordinal(date(2018, 6, 8))
n2 = date.toordinal(date(2018, 12, 11))
n3 = date.toordinal(date(2019, 6, 11))
n4 = date.toordinal(date(2019, 12, 10))
n5 = date.toordinal(date(2020, 6, 9))
n6 = date.toordinal(date(2020, 12, 9))

check_day = np.array([n1-n0, n2-n0, n3-n0, n4-n0, n5-n0, n6-n0])

# 기초자산 간 상관 계수
rho_xy = 0.279
rho_yz = 0.5256
rho_xz = 0.2895

# 촐레스키 분해를 사용하기 위한 상관계수 행렬
corr = [[1, rho_xy, rho_xz], [rho_xy, 1, rho_yz], [rho_xz, rho_yz, 1]]

k = np.linalg.cholesky(corr)

one_year = 365

tot_date = n6-n0

dt = 1/one_year

S1 = np.zeros([tot_date + 1, 1])
S2 = np.zeros([tot_date + 1, 1])
S3 = np.zeros([tot_date + 1, 1])

S1[0] = 100
S2[0] = 100
S3[0] = 100

ratio_S1 = S1[0]
ratio_S2 = S2[0]
ratio_S3 = S3[0]

strike_price = [0.95, 0.95, 0.90, 0.90, 0.85, 0.85]

repay_n = len(strike_price)

coupon_rate = [0.048, 0.096, 0.144, 0.192, 0.24, 0.288]

tot_payoff = np.zeros([repay_n, 1])

payoff = np.zeros([repay_n, 1])

payment = np.array([repay_n, 1])

face_value = 10**4

kib = 0.5

dummy = 0.06

payment = [face_value * coupon_rate[i] for i in range(repay_n)]



for i in range(n):
    w0 = np.transpose(np.random.normal(0, 1, size=[tot_date, 3]))
    w = np.matmul(k, w0)

    for j in range(tot_date):
        S1[j + 1] = S1[j] * np.exp((r - 0.5 * x_vol ** 2) * dt + x_vol * np.sqrt(dt) * w[0, j])
        S2[j + 1] = S1[j] * np.exp((r - 0.5 * y_vol ** 2) * dt + y_vol * np.sqrt(dt) * w[1, j])
        S3[j + 1] = S1[j] * np.exp((r - 0.5 * z_vol ** 2) * dt + z_vol * np.sqrt(dt) * w[2, j])

    R1 = S1 / ratio_S1
    R2 = S2 / ratio_S2
    R3 = S3 / ratio_S3

    WP = np.minimum(R1, R2, R3)

    WP_checkday = WP[check_day]

    repay_event = 0

    for j in range(repay_n):
        if WP_checkday[j] >= strike_price[j]:
            payoff[j] = payment[j]
            repay_event = 1
            break

    if repay_event == 0:
        if min(WP) > kib:
            payoff[-1] = face_value * (1 + dummy)
        else:
            payoff[-1] = face_value * WP[-1]

    tot_payoff = tot_payoff + payoff

mean_payoff = tot_payoff/n

discount_payoff = [mean_payoff[i] * np.exp(-r*check_day[i]/one_year) for i in range(repay_n)]

price = np.sum(discount_payoff)
print(price)









