#include <cmath>
#include "Lab1.h"


int64_t powerMod(int64_t base, int64_t exponent, int64_t modulus) {
    int64_t result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent & 1)
            result = (result * base) % modulus;

        base = (base * base) % modulus;
        exponent = exponent >> 1;
    }
    return result;
}


bool millerRabin(int64_t n, int64_t k) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0)
        return false;

    int64_t m = (n - 1) / 2;
    int64_t t = 1;

    while (m % 2 == 0) {
        m /= 2;
        t++;
    }

    int64_t a, u;
    for (int64_t i = 1; i <= k; ++i) {
        int64_t random = rand() % (n - 3) + 2;
        a = random;
        u = powerMod(a, m, n);

        if (u != 1 && u != n - 1) {
            for (int64_t j = 1; j < t && u != n - 1; ++j)
                u = powerMod(u, 2, n);

            if (u != n - 1)
                return false;
        }
    }

    return true;
}

bool isQuadraticResidue(int64_t a, int64_t p) {
    for (int64_t i = 1; i < p; ++i) {
        if ((i * i) % p == a) {
            return true;
        }
    }
    return false;
}


int64_t legendre(int64_t a, int64_t p) {
    int64_t modded = a % p;
    if (p < 3 || modded == 0)
        return 0;

    if (isQuadraticResidue(a, p)) {
        return 1;
    }
    return -1;
}


int64_t jacobi(int64_t a, int64_t n) {
    if (n <= 0 || n % 2 == 0) return 0;
    a = a % n;
    int64_t t = 1;
    int64_t r;
    while (a != 0) {
        while (a % 2 == 0) {
            a /= 2;
            r = n % 8;
            if (r == 3 || r == 5) {
                t = -t;
            }
        }
        r = n;
        n = a;
        a = r;
        if (a % 4 == 3 && n % 4 == 3) {
            t = -t;
        }
        a = a % n;
    }
    if (n == 1) {
        return t;
    } else {
        return 0;
    }
}

int64_t u_i(int64_t i, int64_t p, int64_t q, int64_t n) {

    int64_t u_0 = 0;
    int64_t u_1 = 1;
    if (i == 0) return u_0;
    if (i == 1) return u_1;

    int64_t u_i;
    for (int64_t j = 2; j <= i; j++) {
        u_i = (p * u_1 - q * u_0) % n;
        u_0 = u_1;
        u_1 = u_i;
    }
    return u_i;
}


int64_t v_i(int64_t i, int64_t p, int64_t q, int64_t n) {

    int64_t v_0 = 2;
    int64_t v_1 = p;
    if (i == 0) return v_0;
    if (i == 1) return v_1;

    int64_t v_i;
    for (int64_t j = 2; j <= i; j++) {
        v_i = (p * v_1 - q * v_0) % n;
        v_0 = v_1;
        v_1 = v_i;
    }
    return v_i;
}


bool lucasTest(int64_t n, int64_t d, int64_t p, int64_t q) {
    int64_t n_e = n + 1;
    int64_t r = 0;

    while (n_e % 2 == 0 && n_e > 0) {
        n_e /= 2;
        r++;
    }

    int64_t s = n_e;

    for (int j = 0; j < r; j++) {
        if (v_i(s * pow(2, j), p, q, n) % n == 0)
            return true;
    }

    return u_i(s, p, q, n) % n == 0;
}


bool bailliePSW(int64_t n) {
    if (!millerRabin(n, 2)) return false;

    int64_t d = 5;

    while (jacobi(d, n) != -1) {
        if (d > 0)
            d = -(d + 2);
        else
            d = -(d - 2);
    }

    int64_t p = 1;
    int64_t q = (1 - d) / 4;
    return lucasTest(n, d, p, q);
}