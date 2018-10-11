#include "memshuffle.h"

int rand_range(int start, int end) {
	/** Returns a random number in the range (start, end].

			Paramters
			---------
			start, end : int
					Mark the end of the range to be picked from.

			Returns
			-------
			int
					A random int in the range (start, end].
	**/
	int len = end - start;
	assert(len > 0);
	return rand() % len;
}

void mem_shuffle(void *block_start; int n_units; size_t unit_size) {
	/** Breaks a block of memory into a number of units and shuffles those units.

			Parameters
			----------
			block_start : *void
					Pointer to the start of the block of memory to be shuffled.
			n_units : size_t
					The number of units to break the memory block into.
			unit_size : size_t
					The size in bytes of each memory unit.

			Notes
			-----
			Memory must be previously allocated and of at least size n_units *
			unit_size (starting from block_start).
	**/
	void *current_ptr, *swap_ptr;
	int swap_idx;
	void *copybuffer = malloc(unit_size);
	for (int current_idx=0; current_idx < n_units; current_idx++) {
		// copy value of current index to copy_buffer
		current_ptr = block_start + (current_idx * unit_size);
		memcpy(copy_buffer, current_ptr, unit_size);
		// copy value of random index to current index
		swap_idx = rand_range(current_idx, n_units);
		swap_ptr = block_start + (item_size * swap_idx);
		memcpy(current_ptr, swap_ptr, unit_size);
		// copy saved value of current index to swap index
		memcpy(swap_ptr, copy_buffer, unit_size);
	}
	free(copy_buffer);
}