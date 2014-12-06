# gcc-aarch-optimization-bug

This repo contains code to show a GCC on Aarch64 compiler bug that is present
in gcc version 4.9.2 (Debian/Linaro 4.9.2-5). The bug seems to be some sort
of incorrect interaction between the inliner and the `-fschedule-insns` compiler
flag.

The repo contains:

* ag_enc.c : The file displaying the problem.
* aglib.h : A header file.
* dyn_comp_test.c : The driver program.
* Makefile

# The Problem

The probelm is that the file `ag_enc.c` compiled with GCC 4.9.2 from Debian,
with optimisation flags of `-O1` returns the correct result, while if it is
compiled with `-O1 -fschedule-insns` it returns an incorrect result.

On a Debian Aarch64 system you can just run:

    CC=gcc-4.9 make clean check

which will compile the test program with the two different sets of compiler
flags, one which passes one which fails.

With gcc-4.8 on Aarch64 or gcc of any version of any other architecture, the
program will pass with both sets of compiler flags. Eg on Aarch64:

    CC=gcc-4.8 make clean check

I've also test this with Debian's gcc-snapshot (`gcc version 5.0.0 20141118
(experimental) [trunk revision 217719] (Debian 20141118-1)`) and it does not
display the problem either.
