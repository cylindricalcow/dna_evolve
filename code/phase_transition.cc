#include "dna.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <random>
#include <time.h>
#include <algorithm>
#include <fstream> 
#include <functional>
#include <numeric>
#include <iomanip>
#include <map>
#include <math.h>
#include <iomanip>
#include <sstream>
#include<iterator>
#include <sys/stat.h>

using namespace std;

bool fileExists(const string& filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}


void phase_transition(){
    int L1;
    cout << "Please enter length of sequence (int) \n";
    cin >> L1;

    float BJ1;
    cout << "Please enter BJ value (float) \n";
    cin >> BJ1;

    int iterations1;
    cout << "Please enter iterations for MCMC (int) \n";
    cin >> iterations1;

    Sequence state1(L1,BJ1,iterations1);

    vector<int> i_seq=state1.init_seq();
    ofstream out;
    
    double bj_min;
    cout << "Please enter minimumum Beta to search over (double) (e.g. 0.14): \n";
    cin >> bj_min;

    double bj_max;
    cout << "Please enter maximum Beta to search over (double) (e.g. 0.17): \n";
    cin >> bj_max;

    double step;
    cout << "Please enter step size for beta search (double) (e.g. 0.05): \n";
    cin >> step;

    for (float Bstep=bj_max; Bstep>=bj_min; Bstep-=step)
    {
        cout<<"Bstep: "<<Bstep<<endl;
        string str="/home/jtrichm2/Evolution/"+to_string(L1)+"_L_iters_"+to_string(iterations1)+"/"+to_string(L1)+"_beta_crit_"+to_string(iterations1)+"_iters_"+to_string(Bstep)+".txt";
        cout<<str<<endl;
        if (fileExists(str)) out.open(str, ios::app);
        else out.open(str);
        //out.open(str, ios::app);
        //double m2_temp2=0;
        
        vector<int> i_seq=state1.init_seq();
        state1.updateBJ(Bstep);
        
        double m2_temp=0;
        for (int i=0; i<state1.getIterations();i++)
        {
            cout<<"B of: "<<Bstep<<" "<<i<<endl;
            state1.alpha();
            if ((i%50==0) and (i>(state1.getIterations()-500)))
            {
                int M2=state1.totM2();
                m2_temp+=M2;
            }   

        }
            
        double m2avg2=m2_temp/10.0;
        out << Bstep<<" "<<m2avg2<<endl;
        out.close();
    }
    return;
}
int main(){ phase_transition();

}
