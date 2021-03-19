#include "blowfish-tables.h"
#include "test-tables.h"

#include <assert.h>
#include <stdbool.h> 
#include <stddef.h>

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
    unsigned int **arr1, size_t arr1_size1, size_t arr1_size2,
    unsigned int **arr2, size_t arr2_size1, size_t arr2_size2
) {
    if (arr1_size1 != arr2_size1 || arr1_size2 != arr2_size2) return false;

    for (size_t i = 0; i < arr1_size1; i++) {
        for (size_t j = 0; j < arr1_size2; j++) {
            if (arr1[i][j] != arr2[i][j]) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    unsigned int p_array[18];
    unsigned int s_boxes[4][256];
    MakeBlowfishPArray(p_array, sizeof(p_array));
    MakeBlowfishSBoxes(s_boxes, sizeof(s_boxes), sizeof(s_boxes[0]));
    assert(ArraysEqual1D(
        p_array, sizeof(p_array),
        PArray,  sizeof(PArray)));
    assert(ArraysEqual2D(
        s_boxes, sizeof(s_boxes), sizeof(s_boxes[0]),
        SBoxes,  sizeof(SBoxes),  sizeof(SBoxes[0])));
    return 0;
}