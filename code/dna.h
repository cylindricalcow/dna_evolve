#ifndef DNA_H_

#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <random>
#include <time.h>
#include <algorithm>
#include <fstream> 

using namespace std;
class Sequence 
{
    private:
        vector<int> current_seq;              //vec of current state w len=ncells^ndims
        //int ndims;                              //like 2d or 3d
        int L;                             //length of sequence must be even
        int e_g;				//favorable bond energy
        int e_n;				//neutral bond energy
        int e_b;				//unfavorable bond energy
        int iterations;                         //times to run MCMC
        float BJ;                                 //B*J   
    public:
        void test();           //test to see if modding state_vec changes current_state (it doesn't)
        int totE();                             //calc sum(si*sj) for NN_ij of state vector
        int totM2();           //analog of m2 where A=(1,0), T=(-1,0), G=(0,i),C=(0,-i). Calc only with NN then sum square            
        vector<int> init_seq();            //intialize vector with length n^2 
        void update_seq(int);                 //update state of cell by flipping state
        vector<int> get_current_seq();            //get vector of current state
        int get_NN(int);                //get nearest neighbors for a cell
        void alpha();                    //compute prob of transition for 2 diff states
        int seq_swap();                       //find new state to try to swap
        void updateBJ(float);
        float RandFloat(float, float);  
        double RandDouble(double, double);  
        int RandInt(int);
        void set_seq(vector<int>); 
        string get_seq_str();     
             
        Sequence(int L1, float BJ1, int iterations1)
        {
            L=L1;
            
            BJ=BJ1;
            iterations=iterations1;
            srand(time(NULL));
            current_seq=init_seq();
            e_g=-1;
            e_b=1;
            e_n=0;
	    
        }
        int getL()
        {
            return L;
        }
        float getBJ()
        {
            return BJ;
        }
        int getIterations()
        {
            return iterations;
        }
        
};
#endif
