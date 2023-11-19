import numpy as np
import time
import book_study.els_step_down_book.FDM.thomas as tho


def calculate_three_assets():

    start = time.time()

    facevalue = 10000

    x_volatility = 0.2662
    y_volatility = 0.2105
    z_volatility = 0.2111

    rho_xy = 0.279
    rho_yz = 0.5256
    rho_zx = 0.2895

    r = 0.0165

    T = 3
    Nt = 180*T
    dt = T/Nt

    x0 = 100
    y0 = 100
    z0 = 100

    A = np.array([0])
    B = np.arange(65, 132.5, 2.5)
    C = np.array([160, 180, 200, 220])

    x = np.r_[A, B, C]
    y = x
    z = x

    Nx = len(x)
    Ny = Nx
    Nz = Nx

    hx = np.diff(x)
    hy = hx
    hz = hx

    coupon_rate = np.array([0.28, 0.24, 0.192, 0.144, 0.096, 0.048])

    step = np.arange(1, 8, 1)*Nt/6

    strike_price = np.array([0.85, 0.85, 0.9, 0.9, 0.95, 0.95])

    dummy = 0.06
    kib = 0.50
    lst = [Nx, Ny, Nz]

    [u, ku] = map(np.zeros, [lst, lst])

    for i in range(0, Nx):
        for j in range(0, Ny):
            for k in range(0, Nz):
                if x[i] <= kib*x0 or y[j] <= kib*y0 or z[k] <= kib*z0:
                    u[i, j, k] = np.min([x[i], y[j], z[k]]) / x0 * facevalue
                    ku[i, j, k] = np.min([x[i], y[j], z[k]]) / x0 * facevalue
                elif x[i] < strike_price[0] * x0 or y[j] < strike_price[0] * y0 or z[k] < strike_price[0] * z0:
                    u[i, j, k] = facevalue * (1.0 + dummy)
                    ku[i, j, k] = np.min([x[i], y[j], z[k]]) / x0 * facevalue
                else:
                    u[i, j, k] = facevalue * (1.0 + coupon_rate[0])
                    ku[i, j, k] = facevalue * (1.0 + coupon_rate[0])

    [ax, dx, cx, ay, dy, cy, az, dz, cz] = map(np.zeros, [Nx-2, Nx-2, Nx-2, Ny-2, Ny-2, Ny-2, Nz-2, Nz-2, Nz-2])

    ax[:] = (-(x_volatility*x[1:Nx-1])**2 + r * x[1:Nx-1]*hx[1:Nx-1])/(hx[0:Nx-2]*(hx[0:Nx-2] + hx[1:Nx-1]))
    dx[:] = 1/dt + (x_volatility*x[1:Nx-1])**2/(hx[0:Nx-2]*hx[1:Nx-1]) - r*x[1:Nx-1] * (hx[1:Nx-1] - hx[0:Nx-2]) / (hx[0:Nx-2]*hx[1:Nx-1]) + r/3
    cx[:] = -((x_volatility*x[1:Nx-1])**2 + r*x[1:Nx-1] * hx[0:Nx-2]) / (hx[1:Nx-1]*(hx[0:Nx-2] + hx[1:Nx-1]))
    ax[Nx-3] = ax[Nx-3] - cx[Nx-3]
    dx[Nx-3] = dx[Nx-3] + 2 * cx[Nx-3]

    ay[:] = (-(y_volatility*y[1:Ny-1])**2 + r * y[1:Ny-1]*hy[1:Ny-1])/(hy[0:Ny-2]*(hy[0:Ny-2] + hy[1:Ny-1]))
    dy[:] = 1/dt + (y_volatility*y[1:Ny-1])**2/(hy[0:Ny-2]*hy[1:Ny-1]) - r*y[1:Ny-1] * (hy[1:Ny-1] - hy[0:Ny-2]) / (hy[0:Ny-2]*hy[1:Ny-1]) + r/3
    cy[:] = -((y_volatility*y[1:Ny-1])**2 + r*y[1:Ny-1] * hy[0:Ny-2]) / (hy[1:Ny-1]*(hy[0:Ny-2] + hy[1:Ny-1]))
    ay[Ny-3] = ay[Ny-3] - cy[Ny-3]
    dy[Ny-3] = dy[Ny-3] + 2 * cy[Ny-3]

    az[:] = (-(z_volatility*z[1:Nz-1])**2 + r * z[1:Nz-1]*hz[1:Nz-1])/(hz[0:Nz-2]*(hz[0:Nz-2] + hz[1:Nz-1]))
    dz[:] = 1/dt + (z_volatility*z[1:Nz-1])**2/(hz[0:Nz-2]*hz[1:Nz-1]) - r*z[1:Nz-1] * (hz[1:Nz-1] - hz[0:Nz-2]) / (hz[0:Nz-2]*hz[1:Nz-1]) + r/3
    cz[:] = -((z_volatility*z[1:Nz-1])**2 + r*z[1:Nz-1] * hz[0:Nz-2]) / (hz[1:Nz-1]*(hz[0:Nz-2] + hz[1:Nz-1]))
    az[Nz-3] = az[Nz-3] - cz[Nz-3]
    dz[Nz-3] = dz[Nz-3] + 2 * cz[Nz-3]

    [old_u, old_ku] = map(np.zeros, [lst, lst])
    [fx, fy, fz] = map(np.zeros, [Nx-2, Ny-2, Nz-2])
    tag = 0

    for iter in range(0, Nt):
        if iter == step[tag]:
            gx = np.min(np.where(x >= x0 * strike_price[tag + 1]))
            gy = np.min(np.where(y >= y0 * strike_price[tag + 1]))
            gz = np.min(np.where(z >= z0 * strike_price[tag + 1]))
            u[gx:Nx, gy:Ny, gz:Nz] = facevalue * (1 + coupon_rate[tag + 1])
            ku[gx:Nx, gy:Ny, gz:Nz] = facevalue * (1 + coupon_rate[tag + 1])
            tag = tag + 1

        gx = np.min(np.where(x >= x0 * kib))
        gy = np.min(np.where(y >= y0 * kib))
        gz = np.min(np.where(z >= z0 * kib))
        # 확인완료

        u[0:gx + 1, :, :] = ku[0:gx + 1, :, :]
        u[:, 0:gy + 1, :] = ku[:, 0:gy + 1, :]
        u[:, :, 0:gz + 1] = ku[:, :, 0:gz + 1]

        for j in range(1, Ny - 1):
            for k in range(1, Nz - 1):
                fx[0:Nx-1] = 1/3 * rho_xy * x_volatility * y_volatility * x[1:Nx-1] * y[j] * (u[2:Nx, j+1, k] - u[2:Nx, j-1, k] - u[0:Nx-2, j+1, k] + u[0:Nx-2, j-1, k]) \
                             / (hx[0:Nx-2] * hy[j] + hx[1:Nx-1] * hy[j] + hx[1:Nx-1] * hy[j-1] + hx[0:Nx-2] * hy[j-1]) \
                             + 1/3 * rho_zx * x_volatility * z_volatility * x[1:Nx-1] * z[k] * (u[2:Nx, j, k+1] - u[2:Nx, j, k-1] - u[0:Nx-2, j, k+1] + u[0:Nx-2, j, k-1]) \
                             / (hx[0:Nx-2] * hz[k] + hx[1:Nx-1] * hz[k] + hx[1:Nx-1] * hz[k-1] + hx[0:Nx-2] * hz[k-1]) \
                             + 1/3 * rho_yz * y_volatility * z_volatility * y[j] * z[k] * (u[1:Nx-1, j+1, k+1] - u[1:Nx-1, j+1, k-1] - u[1:Nx-1, j-1, k+1] + u[1:Nx-1, j-1, k-1]) \
                             / (hy[j-1] * hz[k] + hy[j] * hz[k] + hy[j] * hz[k-1] + hy[j-1] * hz[k-1]) + u[1:Nx-1, j, k]/dt
                old_u[1:Nx-1, j, k] = tho.thomas(ax, dx, cx, fx)
        old_u[1:Nx-1, 1:Ny-1, Nz-1] = 2 * old_u[1:Nx-1, 1:Ny-1, Nz-2] - old_u[1:Nx-1, 1:Ny-1, Nz-3]
        old_u[Nx-1, 1:Ny-1, 1:Nz] = 2 * old_u[Nx-2, 1:Ny-1, 1:Nz] - old_u[Nx-3, 1:Ny-1, 1:Nz]
        old_u[1:Nx, Ny-1, 1:Nz] = 2 * old_u[1:Nx, Ny-2, 1:Nz] - old_u[1:Nx, Ny-3, 1:Nz]

        for k in range(1, Nz-1):
            for i in range(1, Nx-1):
                fy[0:Ny-1] = 1/3 * rho_xy * x_volatility * y_volatility * x[i] * y[1:Ny-1] * (old_u[i+1, 2:Ny, k] - old_u[i+1, 0:Ny-2, k] - old_u[i-1, 2:Ny, k] + old_u[i-1, 0:Ny-2, k]) \
                             / (hx[i-1] * hy[1:Ny-1] + hx[i] * hy[1:Ny-1] + hx[i] * hy[0:Ny-2] + hx[i-1] * hy[0:Ny-2]) \
                             + 1/3 * rho_zx * z_volatility * x_volatility * x[i] * z[k] * (old_u[i+1, 1:Ny-1, k+1] - old_u[i+1, 1:Ny-1, k-1] - old_u[i-1, 1:Ny-1, k+1] +old_u[i-1, 1:Ny-1, k-1]) \
                             / (hx[i-1] * hz[k] + hx[i] * hz[k] + hx[i] * hz[k-1] + hx[i-1] * hz[k-1]) \
                             + 1/3 * rho_yz * y_volatility * z_volatility * y[1:Ny-1] * z[k] * (old_u[i, 2:Ny, k+1] - old_u[i, 2:Ny, k-1] - old_u[i, 0:Ny-2, k+1] + old_u[i, 0:Ny-2, k-1]) \
                             / (hy[0:Ny-2] * hz[k] + hy[1:Ny-1] * hz[k] + hy[1:Ny-1] * hz[k-1] + hy[0:Ny-2] * hz[k-1]) + old_u[i, 1:Ny-1, k]/dt
                u[i, 1:Ny-1, k] = tho.thomas(ay, dy, cy, fy)
        u[1:Nx - 1, 1:Ny - 1, Nz - 1] = 2 * u[1:Nx - 1, 1:Ny - 1, Nz - 2] - u[1:Nx - 1, 1:Ny - 1, Nz - 3]
        u[Nx - 1, 1:Ny - 1, 1:Nz] = 2 * u[Nx-2, 1:Ny - 1, 1:Nz] - u[Nx - 3, 1:Ny - 1, 1:Nz]
        u[1:Nx, Ny - 1, 1:Nz] = 2 * u[1:Nx, Ny - 2, 1:Nz] - u[1:Nx, Ny-3, 1:Nz]

        for j in range(1, Ny-1):
            for i in range(1, Nx-1):
                fz[0:Nz-1] = 1/3 * rho_xy * x_volatility * y_volatility * x[i] * y[j] * ((u[i+1, j+1, 1:Nz-1] - u[i+1, j-1, 1:Nz-1] - u[i-1, j+1, 1:Nz-1] + u[i-1, j-1, 1:Nz-1]) \
                             / (hx[i-1] * hy[j] + hx[i] * hy[j] + hx[i] * hy[j-1] + hx[i-1] * hy[j-1])) \
                             + 1/3 * rho_zx * z_volatility * x_volatility * x[i] * z[1:Nz-1] * ((u[i+1, j, 2:Nz] - u[i+1, j, 0:Nz-2] - u[i-1, j, 2:Nz] + u[i-1, j, 0:Nz-2]) \
                             / (hx[i-1] * hz[1:Nz-1] + hx[i] * hz[1:Nz-1] + hx[i] * hz[0:Nz-2] + hx[i-1] * hz[0:Nz-2])) \
                             + 1/3 * rho_yz * y_volatility * z_volatility * y[j] * z[1:Nz-1] * ((u[i, j+1, 2:Nz] - u[i, j+1, 0:Nz-2] - u[i, j-1, 2:Nz] + u[i, j-1, 0:Nz-2]) \
                             / (hy[j-1] * hz[1:Nz-1] + hy[j] * hz[1:Nz-1] + hy[j] * hz[0:Nz-2] + hy[j-1] * hz[0:Nz-2]) + u[i, j, 1:Nz-1])
                old_u[i, j, 1:Nz-1] = tho.thomas(az, dz, cz, fz)
        old_u[1:Nx - 1, 1:Ny - 1, Nz - 1] = 2 * old_u[1:Nx - 1, 1:Ny - 1, Nz - 2] - old_u[1:Nx - 1, 1:Ny - 1, Nz - 3]
        old_u[Nx - 1, 1:Ny - 1, 1:Nz] = 2 * old_u[Nx - 2, 1:Ny - 1, 1:Nz] - old_u[Nx - 3, 1:Ny - 1, 1:Nz]
        old_u[1:Nx, Ny - 1, 1:Nz] = 2 * old_u[1:Nx, Ny - 2, 1:Nz] - old_u[1:Nx, Ny - 3, 1:Nz]

        u = old_u

        for j in range(1, Ny - 1):
            for k in range(1, Nz - 1):
                fx[0:Nx-1] = 1/3 * rho_xy * x_volatility * y_volatility * x[1:Nx-1] * y[j] * (ku[2:Nx, j+1, k] - ku[2:Nx, j-1, k] - ku[0:Nx-2, j+1, k] + ku[0:Nx-2, j-1, k]) \
                             / (hx[0:Nx-2] * hy[j] + hx[1:Nx-1] * hy[j] + hx[1:Nx-1] * hy[j-1] + hx[0:Nx-2] * hy[j-1]) \
                             + 1/3 * rho_zx * x_volatility * z_volatility * x[1:Nx-1] * z[k] * (ku[2:Nx, j, k+1] - ku[2:Nx, j, k-1] - ku[0:Nx-2, j, k+1] + ku[0:Nx-2, j, k-1]) \
                             / (hx[0:Nx-2] * hz[k] + hx[1:Nx-1] * hz[k] + hx[1:Nx-1] * hz[k-1] + hx[0:Nx-2] * hz[k-1]) \
                             + 1/3*rho_yz * y_volatility * z_volatility * y[j] * z[k] * (ku[1:Nx-1, j+1, k+1] - ku[1:Nx-1, j+1, k-1] - ku[1:Nx-1, j-1, k+1] + ku[1:Nx-1, j-1, k-1]) \
                             / (hy[j-1] * hz[k] + hy[j] * hz[k] + hy[j] * hz[k-1] + hy[j-1] * hz[k-1]) + ku[1:Nx-1, j, k]/dt
                old_ku[1:Nx-1, j, k] = tho.thomas(ax, dx, cx, fx)
        old_ku[1:Nx-1, 1:Ny-1, Nz-1] = 2 * old_ku[1:Nx-1, 1:Ny-1, Nz-2] - old_ku[1:Nx-1, 1:Ny-1, Nz-3]
        old_ku[Nx-1, 1:Ny-1, 1:Nz] = 2 * old_ku[Nx-2, 1:Ny-1, 1:Nz] - old_ku[Nx-3, 1:Ny-1, 1:Nz]
        old_ku[1:Nx, Ny-1, 1:Nz] = 2 * old_ku[1:Nx, Ny-2, 1:Nz] - old_ku[1:Nx, Ny-3, 1:Nz]

        for k in range(1, Nz-1):
            for i in range(1, Nx-1):
                fy[0:Ny-1] = 1/3 * rho_xy * x_volatility * y_volatility * x[i] * y[1:Ny-1] * (old_ku[i+1, 2:Ny, k] - old_ku[i+1, 0:Ny-2, k] - old_ku[i-1, 2:Ny, k] + old_ku[i-1, 0:Ny-2, k]) \
                             / (hx[i-1] * hy[1:Ny-1] + hx[i] * hy[1:Ny-1] + hx[i] * hy[0:Ny-2] + hx[i-1] * hy[0:Ny-2]) \
                             + 1/3 * rho_zx * z_volatility * x_volatility * x[i] * z[k] * (old_ku[i+1, 1:Ny-1, k+1] - old_ku[i+1, 1:Ny-1, k-1] - old_ku[i-1, 1:Ny-1, k+1] +old_ku[i-1, 1:Ny-1, k-1]) \
                             / (hx[i-1] * hz[k] + hx[i] * hz[k] + hx[i] * hz[k-1] + hx[i-1] * hz[k-1]) \
                             + 1/3 * rho_yz * y_volatility * z_volatility * y[1:Ny-1] * z[k] * (old_ku[i, 2:Ny, k+1] - old_ku[i, 2:Ny, k-1] - old_ku[i, 0:Ny-2, k+1] + old_ku[i, 0:Ny-2, k-1]) \
                             / (hy[0:Ny-2] * hz[k] + hy[1:Ny-1] * hz[k] + hy[1:Ny-1] * hz[k-1] + hy[0:Ny-2] * hz[k-1]) + old_ku[i, 1:Ny-1, k]/dt
                ku[i, 1:Ny-1, k] = tho.thomas(ay, dy, cy, fy)
        ku[1:Nx - 1, 1:Ny - 1, Nz - 1] = 2 * ku[1:Nx - 1, 1:Ny - 1, Nz - 2] - ku[1:Nx - 1, 1:Ny - 1, Nz - 3]
        ku[Nx - 1, 1:Ny - 1, 1:Nz] = 2 * ku[Nx-2, 1:Ny - 1, 1:Nz] - ku[Nx - 3, 1:Ny - 1, 1:Nz]
        ku[1:Nx, Ny - 1, 1:Nz] = 2 * ku[1:Nx, Ny - 2, 1:Nz] - ku[1:Nx, Ny-3, 1:Nz]

        for j in range(1, Ny-1):
            for i in range(1, Nx-1):
                fz[0:Nz-1] = 1/3 * rho_xy * x_volatility * y_volatility * x[i] * y[j] * ((ku[i+1, j+1, 1:Nz-1] - ku[i+1, j-1, 1:Nz-1] - ku[i-1, j+1, 1:Nz-1] + ku[i-1, j-1, 1:Nz-1]) \
                             / (hx[i-1] * hy[j] + hx[i] * hy[j] + hx[i] * hy[j-1] + hx[i-1] * hy[j-1])) \
                             + 1/3 * rho_zx * z_volatility * x_volatility * x[i] * z[1:Nz-1] * ((ku[i+1, j, 2:Nz] - ku[i+1, j, 0:Nz-2] - ku[i-1, j, 2:Nz] + ku[i-1, j, 0:Nz-2]) \
                             / (hx[i-1] * hz[1:Nz-1] + hx[i] * hz[1:Nz-1] + hx[i] * hz[0:Nz-2] + hx[i-1] * hz[0:Nz-2]) )\
                             + 1/3 * rho_yz * y_volatility * z_volatility * y[j] * z[1:Nz-1] * ((ku[i, j+1, 2:Nz] - ku[i, j+1, 0:Nz-2] - ku[i, j-1, 2:Nz] + ku[i, j-1, 0:Nz-2]) \
                             / (hy[j-1] * hz[1:Nz-1] + hy[j] * hz[1:Nz-1] + hy[j] * hz[0:Nz-2] + hy[j-1] * hz[0:Nz-2]) + ku[i, j, 1:Nz-1])
                old_ku[i, j, 1:Nz-1] = tho.thomas(az, dz, cz, fz)
        old_ku[1:Nx - 1, 1:Ny - 1, Nz - 1] = 2 * old_ku[1:Nx - 1, 1:Ny - 1, Nz - 2] - old_ku[1:Nx - 1, 1:Ny - 1, Nz - 3]
        old_ku[Nx - 1, 1:Ny - 1, 1:Nz] = 2 * old_ku[Nx - 2, 1:Ny - 1, 1:Nz] - old_ku[Nx - 3, 1:Ny - 1, 1:Nz]
        old_ku[1:Nx, Ny - 1, 1:Nz] = 2 * old_ku[1:Nx, Ny - 2, 1:Nz] - old_ku[1:Nx, Ny - 3, 1:Nz]

        ku = old_ku



    working_time = time.time()-start

    print("Pricing time for 3 assets : %f"%(working_time))

    # X, Y = np.meshgrid(x, y)
    # kk = np.argwhere(z == 100)
    # fig1 = plt.figure()
    # ax = fig1.gca(projection='3d')
    # ax.plot_surface(X, Y, u[:, :, int(kk)], cmap=plt.cm.gray)
    # ax.view_init(elev=30, azim=-132)
    # ax.set_xlabel('x', fontsize=10)
    # ax.set_ylabel('y', fontsize=10)
    # ax.zaxis.set_rotate_label(False)
    # ax.set_zlabel('ELS Price', rotation=90, fontsize=10)
    #
    # fig2 = plt.figure()
    # bx = fig2.gca(projection='3d')
    # bx.plot_surface(X, Y, ku[:, :, int(kk)], cmap=plt.cm.gray)
    # bx.view_init(elev=30, azim=-132)
    # bx.set_xlabel('x', fontsize=10)
    # bx.set_ylabel('y', fontsize=10)
    # bx.zaxis.set_rotate_label(False)
    # bx.set_zlabel('ELS Price', rotation=90, fontsize=10)
    #
    # plt.show()

    ii = np.where(x == 100)
    jj = np.where(y == 100)
    kk = np.where(z == 100)

    return u[ii, jj, kk][0][0]


if __name__ == '__main__':
    print(calculate_three_assets())