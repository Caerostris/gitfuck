#ifndef STACK_H_SDF829034SDF90
#define STACK_H_SDF829034SDF90

#include <inttypes.h>

struct array {
	unsigned int size;
	unsigned int position;
	unsigned int element_size;
	void *values;
};

struct array array_create(unsigned int element_size);
void array_destroy(struct array *array);

void array_push(struct array *array, void *value);
int8_t array_pop(struct array *array, void *value);
int8_t array_get(struct array *array, unsigned int index, void *value);
unsigned int array_size(struct array *array);

#endif // STACK_H_SDF829034SDF90
