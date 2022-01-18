import matplotlib.pyplot as plt
import numpy as np
import os

plt.style.use(os.path.join(os.path.abspath(os.getcwd()), "CSthesis.mplstyle"))
plt.rcParams['text.latex.preamble'] = r"\usepackage{lmodern}"
# Options
params = {'font.family': 'lmodern'}
plt.rcParams.update(params)


y=np.loadtxt("prob_distr_magnetization_N=98975_beta=0.500000_B=0.000000_J=1.000000.txt")
x=np.loadtxt("prob_distr_magnetization_N=98975_beta=0.880000_B=0.000000_J=1.000000.txt")
z=np.loadtxt("prob_distr_magnetization_N=98975_beta=1.000000_B=0.000000_J=1.000000_one_side.txt")

w=np.loadtxt("prob_distr_magnetization_N=98975_beta=1.000000_B=0.000000_J=1.000000.txt")

magnetization1 = np.zeros(len(y))
prob1 = np.zeros(len(y))
magnetization2 = np.zeros(len(x))
prob2 = np.zeros(len(x))
magnetization3 = np.zeros(len(z))
prob3 = np.zeros(len(z))
magnetization4 = np.zeros(len(w))
prob4 = np.zeros(len(w))
                
                
for i in range(len(y)):
    magnetization1[i] = float(y[i][0])
    prob1[i] = float(y[i][1])
for i in range(len(x)):
    magnetization2[i] = float(x[i][0])
    prob2[i] = float(x[i][1])
for i in range(len(z)):
    if float(z[i][0])<=0:
        magnetization3[i] = float(z[i][0])
        prob3[i] = float(z[i][1])
for i in range(len(w)):
    if float(w[i][0]) >=0:
        magnetization4[i] = float(w[i][0])
        prob4[i] = float(w[i][1])
        
norm = np.sum(prob1)
prob1 = np.divide(prob1,norm)
norm = np.sum(prob2)
prob2=np.divide(prob2,norm)
norm = np.sum(prob3)
norm += np.sum(prob4)
prob3 = np.multiply(prob3,1/norm)
prob4 = np.multiply(prob4,1/norm)

    
   
fig, ax = plt.subplots()
plt.plot(np.divide(magnetization1,512),np.multiply(prob1,512),'.',label=r'$\beta = 0.5$',markersize=2)
plt.plot(np.divide(magnetization2,512),np.multiply(prob2,512),'.',label=r'$\beta = 0.88 \approx T_C$',markersize=2)
plt.plot(np.divide(magnetization3,512),np.multiply(prob3,512),'.',label=r'$\beta = 1$',markersize=2)
plt.plot(np.divide(magnetization4,512),np.multiply(prob4,512),'.',color="tab:green",markersize=2)
plt.xlim(-1,1)
plt.xlabel("Average magnetization per site",fontsize=18)
plt.ylabel("Probability density",fontsize=18)
#plt.rc('legend',fontsize=12)
#ax.legend()
#ax.legend(markerscale=10)
#plt.xticks([-512,-256,0,256,512],["-1.0","-0.5","0.0","0.5","1.0"])
plt.xticks(fontsize=12)
plt.yticks(fontsize=12)
plt.savefig("plot_prob_distr_magnetization.pdf",bbox_inches='tight')
plt.show()
