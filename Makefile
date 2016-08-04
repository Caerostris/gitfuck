CFLAGS=-Wall -Wextra
OBJS=src/bf.c src/array.c
BINS=bin/gf2asm bin/bf2asm bin/bf2gf

.PHONY: all clean install
all: $(BINS)

clean:
	rm -f bin/*

install: all
	cp bin/* /usr/local/bin
	cp src/gfcc.sh /usr/local/bin/gfcc
	chmod +x /usr/local/bin/gfcc

bin/%: src/%.c $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $@
