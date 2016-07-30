CFLAGS=-Wall -Wextra
OBJS=src/bf.c src/stack.c
BINS=bin/gf2asm bin/bf2asm

.PHONY: all
all: $(BINS)

bin/%: src/%.c $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $@
