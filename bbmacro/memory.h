#ifndef BBMACRO_MEMORY_H_
#define BBMACRO_MEMORY_H_

#ifndef NOINCLUDE
#define NOINCLUDE
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <bbmacro/static.h>
#include <bbmacro/vector.h>
#undef NOINCLUDE
#endif

/*
 * Allocate memory. Abort if impossible.
 */
static BBUNUSED void *bbmacro_alloc(size_t len, size_t size)
{
	void *res;
	size_t total = len * size;

	assert(total / size == len); /* Check for overflow. */
	res = malloc(total);
	assert(res || total == 0); /* Check if memory was allocated. */
	return res;
}

/*
 * Increase capacity of a container logarithmically.
 * The base is chosen smaller than the golden ratio.
 * Theoretically, it helps to re-use memory (not tested).
 */
static BBUNUSED size_t bbmacro_increase(size_t cap)
{
	if (cap <= 3) {
		return cap + 1;
	} else {
		size_t newcap = cap + (cap >> 1); /* Multiply by 3/2. */
		assert(newcap > cap);
		return newcap;
	}
}

/****************************************
 * Typical usage.
 ****************************************/

#define BBSTATIC_BVECTOR(BV, ELEMENT) \
	BBDECLARE_BVECTOR(BV, ELEMENT, static BBUNUSED); \
	BBDEFINE_BVECTOR(BV, ELEMENT, bbmacro_alloc, free, bbmacro_increase)

#define BBSTATIC_FVECTOR(FV, ELEMENT) \
	BBDECLARE_FVECTOR(FV, ELEMENT, static BBUNUSED); \
	BBDEFINE_FVECTOR(FV, ELEMENT, bbmacro_alloc, free, bbmacro_increase)

#endif
