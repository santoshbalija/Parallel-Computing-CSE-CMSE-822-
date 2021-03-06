//  main.cpp
//  HW2
//
//  Created by Rachel Roca on 9/21/21.
//
#include <iostream>
using std::cout;
using std::endl;
#include <random>
using std::mt19937_64;
using std::uniform_int_distribution;
using std::random_device;
#include<chrono>
using std::chrono::milliseconds;
using std::chrono::nanoseconds;
#include<ctime>
#include <vector>
using std::vector;
int main(){
    double sum =  0;
    double average = 0;
    const int n=3;
    random_device rd;
    mt19937_64 dre(rd());
    for (int l=0; l<1;l++)
    {
    int *a = (int *)malloc(n*n*sizeof(int));
    int *b = (int *)malloc(n*n*sizeof(int));
    int *c = (int *)malloc(n*n*sizeof(int));
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            uniform_int_distribution<int> dist(0,1);
            a[n*i+j]=dist(dre);
            b[n*i+j]=dist(dre);
            c[n*i+j]=0;
        }
        for(int k =0;k<9;++k){
            cout<<a[k]<<endl;
            //cout<<b[k]<<endl;
            
        }
    using duration = milliseconds;
    auto t1 = std::chrono::steady_clock::now();
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            for(int k=0;k<n;++k)
                c[i*n+j]+=a[i*n + k] * b[k + n*j];
        }
    }
    auto t2 = std::chrono::steady_clock::now();
    auto elapsed=std::chrono::duration_cast<duration>(t2-t1).count();
   // cout << "Elapsed time is" << elapsed << " milliseconds."<<'\n';
        sum+=elapsed;
    for(int k =0;k<(n^2);++k){
        //cout<<*c<<endl;
        //c++;
    }
    
    average =sum/5;
   // cout << "Average elapsed time is " << average << " milliseconds."<<'\n';
    
}
    }
}
