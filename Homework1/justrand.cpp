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

int main()
{
    // Generate data
    const unsigned arraySize = 32768;
    int data[arraySize];
	
    for (unsigned c = 0; c < arraySize; ++c)
        
     data[c] = std::rand() % 256;
 
    //std::sort(data, data + arraySize);

    // Test
   using duration = std::chrono::milliseconds;  
	  auto tstart = std::chrono::steady_clock::now();
    long long sum = 0;
    for (unsigned i = 0; i < 100000; ++i)
    {
        for (unsigned c = 0; c < arraySize; ++c)
        {   // Primary loop
            if (data[c] >= 128)
                sum += data[c];
        }
    }

   auto tend = std::chrono::steady_clock::now();

  auto elapsed = std::chrono::duration_cast<duration>(tend-tstart).count();
  std::cout << "Elapsed Time: "<<elapsed<<" ms"<<std::endl;

    std::cout << "sum = " << sum << '\n';
}
