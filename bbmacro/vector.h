#ifndef BBMACRO_VECTOR_H_
#define BBMACRO_VECTOR_H_

#ifndef NOINCLUDE
#define NOINCLUDE
#include <string.h>
#include <bbmacro/static.h>
#undef NOINCLUDE
#endif

/*
 * Vector data structure.
 * 1. A type-creating macro has a prefix:
 *    `B` (Backward) -- push elements into the back end;
 *    `F` (Forward)  -- push elements into the front end;
 *    `Q` (Queue)    -- push elements into the both ends.
 * 2. Core procedures provide manual memory management only.
 * 3. Structure members are a read-only part of the interface.
 *    You are to access the members, but do not modify them directly.
 * 4. Note the vector itself is always the last argument of a procedure.
 */

/*
 * How to call the macro?
 * 1. Usually you need a specific type for just one source file:
 *    BVECTOR_CORE(myvector, int);
 *
 * 2. Often you need to separate interface and implementation:
 *    ... in a header file ...
 *    BVECTOR_CORE_INTERFACE(myvector, int, extern);
 *    ... in a source file ...
 *    BVECTOR_CORE_IMPLEMENTATION(myvector, int);
 *
 * 3. Sometimes you need recursive data structures:
 *    ... in a header file ...
 *    struct item;
 *    BVECTOR_STRUCT(myvector, struct item);
 *    struct item { struct myvector v; ... };
 *    BVECTOR_CORE_DECLARATIONS(myvector, struct item, extern);
 *    ... in a source file ...
 *    BVECTOR_CORE_IMPLEMENTATION(myvector, struct item);
 *
 * 4. For BVECTOR (with automatic memory management) everything is the same,
 *    except for the missing `_CORE` suffix and for the additional arguments
 *    necessary to implement memory management. You can find them in the file
 *    `memory.h`.
 */

/*
 * How to use the vector?
 * Consider we have used `BVECTOR_CORE_INTERFACE(myvector, int, extern);`.
 * The macro expansion will be the following:
 * struct myvector {
 *   size_t len, cap;
 *   int *at;
 * };
 * extern void myvector_init(int *array, size_t cap, struct myvector *bv);
 * extern int *myvector_fini(struct myvector *bv);
 * ...
 * The detailed documentation is in progress.
 */

/****************************************
 * Backward Vector interface.
 ****************************************/

/* Backward Vector structure. */
#define BVECTOR_STRUCT(BV, ELEMENT) \
\
struct BV { \
	size_t len, cap; /* Length and capacity. */ \
	ELEMENT *at; /* Beginning of memory and data. */ \
}

/* Backward Vector core procedures. */
#define BVECTOR_CORE_DECLARATIONS(BV, ELEMENT, PREFIX) \
\
PREFIX void BV##_init(ELEMENT *array, size_t cap, struct BV *bv); \
PREFIX ELEMENT *BV##_fini(struct BV *bv); \
PREFIX void BV##_clear(struct BV *bv); \
PREFIX int BV##_full(struct BV *bv); \
PREFIX ELEMENT *BV##_neg(size_t num, struct BV *bv); \
\
PREFIX ELEMENT *BV##_reserveback(ELEMENT *array, size_t cap, struct BV *bv); \
PREFIX void BV##_pushback(ELEMENT value, struct BV *bv); \
PREFIX ELEMENT *BV##_growback(size_t num, struct BV *bv); \
PREFIX void BV##_popback(struct BV *bv); \
PREFIX void BV##_cutback(size_t num, struct BV *bv); \
PREFIX void BV##_resizeback(size_t len, struct BV *bv); \
PREFIX ELEMENT *BV##_back(struct BV *bv); \
bbstatic_semicolon

/* Backward Vector automatic memory management appendix. */
#define BVECTOR_AUTO_DECLARATIONS(BV, ELEMENT, PREFIX) \
\
PREFIX void BV##_ainit(size_t cap, struct BV *bv); \
PREFIX void BV##_afini(struct BV *bv); \
PREFIX void BV##_aclear(struct BV *bv); \
\
PREFIX void BV##_areserveback(size_t cap, struct BV *bv); \
PREFIX void BV##_apushback(ELEMENT value, struct BV *bv); \
PREFIX ELEMENT *BV##_agrowback(size_t num, struct BV *bv); \
PREFIX void BV##_aresizeback(size_t len, struct BV *bv); \
bbstatic_semicolon

/* Backward Vector automatic memory management procedures. */
#define BVECTOR_DECLARATIONS(BV, ELEMENT, PREFIX) \
	BVECTOR_CORE_DECLARATIONS(BV, ELEMENT, PREFIX); \
	BVECTOR_AUTO_DECLARATIONS(BV, ELEMENT, PREFIX)

/* Backward Vector core interface. */
#define BVECTOR_CORE_INTERFACE(BV, ELEMENT, PREFIX) \
	BVECTOR_STRUCT(BV, ELEMENT); \
	BVECTOR_CORE_DECLARATIONS(BV, ELEMENT, PREFIX)

/* Backward Vector automatic memory management interface. */
#define BVECTOR_INTERFACE(BV, ELEMENT, PREFIX) \
	BVECTOR_STRUCT(BV, ELEMENT); \
	BVECTOR_DECLARATIONS(BV, ELEMENT, PREFIX)

/****************************************
 * Forward Vector interface.
 ****************************************/

/* Forward Vector structure. */
#define FVECTOR_STRUCT(FV, ELEMENT) \
\
struct FV { \
	size_t len, cap; /* Length and capacity. */ \
	ELEMENT *neg; /* End of memory and data. */ \
}

/* Forward Vector core procedures. */
#define FVECTOR_CORE_DECLARATIONS(FV, ELEMENT, PREFIX) \
\
PREFIX void FV##_init(ELEMENT *array, size_t cap, struct FV *fv); \
PREFIX ELEMENT *FV##_fini(struct FV *fv); \
PREFIX void FV##_clear(struct FV *fv); \
PREFIX int FV##_full(struct FV *fv); \
PREFIX ELEMENT *FV##_at(size_t num, struct FV *fv); \
\
PREFIX ELEMENT *FV##_reservefront(ELEMENT *array, size_t cap, struct FV *fv); \
PREFIX void FV##_pushfront(ELEMENT value, struct FV *fv); \
PREFIX ELEMENT *FV##_growfront(size_t num, struct FV *fv); \
PREFIX void FV##_popfront(struct FV *fv); \
PREFIX void FV##_cutfront(size_t num, struct FV *fv); \
PREFIX void FV##_resizefront(size_t len, struct FV *fv); \
PREFIX ELEMENT *FV##_front(struct FV *fv); \
bbstatic_semicolon

/* Forward Vector automatic memory management appendix. */
#define FVECTOR_AUTO_DECLARATIONS(FV, ELEMENT, PREFIX) \
\
PREFIX void FV##_ainit(size_t cap, struct FV *fv); \
PREFIX void FV##_afini(struct FV *fv); \
PREFIX void FV##_aclear(struct FV *fv); \
\
PREFIX void FV##_areservefront(size_t cap, struct FV *fv); \
PREFIX void FV##_apushfront(ELEMENT value, struct FV *fv); \
PREFIX ELEMENT *FV##_agrowfront(size_t num, struct FV *fv); \
PREFIX void FV##_aresizefront(size_t len, struct FV *fv); \
bbstatic_semicolon

/* Forward Vector automatic memory management procedures. */
#define FVECTOR_DECLARATIONS(FV, ELEMENT, PREFIX) \
	FVECTOR_CORE_DECLARATIONS(FV, ELEMENT, PREFIX); \
	FVECTOR_AUTO_DECLARATIONS(FV, ELEMENT, PREFIX)

/* Forward Vector core interface. */
#define FVECTOR_CORE_INTERFACE(FV, ELEMENT, PREFIX) \
	FVECTOR_STRUCT(FV, ELEMENT); \
	FVECTOR_CORE_DECLARATIONS(FV, ELEMENT, PREFIX)

/* Forward Vector automatic memory management interface. */
#define FVECTOR_INTERFACE(FV, ELEMENT, PREFIX) \
	FVECTOR_STRUCT(FV, ELEMENT); \
	FVECTOR_DECLARATIONS(FV, ELEMENT, PREFIX)

/****************************************
 * Backward Vector implementation.
 ****************************************/

/* Backward Vector core procedures. */
#define BVECTOR_CORE_IMPLEMENTATION(BV, ELEMENT) \
\
void BV##_init(ELEMENT *array, size_t cap, struct BV *bv) \
{	bv->at = array; \
	bv->len = 0; \
	bv->cap = cap; \
} \
ELEMENT *BV##_fini(struct BV *bv) \
{	return bv->at; \
} \
void BV##_clear(struct BV *bv) \
{	bv->len = 0; \
} \
int BV##_full(struct BV *bv) \
{	return bv->len == bv->cap; \
} \
ELEMENT *BV##_neg(size_t num, struct BV *bv) \
{	return &bv->at[bv->len - num]; \
} \
ELEMENT *BV##_reserveback(ELEMENT *array, size_t cap, struct BV *bv) \
{	ELEMENT *old = bv->at; \
	memcpy(array, old, sizeof(ELEMENT) * bv->len); \
	bv->at = array; \
	bv->cap = cap; \
	return old; \
} \
void BV##_pushback(ELEMENT value, struct BV *bv) \
{	bv->at[bv->len++] = value; \
} \
ELEMENT *BV##_growback(size_t num, struct BV *bv) \
{	ELEMENT *old = &bv->at[bv->len]; \
	bv->len += num; \
	return old; \
} \
void BV##_popback(struct BV *bv) \
{	bv->len--; \
} \
void BV##_cutback(size_t num, struct BV *bv) \
{	bv->len -= num; \
} \
void BV##_resizeback(size_t len, struct BV *bv) \
{	bv->len = len; \
} \
ELEMENT *BV##_back(struct BV *bv) \
{	return &bv->at[bv->len - 1]; \
} \
bbstatic_semicolon

/* Backward Vector automatic memory management appendix. */
#define BVECTOR_AUTO_IMPLEMENTATION(BV, ELEMENT, ALLOC, FREE, NEXT_CAP) \
\
void BV##_ainit(size_t cap, struct BV *bv) \
{	ELEMENT *ptr = ALLOC(cap, sizeof(ELEMENT)); \
	BV##_init(ptr, cap, bv); \
} \
void BV##_afini(struct BV *bv) \
{	FREE(BV##_fini(bv)); \
} \
void BV##_aclear(struct BV *bv) \
{	FREE(bv->at); \
	bv->at = NULL; \
	bv->len = 0; \
	bv->cap = 0; \
} \
void BV##_areserveback(size_t cap, struct BV *bv) \
{	ELEMENT *ptr = ALLOC(cap, sizeof(ELEMENT)); \
	FREE(BV##_reserveback(ptr, cap, bv)); \
} \
void BV##_apushback(ELEMENT value, struct BV *bv) \
{	if (BV##_full(bv)) \
		BV##_areserveback(NEXT_CAP(bv->cap), bv); \
	BV##_pushback(value, bv); \
} \
ELEMENT *BV##_agrowback(size_t num, struct BV *bv) \
{	size_t len = bv->len + num; \
	size_t cap = bv->cap; \
	if (len > cap) { \
		cap = NEXT_CAP(cap); \
		if (len > cap) \
			cap = len; \
		BV##_areserveback(cap, bv); \
	} \
	return BV##_growback(num, bv); \
} \
void BV##_aresizeback(size_t len, struct BV *bv) \
{	size_t cap = bv->cap; \
	if (len > cap) { \
		cap = NEXT_CAP(cap); \
		if (len > cap) \
			cap = len; \
		BV##_areserveback(cap, bv); \
	} \
	bv->len = len; \
} \
bbstatic_semicolon

/* Backward Vector automatic memory management procedures. */
#define BVECTOR_IMPLEMENTATION(BV, ELEMENT, ALLOC, FREE, NEXT_CAP) \
	BVECTOR_CORE_IMPLEMENTATION(BV, ELEMENT); \
	BVECTOR_AUTO_IMPLEMENTATION(BV, ELEMENT, ALLOC, FREE, NEXT_CAP)

/* Backward Vector core full. */
#define BVECTOR_CORE(BV, ELEMENT) \
	BVECTOR_CORE_INTERFACE(BV, ELEMENT, static BBUNUSED); \
	BVECTOR_CORE_IMPLEMENTATION(BV, ELEMENT)

/* Backward Vector automatic memory management full. */
#define BVECTOR(BV, ELEMENT, ALLOC, FREE, NEXT_CAP) \
	BVECTOR_INTERFACE(BV, ELEMENT, static BBUNUSED); \
	BVECTOR_IMPLEMENTATION(BV, ELEMENT, ALLOC, FREE, NEXT_CAP)

/****************************************
 * Forward Vector implementation.
 ****************************************/

/* Forward Vector core procedures. */
#define FVECTOR_CORE_IMPLEMENTATION(FV, ELEMENT) \
\
void FV##_init(ELEMENT *array, size_t cap, struct FV *fv) \
{	fv->neg = array + cap; \
	fv->len = 0; \
	fv->cap = cap; \
} \
ELEMENT *FV##_fini(struct FV *fv) \
{	return fv->neg - fv->cap; \
} \
void FV##_clear(struct FV *fv) \
{	fv->len = 0; \
} \
int FV##_full(struct FV *fv) \
{	return fv->len == fv->cap; \
} \
ELEMENT *FV##_at(size_t num, struct FV *fv) \
{	return &(fv->neg - fv->len)[num]; \
} \
ELEMENT *FV##_reservefront(ELEMENT *array, size_t cap, struct FV *fv) \
{	ELEMENT *old = fv->neg - fv->cap; \
	ELEMENT *end = array + cap; \
	size_t len = fv->len; \
	memcpy(end - len, fv->neg - len, sizeof(ELEMENT) * len); \
	fv->neg = end; \
	fv->cap = cap; \
	return old; \
} \
void FV##_pushfront(ELEMENT value, struct FV *fv) \
{	*(fv->neg - (++fv->len)) = value; \
} \
ELEMENT *FV##_growfront(size_t num, struct FV *fv) \
{	fv->len += num; \
	return fv->neg - fv->len; \
} \
void FV##_popfront(struct FV *fv) \
{	fv->len--; \
} \
void FV##_cutfront(size_t num, struct FV *fv) \
{	fv->len -= num; \
} \
void FV##_resizefront(size_t len, struct FV *fv) \
{	fv->len = len; \
} \
ELEMENT *FV##_front(struct FV *fv) \
{	return fv->neg - fv->len; \
} \
bbstatic_semicolon

/* Forward Vector automatic memory management appendix. */
#define FVECTOR_AUTO_IMPLEMENTATION(FV, ELEMENT, ALLOC, FREE, NEXT_CAP) \
\
void FV##_ainit(size_t cap, struct FV *fv) \
{	ELEMENT *ptr = ALLOC(cap, sizeof(ELEMENT)); \
	FV##_init(ptr, cap, fv); \
} \
void FV##_afini(struct FV *fv) \
{	FREE(FV##_fini(fv)); \
} \
void FV##_aclear(struct FV *fv) \
{	FREE(fv->neg - fv->cap); \
	fv->neg = NULL; \
	fv->len = 0; \
	fv->cap = 0; \
} \
void FV##_areservefront(size_t cap, struct FV *fv) \
{	ELEMENT *ptr = ALLOC(cap, sizeof(ELEMENT)); \
	FREE(FV##_reservefront(ptr, cap, fv)); \
} \
void FV##_apushfront(ELEMENT value, struct FV *fv) \
{	if (FV##_full(fv)) \
		FV##_areservefront(NEXT_CAP(fv->cap), fv); \
	FV##_pushfront(value, fv); \
} \
ELEMENT *FV##_agrowfront(size_t num, struct FV *fv) \
{	size_t len = fv->len + num; \
	size_t cap = fv->cap; \
	if (len > cap) { \
		cap = NEXT_CAP(cap); \
		if (len > cap) \
			cap = len; \
		FV##_areservefront(cap, fv); \
	} \
	return FV##_growfront(num, fv); \
} \
void FV##_aresizefront(size_t len, struct FV *fv) \
{	size_t cap = fv->cap; \
	if (len > cap) { \
		cap = NEXT_CAP(cap); \
		if (len > cap) \
			cap = len; \
		FV##_areservefront(cap, fv); \
	} \
	fv->len = len; \
} \
bbstatic_semicolon

/* Forward Vector automatic memory management procedures. */
#define FVECTOR_IMPLEMENTATION(FV, ELEMENT, ALLOC, FREE, NEXT_CAP) \
	FVECTOR_CORE_IMPLEMENTATION(FV, ELEMENT); \
	FVECTOR_AUTO_IMPLEMENTATION(FV, ELEMENT, ALLOC, FREE, NEXT_CAP)

/* Forward Vector core full. */
#define FVECTOR_CORE(FV, ELEMENT) \
	FVECTOR_CORE_INTERFACE(FV, ELEMENT, static BBUNUSED); \
	FVECTOR_CORE_IMPLEMENTATION(FV, ELEMENT)

/* Forward Vector automatic memory management full. */
#define FVECTOR(FV, ELEMENT, ALLOC, FREE, NEXT_CAP) \
	FVECTOR_INTERFACE(FV, ELEMENT, static BBUNUSED); \
	FVECTOR_IMPLEMENTATION(FV, ELEMENT, ALLOC, FREE, NEXT_CAP)

/****************************************
 * Legacy.
 ****************************************/

#define BBDECLARE_MBVECTOR BVECTOR_CORE_INTERFACE
#define BBDECLARE_MFVECTOR FVECTOR_CORE_INTERFACE
#define BBDEFINE_MBVECTOR  BVECTOR_CORE_IMPLEMENTATION
#define BBDEFINE_MFVECTOR  FVECTOR_CORE_IMPLEMENTATION

#define BBDECLARE_ABVECTOR BVECTOR_AUTO_DECLARATIONS
#define BBDECLARE_AFVECTOR FVECTOR_AUTO_DECLARATIONS
#define BBDEFINE_ABVECTOR  BVECTOR_AUTO_IMPLEMENTATION
#define BBDEFINE_AFVECTOR  FVECTOR_AUTO_IMPLEMENTATION

#define BBDECLARE_BVECTOR  BVECTOR_INTERFACE
#define BBDECLARE_FVECTOR  FVECTOR_INTERFACE
#define BBDEFINE_BVECTOR   BVECTOR_IMPLEMENTATION
#define BBDEFINE_FVECTOR   FVECTOR_IMPLEMENTATION

#endif
