PROGRAM = ctg # name of executable
CC = gcc # compiler used: gcc
MAINSRC = main.c # main source file, in most cases main.c
SRCS = libturtlef.c # .c files containing funcs
HEADERS = libturtle.h bitman.h # .h files

PROFPROG = gprof # program used for profiling
PROFFLAGS = # flags for profiling program
OUTPROFFILE = perftest.txt # profiled output

CFLAGS = -O0 -ggdb -Wall -pg -Werror #-pedantic -ansi

# 'make' or 'make all' compiles executable
# 'make clean/cls' - removes files produced mid compiling
# 'make perftest' - builds, runs and profiles the program
# ====NO TOUCHIE TOUCHIE BELOW THIS LINE====

.PHONY: all clean cls perftest

OBJS = ${SRCS:.c=.o} $(MAINSRC:.c=.o)

all: $(PROGRAM)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean cls:
	rm -f  $(PROGRAM) $(OBJS) $(OUTPROFFILE)

perftest: $(PROGRAM)
	./$(PROGRAM) | $(PROFPROG) $(PROFFLAGS) $(PROGRAM) > $(OUTPROFFILE)
	rm -f gmon.out
