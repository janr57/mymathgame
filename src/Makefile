# Makefile for mymathgame

PROG = mymathgame

CC = clang

CFLAGS = -g -Wall -O0

all: $(PROG)

$(PROG): $(PROG).o algorithms.o options.o jobs.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(PROG).o: $(PROG).c algorithms.h options.h jobs.h
	$(CC) $(CFLAGS) -o $@ -c $<

options.o: options.c options.h
	$(CC) $(CFLAGS) -o $@ -c $<

algorithms.o: algorithms.c algorithms.h
	$(CC) $(CFLAGS) -o $@ -c $<

mathops.o: jobs.c jobs.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	rm -f $(PROG) *.o *~ *#



