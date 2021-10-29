import matplotlib.pyplot as plt
import numpy as np
import os

L = 32

#f=open("state.txt","r")

f=open("steps_state.txt","r")

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
        
        ax.tick_params(labeltop=True, labelright=True)
        
        if(int(state[i])==0):
            plt.plot(width,height,'.',color="tab:blue")
        else:
            plt.plot(width,height,'.',color="tab:orange")
            
    if(len(lines)==1):
        plt.savefig("state.png",bbox_inches = 'tight')
    else:
        plt.savefig("step_plots/step_"+str(index)+"state.png",bbox_inches = 'tight')
