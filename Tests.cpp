//
// Created by lenovo on 13.05.2024.
//

#include <iostream>
#include <bitset>
#include "Lab1.h"
#include "Lab2.h"
#include "Convertor.h"
#include "Tests.h"

using namespace std;

void bailliePSWTest(int64_t n) {
    cout << endl << "bailliePSW test for " << n << endl;

    if (bailliePSW(n))
        cout << n << " is probably prime." << endl;
    else
        cout << n << " is composite." << endl;
}

void millerRabinTest(int64_t n, int64_t k) {
    cout << endl << "millerRabin test for " << n << endl;

    if (millerRabin(n, k))
        cout << n << " is probably prime." << endl;
    else
        cout << n << " is composite." << endl;
}


void convertorTest(int64_t n, int bits, int count) {
    cout << endl << "convertor test for " << n << endl;
    cout << "Binary: " << toBinary(n) << endl;
    cout << "Base10: " << toBase10(n) << endl;
    cout << "Base64: " << toBase64(n) << endl;
    vector<int64_t> primes = generatePrimesWithBitLength(bits, count);
    cout << count << " primes with " << bits << " bits: ";
    for (int64_t prime: primes) {
        cout << prime << " ";
    }
    std::cout << std::endl;
    std::vector<uint8_t> byteArray = toByteArray(n);

    std::cout << "Byte array representation of " << n << ":" << std::endl;
    for (uint8_t byte: byteArray) {
        std::cout << static_cast<int>(byte) << " ";
    }

}