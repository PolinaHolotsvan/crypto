#include "Lab2.h"
#include "Lab1.h"
#include "Convertor.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

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



uint32_t leftShift(uint32_t w, unsigned bits) {
    return (w << bits) | (w >> (32 - bits));
}

string RSA::SHA1(string message) {
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;
    vector<uint8_t> bitMessage(message.begin(), message.end());

    uint64_t ml = bitMessage.size() * 8;
    bitMessage.push_back(0x80);
    while ((bitMessage.size() * 8) % 512 != 448) {
        bitMessage.push_back(0x00);
    }

    for (int i = 7; i >= 0; --i) {
        bitMessage.push_back((ml >> (i * 8)) & 0xFF);
    }

    for (size_t i = 0; i < bitMessage.size(); i += 64) {

        uint32_t w[80];
        for (int j = 0; j < 16; ++j) {
            w[j] = (uint32_t(bitMessage[i + j * 4]) << 24) |
                   (uint32_t(bitMessage[i + j * 4 + 1]) << 16) |
                   (uint32_t(bitMessage[i + j * 4 + 2]) << 8) |
                   (uint32_t(bitMessage[i + j * 4 + 3]));
        }
        for (int j = 16; j < 80; ++j) {
            w[j] = leftShift((w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16]), 1);
        }

        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;

        for (int j = 0; j < 80; ++j) {
            uint32_t f, k;
            if (j < 20) {
                f = (b & c) | (~b & d);
                k = 0x5A827999;
            } else if (j < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }
            uint32_t temp = leftShift(a, 5) + f + e + k + w[j];
            e = d;
            d = c;
            c = leftShift(b, 30);
            b = a;
            a = temp;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    uint32_t h[] = {h0, h1, h2, h3, h4};
    ostringstream hashStream;
    for (auto i : h) {
        hashStream << hex << setfill('0') << setw(8);
        hashStream << i;
    }

    string hash = hashStream.str();
    return hash;
}

