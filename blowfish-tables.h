#ifndef MAKE_BLOWFISH_TABLES
#define MAKE_BLOWFISH_TABLES

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stddef.h>

// https://en.wikipedia.org/wiki/Modular_exponentiation#Pseudocode
static inline size_t _bftPowermod(size_t base, size_t exp, size_t mod) {
    if (mod == 1)
        return 0;
    size_t result = 1;
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

double _bftFPart(double x) {
    return x - floor(x);
}

// Copied from https://giordano.github.io/blog/2017-11-21-hexadecimal-pi/
double _bftCalcPiSum(size_t n, int j) {
    double sum = 0;
    size_t denominator = j;
    for (int k = 0; k <= n; k++) {
        sum = _bftFPart(sum + (double)_bftPowermod(16, n - k, denominator) / denominator);
        denominator += 8;
    }

    double numerator = 1.0 / 16;
    double fractional;
    while ((fractional = numerator / denominator) > DBL_EPSILON) {
        sum += fractional;
        numerator /= 16;
        denominator += 8;
    }

    return _bftFPart(sum);
}

/* See https://en.wikipedia.org/wiki/Bailey–Borwein–Plouffe_formula#BBP_digit-extraction_algorithm_for_π */
unsigned int _bftCalcPiFractionalDigit(size_t n) {
    n--;
    double sum1 = 4 * _bftCalcPiSum(n, 1);
    double sum2 = 2 * _bftCalcPiSum(n, 4);
    double sum3 = _bftCalcPiSum(n, 5);
    double sum4 = _bftCalcPiSum(n, 6);
    return (unsigned int)floor(16 * _bftFPart(sum1 - sum2 - sum3 - sum4));
}

unsigned int _bftMakeGroup(size_t n) {
    unsigned int group;
    for (int i = 1; i <= 8; i++) {
        group = (group << 4) | _bftCalcPiFractionalDigit(n + i);
    }
    return group;
}

/** Builds a Blowfish p-array into the provided buffer. */
void MakeBlowfishPArray(unsigned int *pArray, size_t subkeyCount) {
    size_t halfBytes = subkeyCount * 8;
    for (size_t n = 0; n < halfBytes; n += 8) {
        pArray[n / 8] = _bftMakeGroup(n);
    }
}

/** Builds Blowfish substitution boxes into the provided buffer. */
void MakeBlowfishSBoxes(unsigned int *sBoxes, size_t boxCount, size_t boxSize, size_t pSubkeys) {
    size_t halfBytes = boxCount * boxSize * 8;
    for (size_t b = 0; b < boxCount; b++) {
        size_t startHalfByte = b * (halfBytes / boxCount);
        size_t endHalfByte = (b + 1) * (halfBytes / boxCount);
        for (size_t n = startHalfByte; n < endHalfByte; n += 8) {
            sBoxes[n / 8] = _bftMakeGroup(pSubkeys * 8 + n);
        }
    }
}

#endif /* MAKE_BLOWFISH_TABLES */