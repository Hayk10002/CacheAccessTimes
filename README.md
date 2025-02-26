# CacheAccessTimes

## Table of Contents
- [Introduction](#introduction)
- [Build and Run](#build-and-run)
- [Possible Output](#possible-output)
- [How does this work](#how-does-this-work)

## Introduction
The purpose of this project is to compare access times to varius cache types (e.g. L1, L2, L3 caches).

## Build and Run
To clone and run this project, you'll need [Git](https://git-scm.com) and [CMake](https://cmake.org/) installed on your computer. From your command line:

```bash
# Clone this repository
$ git clone https://github.com/Hayk10002/CacheAccessTimes

# Go into the repository
$ cd CacheAccessTimes

# We need to generate the executable in Release configuration to be able to observe the time difference between std::list and std::vector

# Generate the build files
$ cmake -DCMAKE_BUILD_TYPE=Release -S . -B build

# Build the project
$ cmake --build build --config Release

# Then, run the executable generated in the `build` directory with two number arguments.
$ your/path/to/ex/main.exe {The number of steps in one iteration} {The number of iterations}
# example - ...//main.exe 10000 1000
```

## Possible Output

```
Stride 1:     4902us  Average:      0ns
Stride 2:     3472us  Average:      0ns
Stride 4:     3356us  Average:      0ns
Stride 8:     5485us  Average:      0ns
Stride 16:   13195us  Average:      1ns
Stride 32:   15522us  Average:      1ns
Stride 64:   26160us  Average:      2ns
Stride 128:  49862us  Average:      4ns
Stride 256:  57181us  Average:      5ns
Stride 512:  56336us  Average:      5ns
Stride 1024: 52087us  Average:      5ns
Stride 2048: 67434us  Average:      6ns
```

## How does this work
by accessing elements with different strides. The stride is the number of elements skipped between each access. For example, a stride of 1 means accessing every element, while a stride of 2 means accessing every second element.

The code measures the time taken to access elements with different strides and calculates the average access time per element. This helps in understanding the impact of cache on access times. Larger strides may lead to more cache misses, resulting in higher access times.

The results show the total time taken for each stride and the average time per element access, giving insights into the efficiency of cache usage for different access patterns.

Note that average access time of 6ns is very fast for cache misses, this is the effect of cache prefetching.
