#include <iostream>
#include <limits>
#include <random>
#include <vector>
#include <math.h>

template <typename T>
void accumulate(std::vector<double>& vec) {

}

int main(int argc, char *argv[]) {
  // Number of elements in vector
  long N = 100000;

  // Initialize a vector with a random distribution of values
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  std::mt19937 mt = std::mt19937(1);
  std::vector<double> vec;
  for (int i = 0; i < N; i++) {
    vec.push_back( dist(mt) );
  }

  // Test the forwards and backwards accumulations, using several different types for holding the intermediate values.
  accumulate<float>(vec);
  accumulate<double>(vec);
  accumulate<int>(vec);
  accumulate<long>(vec);
}
