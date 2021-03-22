#ifndef MAKE_BLOWFISH_TABLES
#define MAKE_BLOWFISH_TABLES

#include <stddef.h>

// https://en.wikipedia.org/wiki/Modular_exponentiation#Pseudocode
// These must be 64-bit unsigned integers, or the base^2 operation will
// overflow for large bases.
static inline unsigned long long _bftPowermod(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    if (mod == 1)
        return 0;
    unsigned long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// https://stackoverflow.com/a/26091248
unsigned int _bftFloor(double x) {
    unsigned int xi = (unsigned int)x;
    return x < xi ? xi - 1 : xi;
}

double _bftFPart(double x) {
    return x - _bftFloor(x);
}

// Based on https://giordano.github.io/blog/2017-11-21-hexadecimal-pi/
double _bftCalcPiSum(size_t n, size_t j) {
    double sum = 0.0;
    size_t denominator = j;
    for (size_t k = 0; k <= n; k++) {
        sum += (double)_bftPowermod(16, n - k, denominator) / denominator;
        denominator += 8;
    }
    // Completely elide the infinite sum
    return sum;
}

/* See https://en.wikipedia.org/wiki/Bailey–Borwein–Plouffe_formula#BBP_digit-extraction_algorithm_for_π */
unsigned int _bftCalcPiFractionalDigit(size_t n) {
    double sum1 = _bftCalcPiSum(n, 1);
    double sum2 = _bftCalcPiSum(n, 4);
    double sum3 = _bftCalcPiSum(n, 5);
    double sum4 = _bftCalcPiSum(n, 6);
    return _bftFloor(16 * _bftFPart(4 * sum1 - 2 * sum2 - sum3 - sum4));
}

unsigned int _bftMakeGroup(size_t n) {
    unsigned int group;
    unsigned int digits[8];
    
    #pragma omp parallel for default(none) firstprivate(n) shared(digits)
    for (size_t i = 0; i < 8; i++) {
        digits[i] = _bftCalcPiFractionalDigit(n + i);
    }
    
    for (int i = 0; i < 8; i++) {
        digits[i] <<= (32 - (i + 1) * 4);
    }

    for (int i = 0; i < 8; i++) {
        group |= digits[i];
    }

    return group;
}

/** Builds a Blowfish p-array into the provided buffer. */
void MakeBlowfishPArray(unsigned int *pArray, size_t subkeyCount) {
    for (size_t n = 0; n < subkeyCount; n++) {
        pArray[n] = _bftMakeGroup(n * 8);
    }
}

/** Builds Blowfish substitution boxes into the provided buffer. */
void MakeBlowfishSBoxes(unsigned int *sBoxes, size_t boxCount, size_t boxSize, size_t pSubkeys) {
    size_t subkeyCount = boxCount * boxSize;
    for (size_t n = 0; n < subkeyCount; n++) {
        sBoxes[n] = _bftMakeGroup(8 * (pSubkeys + n));
    }
}

#endif /* MAKE_BLOWFISH_TABLES */