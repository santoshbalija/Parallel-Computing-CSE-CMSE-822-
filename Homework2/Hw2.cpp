
#include <iostream>
using std::cout;
using std::endl;
#include <random>
using std::mt19937_64;
using std::uniform_int_distribution;
using std::random_device;
#include<chrono>
using std::chrono::milliseconds;
#include<ctime>
int main(){
    const int n=5000;
   random_device rd;
    mt19937_64 dre(rd());
    long a[n][n];
    long b[n][n];
    long c[n][n];
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            uniform_int_distribution<long> dist(0,255);
            a[i][j]=dist(dre);
            b[i][j]=dist(dre);
        }
        }
    using duration = milliseconds;
    auto t1 = std::chrono::steady_clock::now();
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            for(int k=0;k<n;++k)
                c[i][j]+=a[i][k] * b[k][j];
        }
    }
    auto t2 = std::chrono::steady_clock::now();
    auto elapsed=std::chrono::duration_cast<duration>(t2-t1).count();
    cout << "Elapsed time is " << elapsed << " milliseconds."<<'\n';
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
           // cout<<c[i][j]<<endl;
        }
    }
}
