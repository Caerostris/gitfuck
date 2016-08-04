#include <stdlib.h>
#include <string.h>
#include "array.h"

struct array array_create(unsigned int element_size)
{
	struct array array;
	array.size = 0;
	array.position = 0;
	array.values = NULL;
	array.element_size = element_size;
	return array;
}

void array_destroy(struct array *array)
{
	free(array->values);
	array->values = NULL;
	array->size = 0;
	array->position = 0;
	array->element_size = 0;
}

void array_push(struct array *array, void *value)
{
	if(array->position == array->size)
	{
		array->size += 10;
		array->values = realloc(
			array->values,
			array->size * array->element_size
		);
	}

	memcpy(array->values + array->position, value, array->element_size);
	array->position += array->element_size;
}

int8_t array_pop(struct array *array, void *value)
{
	if(array->position == 0)
	{
		return 0;
	}

	array->position -= array->element_size;
	memcpy(value, array->values + array->position, array->element_size);
	return 1;
}

int8_t array_get(struct array *array, unsigned int index, void *value)
{
	void *src;
	if(index >= array_size(array))
	{
		return 0;
	}

	src = array->values + index * array->element_size;
	memcpy(value, src, array->element_size);
	return 1;
}

unsigned int array_size(struct array *array)
{
	return array->position / array->element_size;
}
