#include "test-tables.h"

#include <stdio.h>

int main() {
    for (int i = 0; i < 18; i++) {
        printf("%x ", PArray[i]);
    }
    printf("\n");

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 256; j++) {
            printf("%x ", SBoxes[i][j]);
        }
    }
    printf("\n");

    return 0;
}