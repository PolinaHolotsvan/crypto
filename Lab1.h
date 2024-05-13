#ifndef CRYPTO_LAB1_H
#define CRYPTO_LAB1_H
#include <cstdint>


int64_t powerMod(int64_t base, int64_t exponent, int64_t modulus);

bool millerRabin(int64_t n, int64_t k);

bool isQuadraticResidue(int64_t a, int64_t p);

int64_t legendre(int64_t a, int64_t p);

int64_t jacobi(int64_t a, int64_t m);

bool lucasTest(int64_t n, int64_t d, int64_t p, int64_t q);

bool bailliePSW(int64_t n);


#endif //CRYPTO_LAB1_H
