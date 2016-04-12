#include <iostream>
#include <functional>
#include <cstdint>
#include <string>
#include <chrono>

#include "BloomFilter.h"


//std::clock time is fine in this case; no sleeps
void benchRunner(std::string name, std::function<void()> func, std::size_t itterations) {
    std::cout << "=======================================" << std::endl;
    std::cout << "\t" << name << " Benchmark\t" << std::endl;
    std::cout << "\t" << itterations << " iterations" << "\t" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    auto start = std::clock();

    func();

    auto end = std::clock();
    double dt = double(end - start) / (double)CLOCKS_PER_SEC * 1000;
    auto averageTime = double(dt / itterations) * 1000000; // in nanoseconds

    std::cout << "\tTotal Time: " << dt << "ms" << std::endl;
    std::cout << "\tAverage Time: " << averageTime << " ns" << std::endl;

    std::cout << "=======================================" << std::endl << std::endl;
}


std::function<void()> benchInsert(BloomFilter& bf, std::size_t ittr) {
    return [ittr, &bf]() {
        for(size_t i = 0; i < ittr; ++i) {
            const char* foo = "asdfghj";
            bf.insert((std::uint8_t*)foo, 7);
        }
    };
}

std::function<void()> benchPossiblyContains(BloomFilter& bf, std::size_t ittr) {
    return [ittr, &bf]() {
        for(size_t i = 0; i < ittr; ++i) {
            const char* foo = "asdfg156916hj";
            bf.possiblyContains((std::uint8_t*)foo, 7);
        }
    };
}

int main() {
    std::cout << "Let's Bench!!!" << std::endl;
    BloomFilter bf_insert(14, 3.2e+7);
    BloomFilter bf_contains(14, 3.2e+7);

    std::size_t NUM_INSERT = 50000000;
    std::size_t NUM_CONTAINS = 50000000;
    benchRunner("Insert", benchInsert(bf_insert, NUM_INSERT), NUM_INSERT);
    benchRunner("PossiblyContains", benchPossiblyContains(bf_contains, NUM_CONTAINS), NUM_CONTAINS);

    return 0;
}