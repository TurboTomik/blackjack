CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c17
ifeq ($(DEBUG),1)
	CFLAGS += -g
endif

LDFLAGS = -lncurses

TARGET = blackjack

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
