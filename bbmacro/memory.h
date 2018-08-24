#ifndef BBMACRO_MEMORY_H_
#define BBMACRO_MEMORY_H_

#ifndef NOINCLUDE
#define NOINCLUDE
#include <string.h>
#include <stdlib.h>
#include <bbmacro/static.h>
#include <bbmacro/vector.h>
#undef NOINCLUDE
#endif

/*
 * Allocate memory. Abort if impossible.
 */
static BBUNUSED void *bbmemory_alloc(size_t len, size_t size)
{
	void *res;
	size_t total = len * size;

	if (total / size != len) /* Check for integer overflow. */
		abort();
	res = malloc(total);
	if (!res && total != 0) /* Check if memory was allocated. */
		abort();
	return res;
}

/*
 * Increase capacity of a container logarithmically.
 * The base is chosen smaller than the golden ratio.
 * Theoretically, it helps to re-use memory (not tested).
 */
static BBUNUSED size_t bbmemory_increase(size_t cap)
{
	if (cap <= 3) {
		return cap + 1;
	} else {
		size_t newcap = cap + (cap >> 1); /* Multiply by 3/2. */
		if (newcap <= cap) /* Check for integer overflow. */
			abort();
		return newcap;
	}
}

/* Backward Vector. */

#define BVECTOR_DEFAULT_IMPLEMENTATION(BV, ELEMENT) \
	BVECTOR_IMPLEMENTATION(BV, ELEMENT, \
		bbmemory_alloc, free, bbmemory_increase)

#define BVECTOR_DEFAULT(BV, ELEMENT) \
	BVECTOR(BV, ELEMENT, bbmemory_alloc, free, bbmemory_increase)

/* Forward Vector. */

#define FVECTOR_DEFAULT_IMPLEMENTATION(FV, ELEMENT) \
	FVECTOR_IMPLEMENTATION(FV, ELEMENT, \
		bbmemory_alloc, free, bbmemory_increase)

#define FVECTOR_DEFAULT(FV, ELEMENT) \
	FVECTOR(FV, ELEMENT, bbmemory_alloc, free, bbmemory_increase)

/****************************************
 * Legacy.
 ****************************************/

#define bbmacro_alloc    bbmemory_alloc
#define bbmacro_increase bbmemory_increase

#define BBSTATIC_BVECTOR BVECTOR_DEFAULT
#define BBSTATIC_FVECTOR FVECTOR_DEFAULT

#endif
