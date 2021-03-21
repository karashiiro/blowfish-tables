#include "blowfish-tables.h"
#include "test-tables.h"

#include <assert.h>
#include <stdbool.h> 
#include <stddef.h>
#include <stdio.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

bool ArraysEqual1D(
    unsigned int *arr1, size_t arr1Size,
    unsigned int *arr2, size_t arr2Size
) {
    if (arr1Size != arr2Size) return false;

    for (size_t i = 0; i < arr1Size; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }

    return true;
}

bool ArraysEqual2D(
    unsigned int *arr1, size_t arr1Size1, size_t arr1Size2,
    unsigned int *arr2, size_t arr2Size1, size_t arr2Size2
) {
    if (arr1Size1 != arr2Size1 || arr1Size2 != arr2Size2) return false;

    for (size_t i = 0; i < arr1Size1; i++) {
        for (size_t j = 0; j < arr1Size2; j++) {
            if (arr1[i * arr1Size2 + j] != arr2[i * arr2Size2 + j]) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    unsigned int pArray[18];
    MakeBlowfishPArray(pArray, ARRAY_SIZE(pArray));
    assert(ArraysEqual1D(
        pArray, ARRAY_SIZE(pArray),
        PArray,  ARRAY_SIZE(PArray)));
    printf("PASS: P-array generated with correct values.\n");

    unsigned int sBoxes[4][256];
    MakeBlowfishSBoxes(&sBoxes[0][0], ARRAY_SIZE(sBoxes), ARRAY_SIZE(sBoxes[0]), ARRAY_SIZE(pArray));
    assert(ArraysEqual2D(
        &sBoxes[0][0], ARRAY_SIZE(sBoxes), ARRAY_SIZE(sBoxes[0]),
        &SBoxes[0][0],  ARRAY_SIZE(SBoxes), ARRAY_SIZE(SBoxes[0])));
    printf("PASS: Substitution boxes generated with correct values.\n");

    printf("All tests passed.\n");
    return 0;
}