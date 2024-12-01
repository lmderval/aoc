TC = tcmp
CC = gcc
CPP = cpp

TCFLAGS = --c-overload -O --combine-rename --target-ia32 -S
LDFLAGS = -m32
CPPFLAGS = -Iinclude/

BIN = src/main
ASM = $(BIN).s
TIG = $(BIN).tig

TRASH = $(BIN) $(ASM) $(TIG) \
	$(TESTS) \
	main

TIG_TMP = /tmp/a.tig
ASM_TMP = /tmp/a.s

GITIGNORE = .gitignore

all: $(BIN)
	mv $^ ./

asm: $(ASM)
tig: $(TIG)

debug: CPPFLAGS += -DDEBUG
debug: all

%.tig: %.tim
	$(CPP) $(CPPFLAGS) $^ | sed -e '/^\s*#.*$$/d' > $(TIG_TMP) && cp $(TIG_TMP) $@

%.s: %.tig
	$(TC) $(TCFLAGS) $^ > $(ASM_TMP) && cp $(ASM_TMP) $@

%: %.s
	$(CC) $(LDFLAGS) -o $@ $^

%.ast: %.tig
	$(TC) -XA $^

%.bind: %.tig
	$(TC) -OBA $^

clean:
	$(RM) $(TRASH)

gitignore: $(GITIGNORE)
$(GITIGNORE):
	$(RM) $(GITIGNORE)
	for FILE in $(TRASH); do echo "/$${FILE}" >> $(GITIGNORE); done

.PHONY: all asm tig clean gitignore
