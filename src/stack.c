#include <stdlib.h>
#include "stack.h"

struct stack stack_create()
{
	struct stack stack;
	stack.size = 0;
	stack.position = 0;
	stack.values = NULL; 
	return stack;
}

void stack_destroy(struct stack *stack)
{
	free(stack->values);
	stack->values = NULL;
	stack->size = 0;
	stack->position = 0;
}

void stack_push(struct stack *stack, int value)
{
	if(stack->position == stack->size)
	{
		stack->size += 10;
		stack->values = realloc(stack->values, stack->size * sizeof(int));
	}

	stack->values[stack->position++] = value;
}

int8_t stack_pop(struct stack *stack, int *value)
{
	if(stack->position == 0)
	{
		return 0;
	}

	*value = stack->values[--stack->position];
	return 1;
}

unsigned int stack_size(struct stack *stack)
{
	return stack->position;
}
