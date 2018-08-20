#ifndef BBMACRO_STATIC_H_
#define BBMACRO_STATIC_H_

/****************************************
 * Portable attributes.
 * Please do not depend on certain compilers.
 ****************************************/

/* Specifier to put before a never-returning function. */
#if __STDC_VERSION__ >= 201112L /* C11. */
#  define BBNORETURN _Noreturn
#elif defined(__GNUC__)
#  define BBNORETURN __attribute__((noreturn))
#else
#  define BBNORETURN
#endif

/* Specifier to put before an inline function. */
#if __STDC_VERSION__ >= 199901L /* C99. */
#  define BBINLINE inline
#elif defined(__GNUC__)
#  define BBINLINE __inline__
#else
#  define BBINLINE
#endif

/* Attribute for suppressing warning about something unused. */
#if defined(__GNUC__)
#  define BBUNUSED __attribute__((unused))
#else
#  define BBUNUSED
#endif

/* Attribute for producing warning about something deprecated. */
#if defined(__GNUC__)
#  define BBDEPRECATED __attribute__((deprecated))
#else
#  define BBDEPRECATED
#endif

/****************************************
 * Declaration-like macros.
 * PUT THEM WHERE A DECLARATION CAN BE PUT!
 ****************************************/

/* Produce a compilation error if a condition is not met. */
#define bbstatic_assert(condition) \
	extern char (*bbstatic_assert())[sizeof(char [!!(condition) * 2 - 1])]

/* Produce a compilation error if there is no semicolon.
 * It is usually put at the end of a macro definition. */
#define bbstatic_semicolon \
	extern int bbstatic_semicolon()

/****************************************
 * Stringification macros.
 ****************************************/

/* Stringify the result of a macro-expansion. */
#define bbstatic_str(expanded) #expanded
#define bbstatic_xstr(argument) bbstatic_str(argument)

/****************************************
 * Data processing macros.
 ****************************************/

/*
 * The length and the end of a static array.
 * DO NOT APPLY TO A POINTER!
 */
#define bbstatic_len(array) (sizeof(array) / sizeof((array)[0]))
#define bbstatic_end(array) (&(array)[bbstatic_len((array))])

/*
 * Calculate the offset of a structure/union member.
 * The return type is `ptrdiff_t`, not `size_t`.
 */
#define bbstatic_offsetof(type, member) \
	((char *)(&((type *)0)->member) - (char *)0)

/*
 * Calculate the structure/union address, given its member address.
 * It makes type-checking and sets the value of `*deriv` so that
 * &(*deriv)->member == ptr
 * (Compare with the `container_of()` Linux macro.)
 * Usage:
 * struct { int m; } x, *y;
 * bbstatic_cast(&x.m, &y, m);
 */
#define bbstatic_cast(ptr, deriv, member) \
do { \
	__typeof__((*(deriv))->member) *bbstatic_cast_ptr_ = (ptr); \
	*(deriv) = (__typeof__(*(deriv))) \
		((char *)bbstatic_cast_ptr_ - \
		bbstatic_offsetof(__typeof__(**(deriv)), member)); \
} while (0)

/*
 * Swap `*ptr1` and `*ptr2`.
 * Their types must be mutually convertable.
 * Usage:
 * int a, b;
 * bbstatic_swap(&a, &b);
 */
#define bbstatic_swap(ptr1, ptr2) \
do { \
	__typeof__(*(ptr1)) *bbstatic_swap_ptr1_ = (ptr1); \
	__typeof__(*(ptr2)) *bbstatic_swap_ptr2_ = (ptr2), \
		tmp = *bbstatic_swap_ptr2_; \
	*bbstatic_swap_ptr2_ = *bbstatic_swap_ptr1_; \
	*bbstatic_swap_ptr1_ = tmp; \
} while (0)

#endif
