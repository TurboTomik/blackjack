COMPILER=gcc -c
LINKER=gcc
CFLAGS=-Wall -g

.PHONY: clean

OBJECTS=$(patsubst %.c, %.o, $(wildcard *.c))

blackjack: $(OBJECTS)
				$(LINKER) $^ -lncurses -o $@

%.o:: %.c %.h
				$(COMPILER) $(CFLAGS) $< -o $@

clean:
				rm -rf *.o
				rm blackjack
