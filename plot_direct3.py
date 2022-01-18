import matplotlib.pyplot as plt
import numpy as np
import os
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)
from numpy.core.function_base import linspace

plt.style.use(os.path.join(os.path.abspath(os.getcwd()), "CSthesis.mplstyle"))
plt.rcParams['text.latex.preamble'] = r"\usepackage{lmodern}"
# Options
params = {'font.family': 'lmodern'}
plt.rcParams.update(params)

L=32

plt.rcParams["figure.figsize"] = (7, 4.5)

x=np.loadtxt("beta_energy+magnetization_B=0.000000_J=1.000000.txt")
y = x.astype(float)
xi=np.loadtxt("data.txt")
yi = xi.astype(float)


t = np.zeros(len(yi))
U = np.zeros(len(yi))
energy = np.zeros(len(y))
magnetization = np.zeros(len(y))
beta = np.zeros(len(y))

for i in range(len(yi)):
    t[i] = yi[i][0]
    U[i] = yi[i][1]

for i in range(len(y)):
    energy[i] = y[i][1]/(L*L)
    magnetization[i] = abs(y[i][2]/(L*L))
    beta[i] = y[i][0]



J = 0.5

M = np.float_power(1-np.power(np.sinh(2*t*J),(-4)),1/8)/2

print(M)


fig, axs = plt.subplots(2,1)


axs[0].plot(beta,energy,'.')
axs[0].plot(t,U,'r')
axs[0].set_ylabel("U/n",fontsize=18)
axs[0].set_ylim(-1.05,0)
axs[0].set_xlim(0.15,2.05)
axs[0].tick_params(axis='both', which='major', labelsize=12)
axs[0].yaxis.set_major_locator(MultipleLocator(0.2))
axs[0].xaxis.set_major_locator(MultipleLocator(0.25))
axs[0].yaxis.set_minor_locator(MultipleLocator(0.05))
axs[0].xaxis.set_minor_locator(MultipleLocator(0.05))
axs[0].grid(True)

axs[1].plot(beta,magnetization,'.')
axs[1].plot(t,M,'r')
axs[1].set_xlabel(r'$\beta$',fontsize=18)
axs[1].set_ylabel("M/n",fontsize=18)
#axs[1].set_ylim(-1,1)
axs[1].set_ylim(-0.05,0.55)
axs[1].set_xlim(0.15,2.05)
axs[1].tick_params(axis='both', which='major', labelsize=12)
axs[1].yaxis.set_major_locator(MultipleLocator(0.1))
axs[1].xaxis.set_major_locator(MultipleLocator(0.25))
axs[1].yaxis.set_minor_locator(MultipleLocator(0.025))
axs[1].xaxis.set_minor_locator(MultipleLocator(0.05))
axs[1].grid(True)


plt.savefig("plot_magnetisation_energy_temp.pdf",bbox_inches='tight')