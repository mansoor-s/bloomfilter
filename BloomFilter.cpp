//
// Created by mansoor on 4/11/16.
//

#include <cstdint>

#include "BloomFilter.h"
#include "MurmurHash3.h"


BloomFilter::BloomFilter(std::uint64_t size, std::uint64_t numHashes) : m_size(size),
                                                                        m_numHashes(numHashes) {
    m_bits.resize(size);
}

void BloomFilter::insert(const std::uint8_t *data, std::size_t len) {
    auto hashValues = hash(data, len);

    for (int n = 0; n < m_numHashes; ++n) {
        auto hash = BloomFilter::nthHash(n, hashValues[0], hashValues[1], m_size);
        m_bits[hash] = true;
    }
}

bool BloomFilter::possiblyContains(const std::uint8_t *data, std::size_t len) const {
    auto hashValues = hash(data, len);

    for(int n = 0; n < m_numHashes; ++n) {
        auto hash = BloomFilter::nthHash(n, hashValues[0], hashValues[1], m_size);
        if (!m_bits[hash]) {
            return false;
        }
    }
    return true;
}




std::array<std::uint64_t, 2> BloomFilter::hash(const std::uint8_t* data, int len) {
    std::array<std::uint64_t, 2> hashValue;
    MurmurHash3_x64_128(data, len, 0, hashValue.data());
    return hashValue;
}


inline std::uint64_t BloomFilter::nthHash(std::uint8_t n,
                                                 std::uint64_t hashA,
                                                 std::uint64_t hashB,
                                                 std::uint64_t filterSize) {
    return (hashA + n * hashB) % filterSize;
}




