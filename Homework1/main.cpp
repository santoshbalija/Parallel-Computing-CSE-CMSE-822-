//
//  main.cpp
//  Homework1-CMSE822-Parallel Computing
//
//  Created by Balija SantoshKumar on 9/14/21.
//

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <chrono>


using std::mt19937_64; using std::uniform_int_distribution; using std::random_device;
int main()
{
    // Generate data
    const unsigned arraySize = 100000;//256;//32768; 
    int data[arraySize];
	random_device rd;//to generate seed for merene twister
	
	mt19937_64 rng(rd()); //merene twister 
	
	uniform_int_distribution<long> dist(0,256); // to bound the distribution
	
    for (unsigned c = 0; c < arraySize; ++c)
        data[c] = dist(rng) % 256;
     //data[c] = std::rand() % 256;
     
    // !!! With this, the next loop runs faster.
    std::sort(data, data + arraySize); // Sorting

    // Test cases
   using duration = std::chrono::milliseconds;  
	  auto tstart = std::chrono::steady_clock::now();//clock start
    long long sum = 0;
    for (unsigned i = 0; i < 100000; ++i)
    {
        for (unsigned c = 0; c < arraySize; ++c)
        {   // Primary loop
            if (data[c] >= 128)
                sum += data[c];
        }
    }

   auto tend = std::chrono::steady_clock::now(); //clock end

  auto elapsed = std::chrono::duration_cast<duration>(tend-tstart).count();
  std::cout << "Time: "<<elapsed<<" ms"<<std::endl;

    std::cout << "sum = " << sum << '\n';
}
