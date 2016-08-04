# Gitfuck

Gitfuck is (\*) the first programming language ever to be created which cannot be version controlled using git.  
It's basically Brainfuck, but without the git.

\*) probably

## The Gitfuck Language

Gitfuck is 100% compatible with Brainfuck. In fact, Gitfuck is Brainfuck. The only difference is that Gitfuck programs are not stored in files, but in folders.  
Every Gitfuck program is contained in a folder. The folder contains a number of subdirectories. The name of each subdirectory will be interpreted as a line of Brainfuck code. The line number is defined by the timestamp: The subdirectory with the lowest timestamp is line 1, the one with the second lowest timestamp is line 2. A subdirectory containing any file or folder is treated as a commented, and thus completely ignored.

### Hello World in Gitfuck

```sh
mkdir hello.gf
mkdir hello.gf/comment+++ # this line will be completely ignored
touch hello.gf/comment+++/somefile
mkdir "hello.gf/0++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+."
sleep 1
mkdir "hello.gf/+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>."
```

Compile & Run:

```sh
gfcc hello.gf hello
./hello
```

Note that this program would also fit into a single directory name on most systems. The mkdir after the sleep solely serves demonstration purposes.

## Gitfuck tools

This repository contains various tools for the Gitfuck language.  

```sh
make && sudo make install
```

Compiling Gitfuck code:

```sh
gfcc source.gf a.out
```

Transpiling Brainfuck to Gitfuck:
```sh
bf2gf source.b out.bf
```

The gitfuck tools require `gcc` or `clang` installed which can compile AT&T X86-64 assembly code.
