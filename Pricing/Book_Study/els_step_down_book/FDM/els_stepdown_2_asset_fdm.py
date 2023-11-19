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

def calculate_two_asset():
    start = time.time()

    facevalue = 10000
    R = 300

    x_volatility = 0.249
    y_volatility = 0.2182

    rho = 0.0981

    r = 0.0165
    Nx = 61
    Ny = Nx

    h = R / Nx
    x0 = 100
    y0 = 100

    x = np.linspace(0, R, Nx)
    y = x

    T = 3
    Nt = 360 * T
    dt = T / Nt

    lst = [Nx, Ny]

    [u, ku, old_u, old_ku] = map(np.zeros, [lst, lst, lst, lst])

    coupon_rate = np.array([0.15, 0.125, 0.10, 0.075, 0.05, 0.025])

    step = np.array(
        [np.rint(Nt / 6), np.rint(2 * Nt / 6), np.rint(3 * Nt / 6), np.rint(4 * Nt / 6), np.rint(5 * Nt / 6), Nt + 1])

    strike_price = np.array([0.75, 0.80, 0.85, 0.85, 0.90, 0.90])

    dummy = 0.15
    kib = 0.50

    for i in range(0, Nx):
        for j in range(0, Ny):
            if x[i] < kib * x0 or y[j] < kib * y0:
                u[i, j] = np.minimum(x[i], y[j]) / x0 * facevalue
                ku[i, j] = np.minimum(x[i], y[j]) / x0 * facevalue
            elif x[i] <= strike_price[0] * x0 or y[j] <= strike_price[0] * y0:
                u[i, j] = facevalue * (1 + dummy)
                ku[i, j] = np.minimum(x[i], y[j]) / x0 * facevalue
            else:
                u[i, j] = facevalue * (1 + coupon_rate[0])
                ku[i, j] = facevalue * (1 + coupon_rate[0])

    [ax, dx, cx, ay, dy, cy] = map(np.zeros, [Nx - 2, Nx - 2, Nx - 2, Ny - 2, Ny - 2, Ny - 2])

    ax[:] = -0.5 * (x_volatility * x[1:Nx - 1] / h) ** 2 + 0.5 * r * x[1:Nx - 1] / h
    dx[:] = 1 / dt + (x_volatility * x[1:Nx - 1] / h) ** 2 + r * 0.5
    cx[:] = -0.5 * (x_volatility * x[1:Nx - 1] / h) ** 2 - 0.5 * r * x[1:Nx - 1] / h
    ax[Nx - 3] = ax[Nx - 3] - cx[Nx - 3]
    dx[Nx - 3] = dx[Nx - 3] + 2 * cx[Nx - 3]

    ay[:] = -0.5 * (y_volatility * y[1:Ny - 1] / h) ** 2 + 0.5 * r * y[1:Ny - 1] / h
    dy[:] = 1 / dt + (y_volatility * y[1:Ny - 1] / h) ** 2 + r * 0.5
    cy[:] = -0.5 * (y_volatility * y[1:Ny - 1] / h) ** 2 - 0.5 * r * y[1:Ny - 1] / h
    ay[Ny - 3] = ay[Ny - 3] - cy[Ny - 3]
    dy[Ny - 3] = dy[Ny - 3] + 2 * cy[Ny - 3]

    tag = 0

    bx = np.zeros(Nx - 2)
    by = np.zeros(Ny - 2)

    for n in range(0, Nt):
        if n == step[tag]:
            gx = np.min(np.where(x >= x0 * strike_price[tag + 1]))
            gy = np.min(np.where(y >= y0 * strike_price[tag + 1]))

            u[gx: Nx - 1, gy: Ny - 1] = facevalue * (1 + coupon_rate[tag + 1])
            ku[gx: Nx - 1, gy: Ny - 1] = facevalue * (1 + coupon_rate[tag + 1])

            tag = tag + 1

        gx = np.min(np.where(x >= x0 * kib))
        gy = np.min(np.where(y >= y0 * kib))

        u[:, 0:gy + 1] = ku[:, 0:gy + 1]
        u[0:gx + 1, :] = ku[0:gy + 1, :]

        old_u = u
        old_ku = ku

        # u
        for j in range(1, Ny - 1):
            bx[0:Nx - 1] = old_u[1:Nx - 1, j] / dt + 0.5 * rho * x_volatility * y_volatility * x[1:Nx - 1] * y[j] \
                           * (old_u[2:Nx, j + 1] - old_u[2:Nx, j - 1] - old_u[0:Nx - 2, j + 1] + old_u[0:Nx - 2, j - 1]) / (4 * h ** 2)
            u[1:Nx - 1, j] = thomas(ax, dx, cx, bx)
        u[Nx - 1, 1:Ny - 1] = 2 * u[Nx - 2, 1:Ny - 1] - u[Nx - 3, 1:Ny - 1]
        u[:, Ny - 1] = 2 * u[:, Ny - 2] - u[:, Ny - 3]
        old_u = u

        for i in range(1, Nx - 1):
            by[0:Ny - 1] = old_u[i, 1:Ny - 1] / dt + 0.5 * rho * x_volatility * y_volatility * x[i] * y[1:Ny - 1] \
                           * (old_u[i + 1, 2:Ny] - old_u[i + 1, 0:Ny - 2] - old_u[i - 1, 2:Ny] + old_u[i - 1, 0:Ny - 2]) / (4 * h ** 2)
            u[i, 1:Ny - 1] = thomas(ay, dy, cy, by)
        u[1:Nx - 1, Ny - 1] = 2 * u[1:Nx - 1, Ny - 2] - u[1:Nx - 1, Ny - 3]
        u[Nx - 1, :] = 2 * u[Nx - 2, :] - u[Nx - 3, :]


        # ku
        for j in range(1, Ny - 1):
            bx[0:Nx - 1] = old_ku[1:Nx - 1, j] / dt + 0.5 * rho * x_volatility * y_volatility * x[1:Nx - 1] * y[j] \
                           * (old_ku[2:Nx, j + 1] - old_ku[2:Nx, j - 1] - old_ku[0:Nx - 2, j + 1] + old_ku[0:Nx - 2, j - 1]) / (4 * h ** 2)
            ku[1:Nx - 1, j] = thomas(ax, dx, cx, bx)
        ku[Nx - 1, 1:Ny - 1] = 2 * ku[Nx - 2, 1:Ny - 1] - ku[Nx - 3, 1:Ny - 1]
        ku[:, Ny - 1] = 2 * ku[:, Ny - 2] - ku[:, Ny - 3]
        old_ku = ku

        for i in range(1, Nx - 1):
            by[0:Ny - 1] = old_ku[i, 1:Ny - 1] / dt \
                           + 0.5 * rho * x_volatility * y_volatility * x[i] * y[1:Ny - 1] \
                           * (old_ku[i + 1, 2:Ny] - old_ku[i + 1, 0:Ny - 2] - old_ku[i - 1, 2:Ny] + old_ku[i - 1, 0:Ny - 2]) / (4 * h ** 2)
            ku[i, 1:Ny - 1] = thomas(ay, dy, cy, by)
        ku[1:Nx - 1, Ny - 1] = 2 * ku[1:Nx - 1, Ny - 2] - ku[1:Nx - 1, Ny - 3]
        ku[Nx - 1, :] = 2 * ku[Nx - 2, :] - ku[Nx - 3, :]

    ii = np.where(x == 100)
    jj = np.where(y == 100)

    working_time = time.time() - start

    print("Pricing time for 2 asset : %f" % working_time)

    return u[ii, jj][0][0]


if __name__ == '__main__':
    print(calculate_two_asset())
