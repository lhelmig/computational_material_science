import matplotlib.pyplot as plt
import numpy as np
import os

L = 32

f=open("states_B=0.000000_J=1.000000_beta=1.200000.txt","r")

lines=f.readlines()

path=os.getcwd()

print(path)

if len(lines)!=1:
    try:
        os.mkdir(path+"/step_plots")
    except FileExistsError:
        print("directory exists")

for index,line in enumerate(lines):
    
    state = line.split()
    
    fig, ax = plt.subplots()
    
    for i in range(0,len(state)):
        
        width = i % L
        height = int(i/L)
        
        #ax.tick_params(labelleft=False, labeldown=False)
        
        if(state[i] == '0.5'):
            plt.plot(width,height,'s',color="tab:blue")
        else:
            plt.plot(width,height,'s',color="tab:orange")
    
    #plt.xlabel("Position",fontsize=16)
    #plt.ylabel("Position",fontsize=16)
    plt.axis('off')
    if(len(lines)==1):
        plt.savefig("state.pdf",bbox_inches = 'tight')
    else:
        plt.savefig("step_plots/step_"+"%02d" % (index,)+"_state.pdf",bbox_inches = 'tight')