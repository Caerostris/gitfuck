CFLAGS=-Wall -Wextra
OBJS=src/bf.c src/stack.c
BINS=bin/gf2asm bin/bf2asm bin/bf2gf

.PHONY: all
all: $(BINS)

bin/%: src/%.c $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $@
