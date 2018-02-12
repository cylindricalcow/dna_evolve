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

void Sequence::test(){
    vector<int> seq_vec=get_current_seq();
    seq_vec[0]=5;
    cout<<seq_vec[0]<<endl;
    return;
}

float Sequence::RandFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

double Sequence::RandDouble(double a, double b) {
    double random = ((double) rand()) / (double) RAND_MAX;
    double diff = b - a;
    double r = random * diff;
    return a + r;
}

int Sequence::RandInt(int nuc) {
    //nuc is 1 for A, 2 for T, 4 for G, 5 for C [A,T,G,C] maps to [0,1,2,3] for idx
    //int idx_num;

    vector<int> nucs={1,2,4,5};
    int r =rand() % 4; 
    
    if (nucs[r]!= nuc) return nucs[r];
   
    else return nucs[(r+1)%L];
}

vector<int> Sequence::get_current_seq(){
    return current_seq;
}
void Sequence::set_seq(vector<int> vec){
    current_seq=vec;
    return;
}
vector<int> Sequence::init_seq(){
    vector<int> i_seq(L);
    for (int i=0; i<(int)i_seq.size(); i++) i_seq[i]=1;
    
    current_seq=i_seq;

    return i_seq;    
}

void Sequence::updateBJ(float newBJ){
    BJ=newBJ;
    vector<int> i_seq=init_seq();
    return;
}

int Sequence::get_NN(int idx){
    //NN are to the right and down (idx+1,idx-ncells)
    vector<int> seq_vec=get_current_seq();
    int NN;  
    
    NN=seq_vec[(idx+1)%L];

    return NN;
}

int Sequence::totE(){
    vector<int> seq_vec=get_current_seq();
    int Etot=0;
    int NN;
      
    for (int i=0; i<=(int)seq_vec.size(); i+=2)
    {    
        NN=get_NN(i); 
        int og = seq_vec[i];
        int val= abs(og-NN);
        if (val==0) Etot+=e_n;
        else if (val==1) Etot+=e_g;
        else if (val>1) Etot+=e_b;       
    }
    return Etot;   
}

int Sequence::totM2(){
    //A=1=(1,0), T=2=(-1,0), G=4=(0,i),C=5=(0,-i). Therefore max m^2 is 2.
    vector<int> seq_vec=get_current_seq();
    int Mtot=0;
    int NN;
    vector<int> NN_c1(2);
    vector<int> NN_c2(2); 
    vector<int> NN_c(2); 
    int og;
    for (int i=0; i<=(int)seq_vec.size(); i+=2)
    {   
        og=seq_vec[i];
        NN=get_NN(i);
        
        if (og==1) NN_c1={1,0};
        else if (og==2) NN_c1={-1,0};
        else if (og==4) NN_c1={0,1};
        else if (og==5) NN_c1={0,-1};

        if (NN==1) NN_c2 ={1,0};
        else if (NN==2) NN_c2={-1,0};
        else if (NN==4) NN_c2={0,1};
        else if (NN==5) NN_c2={0,-1};
        NN_c[0]=NN_c1[0]+NN_c2[0];
        NN_c[1]=NN_c1[1]+NN_c2[1];
        int accum=0;
        for (int hi = 0; hi < 2; hi++) accum += NN_c[hi] * NN_c[hi];
        Mtot+=accum;
    }
    return Mtot/L;   
}

void Sequence::update_seq(int idx){
    //Need to fix!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //NN are to the right
    vector<int> seq_vec=get_current_seq(); 
    int value=seq_vec[idx];
    seq_vec[idx]=value*-1;
    current_seq=seq_vec;
    return;
}
void Sequence::alpha(){
    vector<int> seq_vec=get_current_seq();
    int attempt=rand()% ((int)seq_vec.size());
    float BJ=getBJ();
    int E_old=totE();
    float prob = RandFloat(0,1); 
    ///Choose insert or transform
    float method = RandFloat(0,1);
    
    if (method>=0.5)             ////transform
    {
        int new_val=RandInt(attempt);
        
        vector<int> copy1= seq_vec;
        copy1[attempt]=new_val;
        int Etot1=0;
        for (int i=0; i<=(int)copy1.size(); i+=2)
        {    
            int NN=copy1[(i+1)%L]; 
            int og = copy1[i];
            int val= abs(og-NN);
            if (val==0) Etot1+=e_n;
            else if (val==1) Etot1+=e_g;
            else if (val>1) Etot1+=e_b;       
        }
        float alpha=exp(-1*BJ*E_old)/exp(-1*BJ*Etot1);
        
        if ((alpha < 1)&&(alpha>=prob)) {
            set_seq(copy1);
            return;}
        else if ((alpha < 1)&&(alpha<prob)) return;
        else if (alpha>=1) {
            set_seq(copy1);
            return;}        
    }
    else
    {
          ///////insert and remove
         vector<int> copy1= seq_vec;
         int attempt2=rand()% ((int)seq_vec.size()); ///insert
         int new_val2=RandInt(attempt2);
         
         int attempt3=rand()% ((int)seq_vec.size()); ///remove
         if ((attempt==attempt2) or (attempt==attempt3) or (attempt2==attempt3)) return;
         else 
         {
             vector<int> new_vec(L);    
             for (int j=0; j<(int)copy1.size();j++) 
             {
                 if ((j!=attempt2) or (j!=attempt3)) new_vec.push_back(copy1[j]);
                 else if (j==attempt2) new_vec.push_back(new_val2);
                 else if (j==attempt3) continue;                
             }
             int Etot2=0;
             for (int w=0; w<=(int)new_vec.size(); w+=2)
             {    
                int NN2=new_vec[(w+1)%L]; 
                int og2 = new_vec[w];
                int val2= abs(og2-NN2);
                if (val2==0) Etot2+=e_n;
                else if (val2==1) Etot2+=e_g;
                else if (val2>1) Etot2+=e_b;       
             }
             float alpha=exp(-1*BJ*E_old)/exp(-1*BJ*Etot2);
             
             if ((alpha < 1)&&(alpha>=prob)) {
                 set_seq(new_vec);
                 return;}
             else if ((alpha < 1)&&(alpha<prob)) return;
             else if (alpha>=1) {
                 set_seq(new_vec);
                 return;}
         }   
    }
    
    
}


string Sequence::get_seq_str(){
    vector<int> v=get_current_seq(); 
    //for (int q=0;q<(int)v.size();q++) cout<<" "<<v[q]<<" ";
    stringstream ss;
    copy( v.begin(), v.end(), ostream_iterator<int>(ss, " "));
    string s = ss.str();
    s = s.substr(0, s.length()-1);
    return s;

    //old method
    /*
    string bit_str;
    for (int why=0; why<int(seq_vec.size());why++)
    {
        
        if (seq_vec[why]==1) bit_str+=" 1 ";
        else if (seq_vec[why]==2) bit_str+=" 2 ";
        else if (seq_vec[why]==4) bit_str+=" 4 ";
        else if (seq_vec[why]==5) bit_str+=" 5 ";
    }
    //cout<<bit_str<<endl;
    //cout<<bit_str.size()<<endl;
    //int config_num = stoi(bit_str, nullptr, 2);
    return bit_str;
    */
}



