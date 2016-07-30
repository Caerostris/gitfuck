#ifndef STACK_H_SDF829034SDF90
#define STACK_H_SDF829034SDF90

#include <inttypes.h>

struct stack {
	unsigned int size;
	unsigned int position;
	int *values;
};

struct stack stack_create();
void stack_destroy(struct stack *stack);

void stack_push(struct stack *stack, int value);
int8_t stack_pop(struct stack *stack, int *value);
unsigned int stack_size(struct stack *stack);

#endif // STACK_H_SDF829034SDF90
