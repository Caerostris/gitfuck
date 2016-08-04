#include <stdio.h>
#include <stdlib.h>
#include "bf.h"

struct bf_state bf_start(FILE *stream)
{
	struct bf_state state;
	state.inc_ctr = 0;
	state.loop_ctr = 0;
	state.stream = stream;
	state.loops = stack_create(sizeof(int));

	fprintf(state.stream, ".align 4\n.globl _main\n_main:\n\tpushq\t%%r12\n\tpushq\t\%%rbx\n\tpushq\t%%rbp\n\tmovq\t%%rsp, %%rbp\n\tsubq\t$16, %%rsp\n\tmovq\t$-16, %%rbx\n\tmovq\t$0, 8(%%rsp)\n\tmovq\t$0, (%%rsp)\n\tmovq\t$-1, %%r12\n\n");

	return state;
}

void bf_interpret(struct bf_state *state, char *str)
{
	char c;
	while((c = *(str++)) != '\0')
	{
		bf_interpret_char(state, c);
	}
}

void bf_interpret_char(struct bf_state *state, char c)
{
	switch(c)
	{
		case '+':
			bf_plus(*state);
			break;
		case '-':
			bf_minus(*state);
			break;
		case '.':
			bf_dot(*state);
			break;
		case ',':
			bf_comma(*state);
			break;
		case '>':
			bf_up(state);
			break;
		case '<':
			bf_down(*state);
			break;
		case '[':
			bf_loop_start(state);
			break;
		case ']':
			bf_loop_end(state);
			break;
	}
}

void bf_plus(struct bf_state state)
{
	fprintf(state.stream, "\tincq\t(%%rbp, %%r12)\n");
}

void bf_minus(struct bf_state state)
{
	fprintf(state.stream, "\tdecq\t(%%rbp, %%r12)\n");
}

void bf_dot(struct bf_state state)
{
	fprintf(state.stream, "\n\tmovsbl\t(%%rbp, %%r12), %%edi\n\tcall\t_putchar\n");
}

void bf_comma(struct bf_state state)
{
	fprintf(state.stream, "\n\tcall\t_getchar\n\tmovb\t%%al, (%%rbp, %%r12)\n");
}

void bf_up(struct bf_state *state)
{
	int inc = ++state->inc_ctr;
	fprintf(state->stream, "\n\tcmpq\t%%r12, %%rbx\n\tjl\tDEC_CTR_%d\n\tsubq\t$16, %%rsp\n\tsubq\t$16, %%rbx\n\tmovq\t$0, 8(%%rsp)\n\tmovq\t$0, (%%rsp)\nDEC_CTR_%d:\n\tdecq\t%%r12\n", inc, inc);
}

void bf_down(struct bf_state state)
{
	fprintf(state.stream, "\tincq\t%%r12\n");
}

void bf_end(struct bf_state state)
{
	if(stack_size(&state.loops) != 0)
	{
		fprintf(stderr, "ERROR: Missing ]\n");
		exit(1);
	}

	fprintf(state.stream, "\n\tleave\n\tpopq\t%%rbx\n\tpopq\t%%r12\n\txorl\t%%eax, %%eax\n\tret\n");
	stack_destroy(&state.loops);
}

void bf_loop_start(struct bf_state *state)
{
	int loop = ++state->loop_ctr;
	stack_push(&state->loops, &loop);
	fprintf(state->stream, "\n\tcmpb\t$0, (%%rbp, %%r12)\n\tje\t_LE_%d\n_LS_%d:\n", loop, loop);
}

void bf_loop_end(struct bf_state *state)
{
	int loop;
	if(!stack_pop(&state->loops, &loop))
	{
		fprintf(stderr, "ERROR: Extraneuous ]\n");
		exit(1);
	}

	fprintf(state->stream, "\n\tcmpb\t$0, (%%rbp, %%r12)\n\tjne\t_LS_%d\n_LE_%d:\n\n", loop, loop);
}
