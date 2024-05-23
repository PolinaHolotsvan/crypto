//
// Created by lenovo on 13.05.2024.
//

#include <iostream>
#include <bitset>
#include "Lab1.h"
#include "Lab2.h"
#include "Convertor.h"
#include "Tests.h"
#include <chrono>

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
    cout << endl;
    printByteArray(n);
}

void RSATest(int64_t message, int bits){
    auto start = chrono::steady_clock::now();
    RSA rsa(bits);
    auto m1 = rsa.Encrypt(message);
    cout << "Encrypted message: "<< m1 << endl;
    auto m2 = rsa.Decrypt(m1);
    cout <<"Decrypted message: "<< m2 << endl;
    auto sign = rsa.SHA1(to_string(m2));
    cout <<"Sha1 signature: "<< sign << endl;

    auto end = chrono::steady_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time taken: " << elapsed_time << " milliseconds" << std::endl;
}