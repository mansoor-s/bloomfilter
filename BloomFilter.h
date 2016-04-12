#ifndef BLOOMFILTER_BLOOMFILTER_H
#define BLOOMFILTER_BLOOMFILTER_H


#include <vector>
#include <cstdint>
#include <array>


class BloomFilter {
public:
    BloomFilter(std::uint64_t size, std::uint64_t numHashes);

    void insert(const std::uint8_t* data, std::size_t len);

    bool possiblyContains(const std::uint8_t* data, std::size_t len) const;

    //double currentErrorRate() const;

    // This MurmurHash3 implementation supports only hashing 32767 byte keys. (~32KB)
    static std::array<std::uint64_t, 2> hash(const std::uint8_t* data, int len);

    static inline std::uint64_t nthHash(std::uint8_t n, std::uint64_t hashA,
                                        std::uint64_t hashB, std::uint64_t filterSize);

private:
    std::uint64_t m_size;
    std::uint8_t m_numHashes;
    std::vector<bool> m_bits;
};


#endif //BLOOMFILTER_BLOOMFILTER_H
