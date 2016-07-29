#include <stdio.h>
#include "stack.h"

struct bf_state {
	int inc_ctr;
	int loop_ctr;
	FILE *stream;
	struct stack loops;
};

struct bf_state bf_start(FILE *stream);
void bf_plus(struct bf_state state);
void bf_minus(struct bf_state state);
void bf_dot(struct bf_state state);
void bf_comma(struct bf_state state);
void bf_up(struct bf_state *state);
void bf_down(struct bf_state state);
void bf_loop_start(struct bf_state *state);
void bf_loop_end(struct bf_state *state);
void bf_end(struct bf_state state);

void bf_interpret_char(struct bf_state *state, char c);
void bf_interpret(struct bf_state *state, char *str);
