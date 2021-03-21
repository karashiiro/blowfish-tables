#include "blowfish-tables.h"
#include "test-tables.h"

#include <assert.h>
#include <stdbool.h> 
#include <stddef.h>
#include <stdio.h>

bool ArraysEqual1D(
    unsigned int *arr1, size_t arr1_size,
    unsigned int *arr2, size_t arr2_size
) {
    if (arr1_size != arr2_size) return false;

    for (size_t i = 0; i < arr1_size; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }

    return true;
}

bool ArraysEqual2D(
    unsigned int *arr1, size_t arr1_size1, size_t arr1_size2,
    unsigned int *arr2, size_t arr2_size1, size_t arr2_size2
) {
    if (arr1_size1 != arr2_size1 || arr1_size2 != arr2_size2) return false;

    for (size_t i = 0; i < arr1_size1; i++) {
        for (size_t j = 0; j < arr1_size2; j++) {
            if (arr1[i * arr1_size2 + j] != arr2[i * arr1_size2 + j]) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    unsigned int p_array[18];
    unsigned int s_boxes[4][256];
    MakeBlowfishPArray(p_array, sizeof(p_array) / sizeof(p_array[0]));
    MakeBlowfishSBoxes(&s_boxes[0][0], sizeof(s_boxes) / sizeof(s_boxes[0]), sizeof(s_boxes[0]) / sizeof(s_boxes[0][0]), sizeof(p_array) / sizeof(p_array[0]));
    assert(ArraysEqual1D(
        p_array, sizeof(p_array) / sizeof(p_array[0]),
        PArray,  sizeof(PArray) / sizeof(PArray[0])));
    printf("PASS: P-array generated with correct values.\n");
    assert(ArraysEqual2D(
        &s_boxes[0][0], sizeof(s_boxes) / sizeof(s_boxes[0]), sizeof(s_boxes[0]) / sizeof(s_boxes[0][0]),
        &SBoxes[0][0],  sizeof(SBoxes) / sizeof(SBoxes[0]), sizeof(SBoxes[0]) / sizeof(SBoxes[0][0])));
    printf("PASS: Substitution boxes generated with correct values.\n");
    printf("All tests passed.\n");
    return 0;
}