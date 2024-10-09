TC = tc
CC = gcc

TCFLAGS = --target-ia32 -S
LDFLAGS = -m32

BIN = main
ASM = $(BIN).s
SRC = $(BIN).tig

ECHO = echo -ne
BLUE = \e[34m
RESET = \e[m

CAT = cat
INPUT = input.txt

all: $(BIN)
asm: $(ASM)

ast: $(SRC)
	@$(ECHO) "$(BLUE) -- Computing AST for $^...$(RESET)\n $$ "
	$(TC) -A $^
	@$(ECHO) "$(BLUE) -- Computing AST for $^ OK$(RESET)\n\n"

$(BIN): $(ASM)
	@$(ECHO) "$(BLUE) -- Linking $@...$(RESET)\n $$ "
	$(CC) $(LDFLAGS) -o $@ $^
	@$(ECHO) "$(BLUE) -- Linking $@ OK$(RESET)\n\n"

$(ASM): $(SRC)
	@$(ECHO) "$(BLUE) -- Compiling $^...$(RESET)\n $$ "
	$(TC) $(TCFLAGS) $^ > $@
	@$(ECHO) "$(BLUE) -- Compiling $^ OK$(RESET)\n\n"

clean:
	@$(RM) $(BIN) $(ASM)

run: $(BIN)
	@$(CAT) $(INPUT) | ./$(BIN)

.PHONY: all asm ast clean run
