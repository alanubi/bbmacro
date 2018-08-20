#ifndef BBMACRO_VECTOR_H_
#define BBMACRO_VECTOR_H_

#ifndef NOINCLUDE
#define NOINCLUDE
#include <stddef.h>
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
 * 2. A type-creating macro has one more prefix:
 *    `M` (Manual)    -- manual memory management;
 *    `A` (Automatic) -- automatic memory management appendix;
 *    `-` (None)      -- automatic memory management (all-in-one).
 * 3. Structure members are a read-only part of the interface.
 *    You are to access the members, but do not modify them directly.
 * 4. Note the vector itself is always the last argument of a procedure.
 */

/****************************************
 * Manual memory management (`M` prefix).
 ****************************************/

/* Manual Backward Vector interface. */
#define BBDECLARE_MBVECTOR(BV, ELEMENT, PREFIX) \
\
struct BV { \
	size_t len, cap; /* Length and capacity. */ \
	ELEMENT *at; /* Beginning of memory and data. */ \
}; \
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

/* Manual Forward Vector interface. */
#define BBDECLARE_MFVECTOR(FV, ELEMENT, PREFIX) \
\
struct FV { \
	size_t len, cap; /* Length and capacity. */ \
	ELEMENT *neg; /* End of memory and data. */ \
}; \
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

/* Manual Backward Vector implementation. */
#define BBDEFINE_MBVECTOR(BV, ELEMENT) \
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

/* Manual Forward Vector implementation. */
#define BBDEFINE_MFVECTOR(FV, ELEMENT) \
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

/****************************************
 * Automatic memory management appendix (`A` prefix).
 ****************************************/

/* Automatic Backward Vector interface. */
#define BBDECLARE_ABVECTOR(BV, ELEMENT, PREFIX) \
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

/* Automatic Forward Vector interface. */
#define BBDECLARE_AFVECTOR(FV, ELEMENT, PREFIX) \
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

/* Automatic Backward Vector implementation. */
#define BBDEFINE_ABVECTOR(BV, ELEMENT, ALLOC, FREE, NEXT_CAP) \
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

/* Automatic Forward Vector implementation. */
#define BBDEFINE_AFVECTOR(FV, ELEMENT, ALLOC, FREE, NEXT_CAP) \
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

/****************************************
 * Unite manual and automatic memory management (No prefix).
 ****************************************/

#define BBDECLARE_BVECTOR(BV, ELEMENT, PREFIX) \
	BBDECLARE_MBVECTOR(BV, ELEMENT, PREFIX); \
	BBDECLARE_ABVECTOR(BV, ELEMENT, PREFIX)

#define BBDECLARE_FVECTOR(FV, ELEMENT, PREFIX) \
	BBDECLARE_MFVECTOR(FV, ELEMENT, PREFIX); \
	BBDECLARE_AFVECTOR(FV, ELEMENT, PREFIX)

#define BBDEFINE_BVECTOR(BV, ELEMENT, ALLOC, FREE, NEXT_CAP) \
	BBDEFINE_MBVECTOR(BV, ELEMENT); \
	BBDEFINE_ABVECTOR(BV, ELEMENT, ALLOC, FREE, NEXT_CAP)

#define BBDEFINE_FVECTOR(FV, ELEMENT, ALLOC, FREE, NEXT_CAP) \
	BBDEFINE_MFVECTOR(FV, ELEMENT); \
	BBDEFINE_AFVECTOR(FV, ELEMENT, ALLOC, FREE, NEXT_CAP)

#endif
