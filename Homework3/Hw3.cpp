//
//  main.cpp


#include <atomic>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

using std::atomic;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;
using std::cout;
using std::endl;
using std::mt19937_64;
using std::mutex;
using std::random_device;
using std::thread;
using std::uniform_real_distribution;
using std::vector;

mutex m;

void cal_function(int s, atomic<size_t> &nc){
    // std::lock_guard<mutex> lk(m);
    uniform_real_distribution<double> distribution(-1.0,1.0);
    double x;double y; double d;
    std::random_device rd;
    mt19937_64 dre(rd());

    for(int i=0;i<s;++i){
      x=distribution(dre);
      y=distribution(dre);
      //cout<<x<<endl;
      //cout<<y<<endl;
      d=pow(x,2)+pow(y,2);
      //cout<<d<<endl;
      if (d<=1){
        ++nc;
      }
    }

    cout<<"Top"<<nc<<endl;
}

int main (int argc, char *argv[2]){
  if (argc != 3)
      cout << "Required Arguements: Number of iterations (in total) and number of threads" << endl;
  else{
      using duration = milliseconds;
      double pi_est;
      double n;
      atomic<size_t> nc ;
      n=atof(argv[1]);
      cout<<"Iteration Count: "<<n<<endl;
      nc=0;
      int t_cnt = atoi(argv[2]);
      cout<<"Thread Count: "<<t_cnt<<endl;
      vector<thread> thrds;
      int s = n/t_cnt;
      cout<<"Iteration Count Divided: "<<s<<endl;
      auto t1 = std::chrono::steady_clock::now();
      for(unsigned int i = 0; i < t_cnt; ++i){
        thrds.emplace_back(cal_function,s,std::ref(nc));
        cout << "Starting: "<< i << endl;
        //cout<<d<<endl;
        //cout<<nc<<endl;
      }
      int id=0;
      for(auto &t : thrds){
        if(t.joinable() ){
          t.join();
          //cout << "Joined: "<< id++ << endl;
        }
      }
      auto t2 = std::chrono::steady_clock::now();
      cout<<"Bottom"<< nc<<endl;
      pi_est=4*nc/n;
      cout<< "The value of Pi is " << pi_est <<endl;
      auto elapsed=std::chrono::duration_cast<duration>(t2-t1).count();
      cout << "Elapsed time is " << elapsed << " milliseconds."<<'\n';
    }
}
