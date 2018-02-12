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
int main(){
    int L1;
    cout << "Please enter length of sequence (int) \n";
    cin >> L1;

    float BJ1;
    cout << "Please enter BJ value (float) \n";
    cin >> BJ1;

    int iterations1;
    cout << "Please enter iterations for MCMC (int) \n";
    cin >> iterations1;
    /*
    bool animate;
    cout << "Do you want to save snapshots for animation? (boolean) \n";
    cin >> animate;
    */
    Sequence state1(L1,BJ1,iterations1);

    vector<int> i_seq=state1.init_seq(); 
    ofstream out;
    ofstream out2;
    ofstream out3;
    out.open("/home/jtrichm2/Evolution/nuc_"+to_string(L1)+"_beta_"+to_string(BJ1)+"_iterations_"+to_string(iterations1)+".txt", ios::app);
    out3.open("/home/jtrichm2/Evolution/nuc_"+to_string(L1)+"_beta_"+to_string(BJ1)+"_iterations_"+to_string(iterations1)+"_m2.txt", ios::app);
    string str="/home/jtrichm2/Evolution/sequences/anim_";
    for (int iters=0; iters<iterations1;iters++)
    {
        
        state1.alpha();   
        cout<<"iteration of: "<<iters<<endl;
        int spacing=iterations1/100;
        if (iters%spacing==0){
            
            int E=state1.totE();
            float m2=state1.totM2();
            cout<<"Energy: "<< E<<endl;
            out << iters << " " << E << "\n";
            out3 << iters << " " << m2 << "\n";
            string str_new=str;
            str_new+=to_string(iters);
            str_new+=".txt";
            out2.open(str_new);
            out2 <<state1.get_seq_str();
            
        }  
        out2.close();
       
    }
    out.close(); 
    out3.close();
    return 0;
}

/*
int main(){energy();
}
*/
