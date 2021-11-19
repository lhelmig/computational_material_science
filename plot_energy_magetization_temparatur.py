import matplotlib.pyplot as plt
import numpy as np
import os


x=np.loadtxt("beta_energy+magnetization_B=0.000000_J=1.000000.txt")
y = x.astype(float)

energy = np.zeros(len(y))
magnetization = np.zeros(len(y))
beta = np.zeros(len(y))
                
                
for i in range(len(y)):
    beta[i] = y[i][0]
    energy[i] = y[i][1]
    magnetization[i] = y[i][2]
    
f1 = plt.figure()
plt.plot(beta,energy)
plt.xlabel("Beta")
plt.ylabel("Energy")
plt.savefig("plot_energy.pdf")

f2 = plt.figure()
plt.plot(beta,magnetization)
plt.xlabel("Beta")
plt.ylabel("Magnetization")
plt.savefig("plot_magnetisation.pdf")
