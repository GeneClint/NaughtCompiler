NCC = ../naught/comp
CPP = cpp
CC = gcc
INCDIRS = -I ../nstdlib
CFLAGS = -c -g -Wall -std=c99
LDFLAGS = -L ../nstdlib -lnaught

EXES = example

.PRECIOUS: %.c

all: $(EXES)

example: example.o fact.o initLabel.o ../naught/comp
	$(CC) example.o fact.o initLabel.o -o example $(LDFLAGS)
	./example

%.c : %.n ../naught/comp
	$(CPP) $(INCDIRS) $< | $(NCC) -d -o $@ -
	cat $@

%.o : %.c
	$(CC) $(CFLAGS) $(INCDIRS) $<

clean:
	rm -f *~ *.o *.c $(EXES)
