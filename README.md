# blowfish-tables
A single-header C99 library for generating Blowfish tables, so you don't need to hardcode them into your projects. Allows arbitrary table sizes to handle modified forms of the algorithm.

Uses [OpenMP](https://www.openmp.org/).

## Installation
Include `blowfish-tables.h` in a source file and pass the compiler options `-fopenmp` on build, or `/openmp` with MSVC.

## Usage
```c
unsigned int pArray[18];
MakeBlowfishPArray(pArray, ARRAY_SIZE(pArray));
unsigned int sBoxes[4][256];
MakeBlowfishSBoxes(&sBoxes[0][0], ARRAY_SIZE(sBoxes), ARRAY_SIZE(sBoxes[0]), ARRAY_SIZE(pArray));
```

## Performance
On the typical configuration -- an 18-subkey P-array and 4 256-subkey substitution boxes -- it takes between 6 and 7 seconds to generate both tables on a 4-core Intel Core i5-7500.

**Not ready for actual use.**