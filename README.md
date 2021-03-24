# blowfish-tables
A single-header C99 library for generating Blowfish tables, so you don't need to hardcode them into your projects. Allows arbitrary table sizes to handle modified forms of the algorithm, with no guarantees on accuracy for larger sizes than the usual 18 subkey + 4x256 S-Box configuration.

Uses [OpenMP](https://www.openmp.org/).

**Not ready for actual use.**

## Installation
Include `blowfish-tables.h` in a source file and pass the compiler options `-fopenmp` on build, or `/openmp` with MSVC.

## Usage
```c
unsigned int pArray[18];
MakeBlowfishPArray(pArray, ARRAY_SIZE(pArray));
unsigned int sBoxes[4][256];
MakeBlowfishSBoxes(&sBoxes[0][0], ARRAY_SIZE(sBoxes), ARRAY_SIZE(sBoxes[0]), ARRAY_SIZE(pArray));
```

## Why?
* You don't want a file with lookup tables in your repo?
* You're reading this in 2040 and it takes less than a second for this to run on most machines?
* You want more or larger substitution boxes or P-arrays -- even though I can't guarantee this generates them accurately?
* You want to free the tables after using them to save on memory -- hardcoding them would mean a permanent 0-3kB addition to your binary over this.
* It was interesting to write, and I learned some things about C, assembly, optimization, and OpenMP.

## Performance
On the typical configuration -- an 18-subkey P-array and 4 256-subkey substitution boxes -- it takes between 3 and 5 seconds to generate both tables on a 4-core Intel Core i5-7500.

## Valgrind stuff

### There's a memory leak...
[There isn't.](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=36298)

### Helgrind hates me
[Yeah.](https://valgrind.org/docs/manual/hg-manual.html#hg-manual.effective-use)
