import numpy as np
import matplotlib.pyplot as plt
from scipy.linalg import solve


N = 20  # Number of nodes
L = 1.0 # Length in meters
k = 0.4 # Thermal conductivity
h = 20.01 # Convection coefficient
T_0 = 300 # Temperature at left wall in Kelvin
T_inf = 273.15 # Temperature of the fluid in Kelvin

# Domain discretization
dx = L / N
T = np.linspace(T_0, T_inf, N + 1)
x = np.linspace(0, L, N + 1)
N = len(T) - 1  # Set to index of last element

def residual(T):
    R = np.zeros(N + 1)
    R[0] = T[0] - T_0
    for i in range(1, N):
        R[i] = (T[i - 1] - 2 * T[i] + T[i + 1]) / dx**2
    R[N] = k * (T[N] - T[N-1]) / dx - h * (T[N] - T_inf)  # Non-linear boundary condition at x=L
    return R

def jacobian(T):
    J = np.zeros((N + 1, N + 1))
    J[0, 0] = 1.0
    for i in range(1, N):
        J[i, i - 1] = 1.0 / dx**2
        J[i, i] = -2.0 / dx**2
        J[i, i + 1] = 1.0 / dx**2
    J[N, N - 1] = -k / dx
    J[N, N] = k / dx - h
    return J


tol = 1e-9
max_it = 100

for it in range(max_it):
    r = residual(T)
    j = jacobian(T)
    delta_T = solve(j, -r)
    print(T)
    T += delta_T
    
    if np.linalg.norm(delta_T) < tol:
        print(f'Converged in {it + 1} iterations')
        break
else:
    print('Did not converge')

print('Temperature distribution')
print(T)
plt.figure()
plt.plot(x, T, '--bo', label='Temperature Distribution')
plt.grid(axis='both')
plt.ylabel('Temperature')
plt.xlabel('Distance')

# Save the figure as a png
plt.savefig('temp_dist.png')
plt.show()