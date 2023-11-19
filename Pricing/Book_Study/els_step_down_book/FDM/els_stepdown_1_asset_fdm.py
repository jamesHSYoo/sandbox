import numpy as np
import matplotlib.pyplot as plt

import time

def thomas(alpha, beta, gamma, f):
    n = len(f)
    v = np.zeros(n)

    [aa, dd, cc, bb] = map(np.array, [alpha, beta, gamma, f])

    for i in range(1, n):
        mult = aa[i]/dd[i-1]
        dd[i] = dd[i] - mult * cc[i-1]
        bb[i] = bb[i] - mult * bb[i-1]

    v[n-1] = bb[n-1] / dd[n-1]

    for i in range(n-2, -1, -1):
        v[i] = (bb[i]-cc[i]*v[i+1])/dd[i]

    return v

def calculate_one_asset():

    start = time.time()

    facevalue = 10000
    R = 300
    volatility = 0.1778
    r = 0.0165
    Nx = 301
    h = R/Nx
    x0 = 100
    x = np.linspace(0, R, Nx)
    T = 3
    Nt = 360*T
    dt = T/Nt

    u = np.zeros((Nx, Nt+1))
    ku = np.zeros((Nx, Nt+1))

    coupon_rate = np.array([0.132, 0.11, 0.088, 0.066, 0.044, 0.022])

    strike_price = np.array([0.85, 0.90, 0.90, 0.95, 0.95, 0.95])

    step = np.array([np.rint(Nt/6), np.rint(2*Nt/6), np.rint(3*Nt/6), np.rint(4*Nt/6), np.rint(5*Nt/6), Nt+1])

    dummy = 0.132
    kib = 0.65

    for i in range(0, Nx):
        if x[i] < kib * x0:
            u[i, 0] = x[i] / x0 * facevalue
            ku[i, 0] = x[i] / x0 * facevalue
        elif x[i] < strike_price[0] * x0:
            u[i, 0] = facevalue * (1 + dummy)
            ku[i, 0] = x[i] / x0 * facevalue
        else:
            u[i, 0] = facevalue * (1 + coupon_rate[0])
            ku[i, 0] = facevalue * (1 + coupon_rate[0])

    [a, d, c, b] = map(np.zeros, [Nx, Nx, Nx, Nx])

    a[:] = r * x / (2*h) - (volatility*x)**2/(2*h**2)
    d[:] = (volatility * x) ** 2 / (h**2) + r + (1/dt)
    c[:] = -r * x / (2*h) - (volatility*x)**2 / (2*h**2)

    a[Nx-1] = a[Nx-1] - c[Nx-1]
    d[Nx-1] = d[Nx-1] + 2 * c[Nx-1]
    tag = 0

    for n in range(0, Nt):
        if n == step[tag]:
            s = np.min(np.where(x >= x0*strike_price[tag + 1]))
            u[s:Nx+1, n] = facevalue * (1+coupon_rate[tag + 1])
            ku[s:Nx + 1, n] = facevalue * (1 + coupon_rate[tag + 1])
            tag = tag+1

        s = np.min(np.where(x >= x0*kib))
        u[0:s, n] = ku[0: s, n]
        b = u[:, n]/dt
        u[:, n+1] = thomas(a, d, c, b)
        b = ku[:, n] / dt
        ku[:, n+1] = thomas(a, d, c, b)

    # plt.figure(1)
    # plt.plot(u[:, Nt-1], 'k', linewidth=0.8, label = 'no Knock-In')
    # plt.plot(ku[:, Nt-1], 'k--', linewidth=0.8, label = 'Knock-In')
    #
    # plt.xlabel("x", fontsize=10)
    # plt.ylabel("ELS Price", fontsize=10)
    #
    # plt.legend()
    # plt.show()
    ii = np.where(x==100)
    # print('Price : %f'%(u[ii, Nt]))

    working_time = time.time()-start

    print("Pricing time for 1 asset : %f"%(working_time))

    return u[ii, Nt][0][0]


if __name__ =='__main__':
    print(calculate_one_asset())