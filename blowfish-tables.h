#ifndef MAKE_BLOWFISH_TABLES
#define MAKE_BLOWFISH_TABLES

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stddef.h>

size_t _powermod(size_t base, size_t exp, size_t mod) {
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

double _fPart(double x) {
    return x - floor(x);
}

// Copied from https://giordano.github.io/blog/2017-11-21-hexadecimal-pi/
double _calcPiSum(size_t n, int j) {
    double sum = 0;
    size_t denominator = j;
    for (int k = 0; k <= n; k++) {
        sum = _fPart(sum + (double)_powermod(16, n - k, denominator) / denominator);
        denominator += 8;
    }

    double numerator = 1.0 / 16;
    double fractional;
    while ((fractional = numerator / denominator) > DBL_EPSILON) {
        sum += fractional;
        numerator /= 16;
        denominator += 8;
    }

    return _fPart(sum);
}

/* See https://en.wikipedia.org/wiki/Bailey–Borwein–Plouffe_formula#BBP_digit-extraction_algorithm_for_π */
unsigned char _calcPiFractionalDigit(size_t n) {
    n--;
    double sum1 = 4 * _calcPiSum(n, 1);
    double sum2 = 2 * _calcPiSum(n, 4);
    double sum3 = _calcPiSum(n, 5);
    double sum4 = _calcPiSum(n, 6);
    return (unsigned char)floor(16 * _fPart(sum1 - sum2 - sum3 - sum4));
}

/** Builds a Blowfish p-array into the provided buffer. */
void MakeBlowfishPArray(unsigned int *p_array, size_t subkey_count) {
    size_t half_bytes = subkey_count * 8;
    for (size_t n = 0; n < half_bytes; n += 8) {
        unsigned group = _calcPiFractionalDigit(n + 1);
        group = (group << 4) | _calcPiFractionalDigit(n + 2);
        group = (group << 4) | _calcPiFractionalDigit(n + 3);
        group = (group << 4) | _calcPiFractionalDigit(n + 4);
        group = (group << 4) | _calcPiFractionalDigit(n + 5);
        group = (group << 4) | _calcPiFractionalDigit(n + 6);
        group = (group << 4) | _calcPiFractionalDigit(n + 7);
        group = (group << 4) | _calcPiFractionalDigit(n + 8);
        p_array[n / 8] = group;
    }
}

/** Builds Blowfish substitution boxes into the provided buffer. */
void MakeBlowfishSBoxes(unsigned int *s_boxes, size_t box_count, size_t box_size) {
    //
}

#endif /* MAKE_BLOWFISH_TABLES */