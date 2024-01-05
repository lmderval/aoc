CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -Wvla -pedantic

BIN = main

all: $(BIN)

debug: CPPFLAGS += -DDEBUG
debug: CFLAGS += -g -fsanitize=address
debug: LDFLAGS += -fsanitize=address
debug: $(BIN)

clean:
	$(RM) $(BIN)

.PHONY: all debug clean
