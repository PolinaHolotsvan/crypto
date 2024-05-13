#include "Lab1.h"
#include <iostream>
#include <bitset>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <windows.h>
#include <algorithm>

using namespace std;

string toBinary(int64_t n) {
    string binary = bitset<64>(n).to_string();
    const auto pos = binary.find_first_not_of('0');
    if (pos != string::npos) {
        return binary.substr(pos);
    }
    return "0";
}

int64_t generatePrimeWithBitLength(int bits) {
    srand(time(NULL));
    int64_t candidate;
    do {
        candidate = rand() % (1 << (bits - 1));
    } while (!bailliePSW(candidate));
    return candidate;
}


vector<int64_t> generatePrimesWithBitLength(int bits, int count) {
    vector<int64_t> primes;
    int64_t candidate;

    for (int i = 0; i < count; ++i) {
        do {
            candidate = generatePrimeWithBitLength(bits);
        } while (find(primes.begin(), primes.end(), candidate) != primes.end());
        primes.push_back(candidate);
    }

    return primes;
}

vector<int64_t> generatePrimesForRSA(int bits) {
    int64_t candidate1, candidate2;
    candidate1 = generatePrimeWithBitLength(bits);

    do {
        candidate2 = generatePrimeWithBitLength(bits);
    } while ((candidate2 / 100) * abs(candidate1 - candidate2) < 40);
    return {candidate1, candidate2};
}

string toBase64(int64_t n) {
    string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string result;
    int64_t n_len = 0, n_copy = n;
    while (n_copy > 0) {
        n_copy /= 10;
        n_len++;
    }
    for (int i = 0; i < n_len; ++i) {
        result = base64_chars[n & 0x3F] + result;
        n >>= 6;
    }
    return result;
}


vector<uint8_t> toByteArray(int64_t n) {
    vector<uint8_t> bytes(sizeof(int64_t));
    for (size_t i = 0; i < sizeof(int64_t); ++i) {
        bytes[sizeof(int64_t) - i - 1] = (n >> (i * 8)) & 0xFF;
    }
    return bytes;
}

string toBase10(int64_t n) {
    return to_string(n);
}