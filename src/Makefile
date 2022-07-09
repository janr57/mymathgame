# Makefile for mymathgame

PROG = mymathgame

CC = clang

CFLAGS = -g -Wall -O0

all: $(PROG)

$(PROG): $(PROG).c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f $(PROG)



