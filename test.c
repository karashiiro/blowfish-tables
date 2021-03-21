#include "blowfish-tables.h"
#include "test-tables.h"

#include <assert.h>
#include <stdbool.h> 
#include <stddef.h>
#include <stdio.h>

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
    unsigned int sBoxes[4][256];
    MakeBlowfishPArray(pArray, sizeof(pArray) / sizeof(pArray[0]));
    MakeBlowfishSBoxes(&sBoxes[0][0], sizeof(sBoxes) / sizeof(sBoxes[0]), sizeof(sBoxes[0]) / sizeof(sBoxes[0][0]), sizeof(pArray) / sizeof(pArray[0]));
    assert(ArraysEqual1D(
        pArray, sizeof(pArray) / sizeof(pArray[0]),
        PArray,  sizeof(PArray) / sizeof(PArray[0])));
    printf("PASS: P-array generated with correct values.\n");
    assert(ArraysEqual2D(
        &sBoxes[0][0], sizeof(sBoxes) / sizeof(sBoxes[0]), sizeof(sBoxes[0]) / sizeof(sBoxes[0][0]),
        &SBoxes[0][0],  sizeof(SBoxes) / sizeof(SBoxes[0]), sizeof(SBoxes[0]) / sizeof(SBoxes[0][0])));
    printf("PASS: Substitution boxes generated with correct values.\n");
    printf("All tests passed.\n");
    return 0;
}