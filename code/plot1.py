import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

import os
import sys
import glob
 
clean=False
if clean:
    os.chdir('/home/jtrichm2/Evolution/sequences/')
    for f in glob.iglob('*.txt'):    
        states=np.genfromtxt(f) 
        states=states[states != 0]
        l1=len(states)
        s=""
        for i in range(l1):
            s+=str(int(states[i]))+" "
        text_file = open(f, "w")
        text_file.write(s)
        text_file.close()   
seq_plot=False
if seq_plot:
    os.chdir('/home/jtrichm2/Evolution/sequences/B_03_L_100/')
    for f in glob.iglob('*.txt'):
        states=np.genfromtxt(f) 
        states=states[states != 0]
        L=len(states)
        state=np.reshape(states,(L/10,10),'C')
        plt.matshow(state)
        plt.savefig('/home/jtrichm2/Evolution/Pictures/B_03_L_100/0'+f[5:-4]+'.png')
        plt.close()
    
       
    os.chdir('/home/jtrichm2/Evolution/')

plot_e=True
if plot_e:
    nuc='100'
    step='03'
    iters='10000'
    df1 = pd.read_csv("/home/jtrichm2/Evolution/data/nuc_"+nuc+"_beta_"+step+"_iterations_"+iters+"_2.txt", sep=" ", names=['steps','Energy'])
    df2 = pd.read_csv("/home/jtrichm2/Evolution/data/nuc_"+nuc+"_beta_"+step+"_iterations_"+iters+"_m2.txt", sep=" ", names=['steps','m2'])
    plt.plot(df1['steps'],df1['Energy'])
    plt.xticks(np.arange(0,2000,200))
    plt.xlim(0,2000)
    plt.xlabel('Steps')
    plt.ylabel('Energy')
    plt.title(nuc+' nucleotides with Beta='+step)
    plt.savefig('/home/jtrichm2/Evolution/Pictures/'+nuc+'_nuc_'+step+'_beta_energy.png')
    plt.show()

    plt.plot(df2['steps'],df2['m2']/10)
    plt.xticks(np.arange(0,2000,200))
    plt.xlim(0,2000)
    plt.xlabel('Steps')
    plt.ylabel('m2')
    plt.title(nuc+' nucleotides with Beta='+step)
    plt.savefig('/home/jtrichm2/Evolution/Pictures/'+nuc+'_nuc_'+step+'_beta_m2.png')
    plt.show()
