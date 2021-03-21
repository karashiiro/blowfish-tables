#ifndef MAKE_BLOWFISH_TABLES
#define MAKE_BLOWFISH_TABLES

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stddef.h>

// https://en.wikipedia.org/wiki/Modular_exponentiation#Pseudocode
size_t _bftPowermod(size_t base, size_t exp, size_t mod) {
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
unsigned char _bftCalcPiFractionalDigit(size_t n) {
    n--;
    double sum1 = 4 * _bftCalcPiSum(n, 1);
    double sum2 = 2 * _bftCalcPiSum(n, 4);
    double sum3 = _bftCalcPiSum(n, 5);
    double sum4 = _bftCalcPiSum(n, 6);
    return (unsigned char)floor(16 * _bftFPart(sum1 - sum2 - sum3 - sum4));
}

/** Builds a Blowfish p-array into the provided buffer. */
void MakeBlowfishPArray(unsigned int *p_array, size_t subkey_count) {
    size_t half_bytes = subkey_count * 8;
    for (size_t n = 0; n < half_bytes; n += 8) {
        unsigned group = _bftCalcPiFractionalDigit(n + 1);
        group = (group << 4) | _bftCalcPiFractionalDigit(n + 2);
        group = (group << 4) | _bftCalcPiFractionalDigit(n + 3);
        group = (group << 4) | _bftCalcPiFractionalDigit(n + 4);
        group = (group << 4) | _bftCalcPiFractionalDigit(n + 5);
        group = (group << 4) | _bftCalcPiFractionalDigit(n + 6);
        group = (group << 4) | _bftCalcPiFractionalDigit(n + 7);
        group = (group << 4) | _bftCalcPiFractionalDigit(n + 8);
        p_array[n / 8] = group;
    }
}

/** Builds Blowfish substitution boxes into the provided buffer. */
void MakeBlowfishSBoxes(unsigned int *s_boxes, size_t box_count, size_t box_size, size_t p_subkeys) {
    size_t half_bytes = box_count * box_size * 8;
    for (size_t b = 0; b < box_count; b++) {
        size_t start_half_byte = b * (half_bytes / box_count);
        size_t end_half_byte = (b + 1) * (half_bytes / box_count);
        for (size_t n = start_half_byte; n < end_half_byte; n += 8) {
            unsigned group = _bftCalcPiFractionalDigit(p_subkeys * 8 + n + 1);
            group = (group << 4) | _bftCalcPiFractionalDigit(p_subkeys * 8 + n + 2);
            group = (group << 4) | _bftCalcPiFractionalDigit(p_subkeys * 8 + n + 3);
            group = (group << 4) | _bftCalcPiFractionalDigit(p_subkeys * 8 + n + 4);
            group = (group << 4) | _bftCalcPiFractionalDigit(p_subkeys * 8 + n + 5);
            group = (group << 4) | _bftCalcPiFractionalDigit(p_subkeys * 8 + n + 6);
            group = (group << 4) | _bftCalcPiFractionalDigit(p_subkeys * 8 + n + 7);
            group = (group << 4) | _bftCalcPiFractionalDigit(p_subkeys * 8 + n + 8);
            s_boxes[n / 8] = group;
        }
    }
}

#endif /* MAKE_BLOWFISH_TABLES */