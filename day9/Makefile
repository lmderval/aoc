CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -Wvla -pedantic

BIN = main

all: $(BIN)

debug: CPPFLAGS += -DDEBUG
debug: CFLAGS += -g
debug: $(BIN)

clean:
	$(RM) $(BIN)

.PHONY: all debug clean
