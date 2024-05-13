#include "Lab2.h"
#include "Lab1.h"
#include "Convertor.h"

using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

int64_t lcm(int64_t a, int64_t b) {
    return a / gcd(a, b) * b;
}

int64_t carmichael(int64_t p, int64_t q) {
    return lcm(p - 1, q - 1);
}

int64_t extendedEuclid(int64_t a, int64_t b) {
    int64_t b0 = b,
            a0 = a,
            x0 = 0,
            x1 = 1;
    int64_t temp, quotient;

    if (b0 == 1)
        return 0;

    while (a0 > 1) {
        quotient = a0 / b0;

        temp = b0;
        b0 = a0 % b0;

        a0 = temp;

        temp = x0;
        x0 = x1 - quotient * x0;
        x1 = temp;
    }

    if (x1 < 0)
        x1 += b;

    return x1;
}


int64_t chineseRemainder(vector<int64_t> &c, vector<int64_t> &m) {
    int64_t mProduct = 1;
    for (size_t i = 0; i < m.size(); ++i) {
        mProduct *= m[i];
    }

    int64_t x0 = 0;
    for (size_t i = 0; i < m.size(); ++i) {
        int64_t M = mProduct / m[i];
        int64_t N;
        N = extendedEuclid(M, m[i]);
        x0 += M * N * c[i];
    }

    return x0 % mProduct;
}


int64_t RSA::Encrypt(int64_t message) {
    return powerMod(message, e, n);
}

int64_t RSA::Decrypt(int64_t message) {
    int64_t m1 = message % p;
    int64_t m2 = message % q;
    int64_t exp1 = d % (p - 1);
    int64_t exp2 = d % (lambda / (p - 1));
    m1 = powerMod(m1, exp1, p);
    m2 = powerMod(m2, exp2, q);
    vector<int64_t> c = {m1, m2};
    vector<int64_t> m = {p, q};

    return chineseRemainder(c, m);
}

RSA::RSA(int64_t p, int64_t q, int bits) : p(p), q(q), bits(bits) {
    lambda = carmichael(p, q);
    n = p * q;
    do {
        e = generatePrimesWithBitLength(bits, 1)[0];
    } while (gcd(e, lambda) != 1);

    d = extendedEuclid(e, lambda);
}

RSA::RSA(int bits) {
    auto pq = generatePrimesForRSA(bits);
    p = pq[0], q = pq[1];
    lambda = carmichael(p, q);
    n = p * q;
    do {
        e = generatePrimesWithBitLength(bits, 1)[0];
    } while (gcd(e, lambda) != 1);

    d = extendedEuclid(e, lambda);
}