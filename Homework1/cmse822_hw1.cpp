#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <chrono>


using std::mt19937_64; using std::uniform_int_distribution; using std::random_device;

int main()
{
    // Generate data
    const unsigned arraySize = 32768;//256,1024,819232768;
    int data[arraySize];
	
	random_device rd;
	// seed with whatever the rd provides
	mt19937_64 prng(rd());
	// templated, defaults to int but you can use another int type
	// range of values are 0-244 inclusive
	uniform_int_distribution<long> dist(0,256);
	// distribution takes the prng as an arg
    
    for (unsigned c = 0; c < arraySize; ++c)
        data[c] = dist(prng) % 256;
        
    // !!! With this, the next loop runs faster.
    std::sort(data, data + arraySize);

    // Test
      // time the sort
	  using duration = std::chrono::milliseconds;  
	  auto t1 = std::chrono::steady_clock::now();
    long long sum_sort = 0;
    for (unsigned i = 0; i < 100000; ++i)
    {
        for (unsigned c = 0; c < arraySize; ++c)
        {   // Primary loop
            if (data[c] >= 128)
                sum_sort += data[c];
        }
    }
    
  auto t2 = std::chrono::steady_clock::now();

  auto elapsed = std::chrono::duration_cast<duration>(t2-t1).count();
  std::cout << "Elapsed Time: "<<elapsed<<" milliseconds"<<std::endl;
  
    std::cout << "sum = " << sum_sort << '\n';
}
