# N2HE-cosine-similarity
This is a C++ open-source library which implements a FHE-based cosine similarity evaluation algorithm. 

We use the N2HE scheme as the underlying FHE scheme and design a cosine similarity evaluation algorithm with two encrypted vectors as input. 
The input vectors should have $l_2$-norm $1$. 


## Prerequisites
- [OpenSSL](https://www.openssl.org/) 3.2.1 or later
- [hexl](https://github.com/intel/hexl) Release V1.2.5 or later
- [Openmp](https://www.openmp.org) Release 4.1.6 or later

## Installation
Installation on Linux:  

```
mkdir build && cd build
cmake ..
make
```

Run the test: 
```
./test
```

## License
This software is distributed under the BSD-3-Clause-Clear license. 
