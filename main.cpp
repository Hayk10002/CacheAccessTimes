#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <random>
#include <format>
#include <cassert>

// Random number from 0 to max-1 inclusive
int getRandomNum(int max)
{
    static std::mt19937 engine{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(0, max - 1);
    return dist(engine);
}

template<class F>
auto time_ms(F f, int N)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++) f();

    return std::chrono::high_resolution_clock::now() - start; 
}

int main(int argc, char* argv[]) {
    assert(argc == 3);
    int N = std::stoi(argv[1]);
    int M = std::stoi(argv[2]);
    int ARR_SIZE = 2048 * N;    
    std::vector<char> array(ARR_SIZE);
    for(int i = 0; i < ARR_SIZE; i++) array[i] = getRandomNum(1000);

    volatile int x;

    auto stride_1    = time_ms([&] { int ind = getRandomNum(ARR_SIZE - (N - 1) * 1   ); for (int i = 0; i < N; i++) { x += array[ind]; ind += 1;    } }, M);
    auto stride_2    = time_ms([&] { int ind = getRandomNum(ARR_SIZE - (N - 1) * 2   ); for (int i = 0; i < N; i++) { x += array[ind]; ind += 2;    } }, M);
    auto stride_4    = time_ms([&] { int ind = getRandomNum(ARR_SIZE - (N - 1) * 4   ); for (int i = 0; i < N; i++) { x += array[ind]; ind += 4;    } }, M);
    auto stride_8    = time_ms([&] { int ind = getRandomNum(ARR_SIZE - (N - 1) * 8   ); for (int i = 0; i < N; i++) { x += array[ind]; ind += 8;    } }, M);
    auto stride_16   = time_ms([&] { int ind = getRandomNum(ARR_SIZE - (N - 1) * 16  ); for (int i = 0; i < N; i++) { x += array[ind]; ind += 16;   } }, M);
    auto stride_32   = time_ms([&] { int ind = getRandomNum(ARR_SIZE - (N - 1) * 32  ); for (int i = 0; i < N; i++) { x += array[ind]; ind += 32;   } }, M);
    auto stride_64   = time_ms([&] { int ind = getRandomNum(ARR_SIZE - (N - 1) * 64  ); for (int i = 0; i < N; i++) { x += array[ind]; ind += 64;   } }, M);
    auto stride_128  = time_ms([&] { int ind = getRandomNum(ARR_SIZE - (N - 1) * 128 ); for (int i = 0; i < N; i++) { x += array[ind]; ind += 128;  } }, M);
    auto stride_256  = time_ms([&] { int ind = getRandomNum(ARR_SIZE - (N - 1) * 256 ); for (int i = 0; i < N; i++) { x += array[ind]; ind += 256;  } }, M);
    auto stride_512  = time_ms([&] { int ind = getRandomNum(ARR_SIZE - (N - 1) * 512 ); for (int i = 0; i < N; i++) { x += array[ind]; ind += 512;  } }, M);
    auto stride_1024 = time_ms([&] { int ind = getRandomNum(ARR_SIZE - (N - 1) * 1024); for (int i = 0; i < N; i++) { x += array[ind]; ind += 1024; } }, M);
    auto stride_2048 = time_ms([&] { int ind = getRandomNum(ARR_SIZE - (N - 1) * 2048); for (int i = 0; i < N; i++) { x += array[ind]; ind += 2048; } }, M);
    
    std::cout << std::format(
        "Stride 1:   {:>8}  Average: {:>8}\n"
        "Stride 2:   {:>8}  Average: {:>8}\n"
        "Stride 4:   {:>8}  Average: {:>8}\n"
        "Stride 8:   {:>8}  Average: {:>8}\n"
        "Stride 16:  {:>8}  Average: {:>8}\n"
        "Stride 32:  {:>8}  Average: {:>8}\n"
        "Stride 64:  {:>8}  Average: {:>8}\n"
        "Stride 128: {:>8}  Average: {:>8}\n"
        "Stride 256: {:>8}  Average: {:>8}\n"
        "Stride 512: {:>8}  Average: {:>8}\n"
        "Stride 1024:{:>8}  Average: {:>8}\n"
        "Stride 2048:{:>8}  Average: {:>8}\n",
        std::chrono::duration_cast<std::chrono::microseconds>(stride_1),   stride_1    / (N * M),
        std::chrono::duration_cast<std::chrono::microseconds>(stride_2),   stride_2    / (N * M),
        std::chrono::duration_cast<std::chrono::microseconds>(stride_4),   stride_4    / (N * M),
        std::chrono::duration_cast<std::chrono::microseconds>(stride_8),   stride_8    / (N * M),
        std::chrono::duration_cast<std::chrono::microseconds>(stride_16),  stride_16   / (N * M),
        std::chrono::duration_cast<std::chrono::microseconds>(stride_32),  stride_32   / (N * M),
        std::chrono::duration_cast<std::chrono::microseconds>(stride_64),  stride_64   / (N * M),
        std::chrono::duration_cast<std::chrono::microseconds>(stride_128), stride_128  / (N * M),
        std::chrono::duration_cast<std::chrono::microseconds>(stride_256), stride_256  / (N * M),
        std::chrono::duration_cast<std::chrono::microseconds>(stride_512), stride_512  / (N * M),
        std::chrono::duration_cast<std::chrono::microseconds>(stride_1024),stride_1024 / (N * M),
        std::chrono::duration_cast<std::chrono::microseconds>(stride_2048),stride_2048 / (N * M)
    );

    return 0;
}
