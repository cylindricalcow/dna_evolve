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
seq_plot=True
if seq_plot:
    os.chdir('/home/jtrichm2/Evolution/sequences/')
    for f in glob.iglob('*.txt'):
        states=np.genfromtxt(f) 
        states=states[states != 0]
        L=len(states)
        state=np.reshape(states,(L/50,50),'C')
        plt.matshow(state)
        plt.savefig('/home/jtrichm2/Evolution/Pictures/step_'+f[5:-4]+'.png')
        plt.close()
    
       
    os.chdir('/home/jtrichm2/Evolution/')

plot_e=False
if plot_e:
    nuc='1000'
    step='01'
    df = pd.read_csv("/home/jtrichm2/Evolution/nuc_"+nuc+"_beta_"+step+"_2.txt", sep=" ", names=['steps','Energy'])

    plt.plot(df['steps'],df['Energy'])
    plt.xticks(np.arange(0,3500,350))
    plt.xlabel('Steps')
    plt.ylabel('Energy')
    plt.title(nuc+' nucleotides with Beta='+step)
    plt.savefig('/home/jtrichm2/Evolution/'+nuc+'_nuc_'+step+'_beta_2.png')
    plt.show()

plot_m2=False
if plot_m2:
    df = pd.read_csv("/home/jtrichm2/PHYS498/project2/csv/m2_corr.txt", sep=" ", names=['steps','m2'])
    plt.plot(df['steps'],df['m2'])
    #plt.xticks(np.arange(0,100,5))
    plt.xlabel('Steps')
    plt.ylabel('m2')
    plt.title('20x20 lattice with Beta=0.25')
    plt.savefig('/home/jtrichm2/PHYS498/project2/m2_vs_iterations.png')
    plt.show()

plot_configs=False

if plot_configs:
    df = pd.read_csv("/home/jtrichm2/PHYS498/project2/csv/5_configs_bj_0.25_2.txt", sep=" ", names=['steps','config'])
    plt.hist(df['config'], bins=50)
    #plt.xticks(np.arange(0,512,5))
    plt.xlabel('Configuration')
    plt.ylabel('Count')
    plt.xlim(0,512)
    plt.title('3x3 lattice with Beta=0.25')
    plt.savefig('/home/jtrichm2/PHYS498/project2/plots/configs/5_steps_config_bj_0.25_2.png')
    plt.show()

    df = pd.read_csv("/home/jtrichm2/PHYS498/project2/csv/50_configs_bj_0.25_2.txt", sep=" ", names=['steps','config'])
    plt.hist(df['config'], bins=50)
    #plt.xticks(np.arange(0,512,5))
    plt.xlabel('Configuration')
    plt.xlim(0,512)
    plt.ylabel('Count')
    plt.title('3x3 lattice with Beta=0.25')
    plt.savefig('/home/jtrichm2/PHYS498/project2/plots/configs/50_steps_config_bj_0.25_2.png')
    plt.show()

    df = pd.read_csv("/home/jtrichm2/PHYS498/project2/csv/500_configs_bj_0.25_2.txt", sep=" ", names=['steps','config'])
    plt.hist(df['config'], bins=50)
    #plt.xticks(np.arange(0,512,5))
    plt.xlim(0,512)
    plt.xlabel('Configuration')
    plt.ylabel('Count')
    plt.title('3x3 lattice with Beta=0.25')
    plt.savefig('/home/jtrichm2/PHYS498/project2/plots/configs/500_steps_config_bj_0.25_2.png')
    plt.show()    


plot_snap=False
if plot_snap:
    os.chdir('/home/jtrichm2/PHYS498/project2/csv/steps_0.4/')
    for f in glob.iglob('*.txt'):
        states=np.genfromtxt(f) 
        print(f[6:-3])
        state=np.reshape(states,(81,81))
        plt.matshow(state)
        plt.savefig('/home/jtrichm2/PHYS498/project2/plots/cg_none/steps_0.4/step_'+f[6:-3])
        plt.close()
    os.chdir('/home/jtrichm2/PHYS498/project2/')
plot_betacrit=False
if plot_betacrit:
    '''
    df = pd.read_csv('/home/jtrichm2/PHYS498/project2/csv/beta_crit.txt', sep=" ", names=['beta','m2'])
    print(df.head())
    plt.plot(df['beta'],df['m2'])
    plt.xlabel('Beta')
    plt.xticks(np.arange(0,3,0.1))
    plt.ylabel('average m^2')
    plt.title('Critical Beta for 20x20 grid with  40,000 steps')
    plt.savefig('/home/jtrichm2/PHYS498/project2/plots/beta_crit2.png')
    plt.show()    
    '''
    os.chdir('/home/jtrichm2/PHYS498/project2/csv/beta_crit2/')
    
    avg2_m2=np.zeros(61)
    Bs=np.arange(0.00,3.05,0.05)
    for i in range(12):
        avg_m2=[]
        for f in glob.iglob('*_'+str(i)+'.txt'):
            df = pd.read_csv(f, sep=" ", names=['steps','m2'])
            avg_m2.append(np.mean(np.array(df['m2'])))
        for k in range(len(avg_m2)):
            avg2_m2[k]+=avg_m2[k]
        #avg2_m2.append(avg_m2)
    #print(avg2_m2)
    #avg_m2=np.mean(avg2_m2, axis=0)
    avg_m2=[x/11 for x in avg2_m2]
    print(len(avg_m2))
    print(len(Bs))
    plt.plot(Bs,avg_m2)
    plt.xlabel('Beta')
    plt.xticks(np.arange(0,3,0.1))
    plt.ylabel('average m^2')
    plt.title('Critical Beta for 20x20 grid with  40,000 steps')
    plt.savefig('/home/jtrichm2/PHYS498/project2/plots/beta_crit4.png')
    plt.show()    
    
