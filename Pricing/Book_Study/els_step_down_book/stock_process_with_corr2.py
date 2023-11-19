import numpy as np
import matplotlib.pyplot as plt

x_vol = 0.079
y_vol = 0.105

r = 0.21

N = 100
T = 1

S1 = np.zeros((N+1, 1))
S2 = np.zeros((N+1, 1))

S1[0] = 100
S2[0] = 100

dt = T/N

t = np.linspace(0, T, N+1)

rho = 0.3

correlation = np.array([[1, rho], [rho, 1]])

cholesky = np.linalg.cholesky(correlation)

z0 = np.random.normal(0, 1, size=[N, 2])

np.random.seed(56)

z0 = np.transpose(z0)

z = np.matmul(cholesky, z0)

worst_performance = np.zeros((N+1, 1))

for i in range(N):
    S1[i+1] = S1[i] * np.exp((r-0.5*x_vol**2)*dt + x_vol*z[0, i]*np.sqrt(dt))
    S2[i+1] = S2[i] * np.exp((r-0.5*y_vol**2)*dt + y_vol*z[1, i]*np.sqrt(dt))
    worst_performance[i] = min(S1[i, 0], S2[i, 0])
    worst_performance[-1] = min(S1[-1, 0], S2[-1, 0])

plt.plot(t, S1[:], 'k-', label='asset1', linewidth=1, markersize=3.5)
plt.plot(t, S2[:], 'k--', label='asset2', linewidth=1, markersize=3.5)
#plt.plot(t, worst_performance[:], 'k+-', label='min(S1, S2)', linewidth=1, markersize=3.5)


plt.legend()
plt.xlim(0, 1.0)
plt.ylim(70, 130)
plt.xlabel('Time')
plt.ylabel('Stock Process')
plt.legend(prop={'size': 12})
plt.show()