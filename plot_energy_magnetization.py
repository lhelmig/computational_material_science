import matplotlib.pyplot as plt
import numpy as np
import os


x=np.loadtxt("energy+magnetization_B=0.000000_J=1.000000_beta=5.000000.txt")
y = x.astype(float)

energy = np.zeros(len(y))
magnetization = np.zeros(len(y))
for i in range(len(y)):
    energy[i] = y[i][0]
    magnetization[i] = y[i][1]
    
f1 = plt.figure()
plt.plot(energy)
plt.xlabel("Steps")
plt.ylabel("Energy")
plt.savefig("plot_energy_beta=0.9.pdf")

f2 = plt.figure()
plt.plot(magnetization)
plt.xlabel("Steps")
plt.ylabel("Magnetisation")
plt.savefig("plot_magnetisation_beta=0.9.pdf")

