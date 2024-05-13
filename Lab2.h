//
// Created by lenovo on 05.05.2024.
//

#ifndef CRYPTO_LAB2_H
#define CRYPTO_LAB2_H


#include <cstdint>

class RSA {
public:
    int bits;
    int64_t p, q, e, d;
    int64_t lambda;
    int64_t n;

    RSA(int64_t p, int64_t q, int bits);

    RSA(int bits);

    int64_t Encrypt(int64_t message);

    int64_t Decrypt(int64_t message);
};

int64_t gcd(int64_t a, int64_t b);

int64_t lcm(int64_t a, int64_t b);

#endif //CRYPTO_LAB2_H
