//
// Created by lenovo on 09.05.2024.
//

#ifndef CRYPTO_CONVERTOR_H
#define CRYPTO_CONVERTOR_H


#include <vector>
#include <string>

std::string toBinary(int64_t n);

std::vector<uint8_t> toByteArray(int64_t n);

int64_t generatePrimeWithBitLength(int bits);

std::vector<int64_t> generatePrimesForRSA(int bits);

std::vector<int64_t> generatePrimesWithBitLength(int bits, int count);

std::string toBase64(int64_t n);

std::string toBase10(int64_t n);


#endif //CRYPTO_CONVERTOR_H
