# Makefile for mymathgame

PROG1 = mymathgame
PROG2 = freqtable

CC = clang

CFLAGS = -g -Wall -O0

all: $(PROG1) $(PROG2)

$(PROG1): $(PROG1).o algorithms.o options.o jobs.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(PROG1).o: $(PROG1).c messages.h algorithms.h options.h jobs.h
	$(CC) $(CFLAGS) -o $@ -c $<

options.o: options.c options.h messages.h
	$(CC) $(CFLAGS) -o $@ -c $<

algorithms.o: algorithms.c algorithms.h
	$(CC) $(CFLAGS) -o $@ -c $<

mathops.o: jobs.c jobs.h messages.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(PROG2): $(PROG2).o algorithms.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(PROG2).o: $(PROG2).c $(PROG2).h algorithms.h
	$(CC) $(CFLAGS) -o $@ -c $< 

.PHONY: clean

clean:
	rm -f $(PROG1) $(PROG2) *.o *~ *# 

