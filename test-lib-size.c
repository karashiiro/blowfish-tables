#include "blowfish-tables.h"

#include <stdio.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

int main() {
    unsigned int pArray[18];
    unsigned int sBoxes[4][256];
    MakeBlowfishPArray(pArray, ARRAY_SIZE(pArray));
    MakeBlowfishSBoxes(&sBoxes[0][0], ARRAY_SIZE(sBoxes), ARRAY_SIZE(sBoxes[0]), ARRAY_SIZE(pArray));
    
    for (int i = 0; i < 18; i++) {
        printf("%x ", pArray[i]);
    }
    printf("\n");

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 256; j++) {
            printf("%x ", sBoxes[i][j]);
        }
    }
    printf("\n");

    return 0;
}