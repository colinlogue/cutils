#ifndef MEMSHUFFLE_H
#define MEMSHUFFLE_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

int rand_range(int start, int end);
void mem_shuffle(void *block_start; int n_units; size_t unit_size);

#endif