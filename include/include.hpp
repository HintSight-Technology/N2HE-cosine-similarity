#ifndef INCLUDE_H
#define INCLUDE_H

#pragma once

//intel hexl library 
 #include "hexl/hexl.hpp"

//SEAL library
//#include "seal/seal.h"

//C++
#include <iostream>
#include <vector>
#include <ctime>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <functional>
#include <condition_variable>
#include <chrono>
#include <thread>
#include <cstdint>
#include <algorithm>
#include <cmath>
// #include <immintrin.h>
#include <omp.h>
#include <string>
#include <memory>
#include <limits>
#include <mutex>
#include <numeric>
#include <random>
#include <sstream>
#include <iomanip>


//Random Number Generator
#include "RandomNumberGenerator/lac_param.h"
#include "RandomNumberGenerator/rand.hpp"


//LWE
#include "LWEscheme/LWE_32.hpp"
#include "LWEscheme/LWE_64.hpp"

//polynomial ring
#include "PolynomialRing/Poly_ring_64.hpp"
typedef vector<int64_t> polynomial;

//RLWE
#include "RLWEscheme/RLWE_64.hpp"
#include "RLWEscheme/Encoding_Decoding_64.hpp"
#include "RLWEscheme/Rotation.hpp"
#include "RLWEscheme/LT.hpp"
#include "RLWEscheme/Multiplication.hpp"
#include "RLWEscheme/Poly_evaluation.hpp"

//test
#include "test/eval.hpp"




#endif