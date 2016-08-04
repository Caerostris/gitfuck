CFLAGS=-Wall -Wextra
OBJS=src/bf.c src/array.c
BINS=bin/gf2asm bin/bf2asm bin/bf2gf

.PHONY: all clean
all: $(BINS)

clean:
	rm -f bin/*

bin/%: src/%.c $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $@
