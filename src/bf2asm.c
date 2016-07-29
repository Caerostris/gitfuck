#include <stdio.h>
#include <stdlib.h>
#include "bf.h"

int main(int argc, char* argv[])
{
	struct bf_state state;
	FILE *in, *out;	
	char c;

	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s <input file> [output file]\n", argv[0]);
		exit(1);
	}
	else if(argc >= 3)
	{
		out = fopen(argv[2], "w+");
	}
	else
	{
		out = stdout;
	}

	in = fopen(argv[1], "r");
	if(in == NULL)
	{
		perror(argv[1]);
		exit(1);
	}
	state = bf_start(out);

	while((c = fgetc(in)) != EOF)
	{
		bf_interpret_char(&state, c);
	}
	bf_end(state);
	return 0;
}
