import numpy as np
from datetime import date

# 시뮬레이션 횟수
n = 1000
# 이자율
r = 0.0165

# 기초자산 변동성
x_vol = 0.249
y_vol = 0.2182

# 평가일
n0 = date.toordinal(date(2018, 6, 29))
n1 = date.toordinal(date(2018, 12, 21))
n2 = date.toordinal(date(2019, 6, 25))
n3 = date.toordinal(date(2019, 12, 23))
n4 = date.toordinal(date(2020, 6, 24))
n5 = date.toordinal(date(2020, 12, 23))
n6 = date.toordinal(date(2021, 6, 24))

# 조기상환일 벡터
check_day = np.array([n1 - n0, n2 - n0, n3 - n0, n4 - n0, n5 - n0, n6 - n0])

# 두 자산의 상관계수
rho = 0.0981

# 촐레스키 분해를 사용하기위한 상관계수 행렬
corr = np.array([[1, rho], [rho, 1]])

# 쿠폰 배열
coupon_rate = np.array([0.025, 0.05, 0.075, 0.1, 0.125, 0.15])

# chol 함수를 이용하여 촐레스키 분해
k = np.linalg.cholesky(corr)

# 1년 일수
oneyear = 365

# 만기
tot_date = n6 - n0

# 기간 격자 간격
dt = 1 / oneyear

# 기초 자산 초깃값
S1 = np.zeros((tot_date + 1, 1))
S2 = np.zeros((tot_date + 1, 1))
S1[0] = 100
S2[0] = 100

ratio_S1 = S1[0]
ratio_S2 = S2[0]

# 조기행사 가격 벡터
strike_price = ([0.90, 0.90, 0.85, 0.85, 0.80, 0.75])

# 조기상환 횟수
repay_n = len(strike_price)

# 조기행사시 페이오프 벡터
payment = np.zeros([repay_n, 1])

# 페이오프 벡터
payoff = np.zeros([repay_n, 1])

# 전체 페이오프 벡터
tot_payoff = np.zeros([repay_n, 1])

# 현가 할인 된 페이오프 벡터
discount_payoff = np.zeros([repay_n, 1])

# 액면금액
face_value = 10 ** 4

# 더미 이자율
dummy = 0.15

# 낙인 베리어
kib = 0.50

# 조기상환 했을 때 페이오프 벡터 생성
for j in range(repay_n):
    payment[j] = face_value * (1 + coupon_rate[j])

for i in range(n):
    w0 = np.transpose(np.random.normal(0, 1, size=[tot_date, 2]))
    w = np.matmul(k, w0)

    for j in range(tot_date):
        S1[j + 1] = S1[j] * np.exp((r - 0.5 * (x_vol ** 2)) * dt + x_vol * np.sqrt(dt) * w[0, j])
        S2[j + 1] = S2[j] * np.exp((r - 0.5 * (x_vol ** 2)) * dt + x_vol * np.sqrt(dt) * w[1, j])

    R1 = S1 / ratio_S1
    R2 = S2 / ratio_S2

    worst_performance = np.minimum(R1, R2)
    wp_checkday = worst_performance[check_day]

    payoff = np.zeros([repay_n, 1])
    repay_event = 0

    for j in range(repay_n):
        # 중간 평가일에 조기상환 발생 여부 확인
        if wp_checkday[j] >= strike_price[j]: 
            # 조기상환 됨
            payoff[j] = payment[j]
            repay_event = 1       #case 3
            break

    if repay_event == 0:
        if min(worst_performance) > kib:
            # 낙인 베리어로 내려간적 없음
            payoff[-1] = face_value * (1 + dummy) # case 2
        else:
            # 낙인 베리어 아래로 내려간 적이 있는 경우
            payoff[-1] = face_value * worst_performance[-1] # case 4


    tot_payoff = tot_payoff + payoff

mean_payoff = tot_payoff / n

for j in range(repay_n):
    discount_payoff[j] = mean_payoff[j] * np.exp(-r*check_day[j]/oneyear)

print(np.sum(discount_payoff))
