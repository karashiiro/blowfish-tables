#ifndef KARA_BLOWFISH_TABLES
#define KARA_BLOWFISH_TABLES

#include <stddef.h>

/** Builds a Blowfish p-array into the provided buffer. */
void MakeBlowfishPArray(unsigned int *p_array, size_t subkey_count) {
    //
}

/** Builds Blowfish substitution boxes into the provided buffer. */
void MakeBlowfishSBoxes(unsigned int **s_boxes, size_t box_count, size_t box_size) {
    //
}

#endif /* KARA_BLOWFISH_TABLES */