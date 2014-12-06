
CC ?= gcc
CFLAGS = $(OPT_FLAGS) -Isrc -std=c99 -Wall -Wextra -Wcast-align -Wcast-qual -Wshadow -Wbad-function-cast -Wwrite-strings -Wundef -Wuninitialized -Winit-self -Wnested-externs -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Waggregate-return -Wsequence-point

check :
	rm -f ag_enc.o
	OPT_FLAGS="-O" make dyn_comp_test && ./dyn_comp_test
	rm -f ag_enc.o
	OPT_FLAGS="-O -fschedule-insns" make dyn_comp_test && ./dyn_comp_test

dyn_comp_test : dyn_comp_test.o ag_enc.o
	$(CC) $+ -lm -o $@

clean :
	rm -f dyn_comp_test *.o
