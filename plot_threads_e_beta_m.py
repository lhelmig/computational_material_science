import matplotlib.pyplot as plt
import numpy as np
import os
import sys


np.set_printoptions(threshold=sys.maxsize)


x0=np.loadtxt("thread0_beta_energy+magnetization_B=0.000000_J=1.000000.txt")
x1=np.loadtxt("thread1_beta_energy+magnetization_B=0.000000_J=1.000000.txt")
x2=np.loadtxt("thread2_beta_energy+magnetization_B=0.000000_J=1.000000.txt")
x3=np.loadtxt("thread3_beta_energy+magnetization_B=0.000000_J=1.000000.txt")
x4=np.loadtxt("thread4_beta_energy+magnetization_B=0.000000_J=1.000000.txt")
x5=np.loadtxt("thread5_beta_energy+magnetization_B=0.000000_J=1.000000.txt")


y0 = x0.astype(float)
y1 = x1.astype(float)
y2 = x2.astype(float)
y3 = x3.astype(float)
y4 = x4.astype(float)
y5 = x5.astype(float)


energy = np.zeros(len(y0)+len(y1)+len(y2)+len(y3)+len(y4)+len(y5))
magnetization = np.zeros(len(y0)+len(y1)+len(y2)+len(y3)+len(y4)+len(y5))
beta = np.zeros(len(y0)+len(y1)+len(y2)+len(y3)+len(y4)+len(y5))


for i in range(len(y0)):
    beta[i] = y0[i][0]
    energy[i] = y0[i][1]
    magnetization[i] = y0[i][2]

for i in range(len(y1)):
    beta[i+len(y0)] = y1[i][0]
    energy[i+len(y0)] = y1[i][1]
    magnetization[i+len(y0)] = y1[i][2]
 
for i in range(len(y2)):
    beta[i+len(y0)+len(y1)] = y2[i][0]
    energy[i+len(y0)+len(y1)] = y2[i][1]
    magnetization[i+len(y0)+len(y1)] = y2[i][2]

for i in range(len(y3)):
    beta[i+len(y0)+len(y1)+len(y2)] = y3[i][0]
    energy[i+len(y0)+len(y1)+len(y2)] = y3[i][1]
    magnetization[i+len(y0)+len(y1)+len(y2)] = y3[i][2]
    
for i in range(len(y4)):
    beta[i+len(y0)+len(y1)+len(y2)+len(y3)] = y4[i][0]
    energy[i+len(y0)+len(y1)+len(y2)+len(y3)] = y4[i][1]
    magnetization[i+len(y0)+len(y1)+len(y2)+len(y3)] = y4[i][2]
    
for i in range(len(y5)):
    beta[i+len(y0)+len(y1)+len(y2)+len(y3)+len(y4)] = y5[i][0]
    energy[i+len(y0)+len(y1)+len(y2)+len(y3)+len(y4)] = y5[i][1]
    magnetization[i+len(y0)+len(y1)+len(y2)+len(y3)+len(y4)] = y5[i][2]


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