#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct stack stack_create(unsigned int element_size)
{
	struct stack stack;
	stack.size = 0;
	stack.position = 0;
	stack.values = NULL;
	stack.element_size = element_size;
	return stack;
}

void stack_destroy(struct stack *stack)
{
	free(stack->values);
	stack->values = NULL;
	stack->size = 0;
	stack->position = 0;
	stack->element_size = 0;
}

void stack_push(struct stack *stack, void *value)
{
	if(stack->position == stack->size)
	{
		stack->size += 10;
		stack->values = realloc(
			stack->values,
			stack->size * stack->element_size
		);
	}

	memcpy(stack->values + stack->position, value, stack->element_size);
	stack->position += stack->element_size;
}

int8_t stack_pop(struct stack *stack, void *value)
{
	if(stack->position == 0)
	{
		return 0;
	}

	stack->position -= stack->element_size;
	memcpy(value, stack->values + stack->position, stack->element_size);
	return 1;
}

int8_t stack_get(struct stack *stack, unsigned int index, void *value)
{
	void *src;
	if(index < 0 || index >= stack_size(stack))
	{
		return 0;
	}

	src = stack->values + index * stack->element_size;
	memcpy(value, src, stack->element_size);
	return 1;
}

unsigned int stack_size(struct stack *stack)
{
	return stack->position / stack->element_size;
}
