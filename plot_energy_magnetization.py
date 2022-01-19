import matplotlib.pyplot as plt
import numpy as np
import os
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)
from numpy.core.function_base import linspace

L=32

plt.rcParams["figure.figsize"] = (7, 4.5)

x=np.loadtxt("energy+magnetization_B=0.000000_J=1.000000_beta=0.500000.txt")
y = x.astype(float)

energy = np.zeros(len(y))
magnetization = np.zeros(len(y))
aU = 0
aM = 0

for i in range(len(y)):
    energy[i] = y[i][0]/(L*L)
    aU = aU + y[i][0]/(L*L)
    magnetization[i] = y[i][1]/(L*L)
    aM = aM + y[i][1]/(L*L)

aU = aU / len(y)
aM = aM / len(y)

x1=linspace(0,2000)
y1=linspace(aU,aU)
y2=linspace(aM,aM)

fig, axs = plt.subplots(2,1)

axs[0].plot(energy,'.')
axs[0].plot(x1,y1,'r')
axs[0].set_ylabel("U/n",fontsize=18)
axs[0].set_ylim(-0.37,-0.19)
axs[0].tick_params(axis='both', which='major', labelsize=12)
axs[0].yaxis.set_major_locator(MultipleLocator(0.05))
axs[0].xaxis.set_major_locator(MultipleLocator(500))
axs[0].yaxis.set_minor_locator(MultipleLocator(0.01))
axs[0].xaxis.set_minor_locator(MultipleLocator(50))
axs[0].grid(True)

axs[1].plot(magnetization,'.')
axs[1].plot(x1,y2,'r')
axs[1].set_xlabel("N",fontsize=18)
axs[1].set_ylabel("M/n",fontsize=18)
axs[1].set_ylim(-0.12,0.12)
axs[1].tick_params(axis='both', which='major', labelsize=12)
axs[1].yaxis.set_major_locator(MultipleLocator(0.05))
axs[1].xaxis.set_major_locator(MultipleLocator(500))
axs[1].yaxis.set_minor_locator(MultipleLocator(0.01))
axs[1].xaxis.set_minor_locator(MultipleLocator(50))
axs[1].grid(True)

plt.savefig("plot_magnetisation_energy.pdf",bbox_inches='tight')

print(aU)
input('5')
print(aM)
input('6')
