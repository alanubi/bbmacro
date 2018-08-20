#ifndef BBMACRO_LABEL_H_
#define BBMACRO_LABEL_H_

/****************************************
 * Switch labels.
 ****************************************/

/*
 * How to use non-fallthrough case labels.
 * switch (...) {
 * when (...) ...
 * when (...) ...
 * otherwise ...
 * }
 *
 * How to use regular fallthrough case labels.
 * switch (...) {
 * when (...) and_when (...) and_when (...) ...
 * when (...) and_when (...) and_otherwise ...
 * }
 */

/* Non-fallthrough case labels. */
#define when(x) break; case (x):
#define otherwise break; default:

/* Regular fallthrough case labels. */
#define and_when(x) case (x):
#define and_otherwise default:

/****************************************
 * Conditional jumps.
 ****************************************/

/*
 * How to write a statement-like macro.
 * 1. To be context-independent, a macro should be wrapped in a `do { ... }
 *    while (0)` loop . But when we want to put a `break` or `continue`
 *    statement into the macro body, this way becomes inappropriate.
 * 2. Without the wrapper loop, `if` branch should always be paired with
 *    the `else` branch. Otherwise, the macro would be context-dependent.
 * 3. In the end of a statement-like macro, we need to force the user to put
 *    a semicolon. So we insert the `((void)0)` consturction.
 */

/*
 * Perform an action if a condition is not met. Usage:
 * SURE (..., break);
 * SURE (..., goto label);
 * SURE (..., abort());
 */
#define SURE(condition, action) \
	if (!(condition)) { action; } \
	else ((void)0)

/*
 * A label after the end of an unconditional `do` loop. Usage:
 * do { ... } LOOP (label);
 */
#define LOOP(label) \
	while (1); /* End of the `do` loop. */ \
	label: ((void)0)

/*
 * A label at the beginning of an unconditionally skipped block of code. Usage:
 * SKIP (label) { ... }
 * SKIP (label) ...;
 */
#define SKIP(label) \
	if (1) (void)0; \
	else label:

#endif
