cmake_minimum_required(VERSION 3.5)
project(bloomfilter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BloomFilter.cpp BloomFilter.h MurmurHash3.cpp MurmurHash3.h)
add_executable(bloomfilter ${SOURCE_FILES})