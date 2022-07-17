# Makefile for mymathgame

PROG = mymathgame

CC = clang

CFLAGS = -g -Wall -O0

all: $(PROG)

$(PROG): $(PROG).o options.o algorithms.o mathops.o
	$(CC) $(CFLAGS) -o $@ $^

$(PROG).o: $(PROG).c options.h algorithms.h mathops.h
	$(CC) $(CFLAGS) -o $@ -c $<

options.o: options.c options.h
	$(CC) $(CFLAGS) -o $@ -c $<

algorithms.o: algorithms.c algorithms.h
	$(CC) $(CFLAGS) -o $@ -c $<

mathops.o: mathops.c mathops.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	rm -f $(PROG) *.o *~ *#



