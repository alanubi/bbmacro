#ifndef ANSICOLOR_H_
#define ANSICOLOR_H_

/****************************************
 * ANSI font style escape codes.
 ****************************************/

/* Standard foreground colors. */
#define ANSICOLOR_CODE_K "30"
#define ANSICOLOR_CODE_R "31"
#define ANSICOLOR_CODE_G "32"
#define ANSICOLOR_CODE_Y "33"
#define ANSICOLOR_CODE_B "34"
#define ANSICOLOR_CODE_M "35"
#define ANSICOLOR_CODE_C "36"
#define ANSICOLOR_CODE_W "37"

/* Bright AIX foreground colors (not widely supported). */
#define ANSICOLOR_CODE_KX "90"
#define ANSICOLOR_CODE_RX "91"
#define ANSICOLOR_CODE_GX "92"
#define ANSICOLOR_CODE_YX "93"
#define ANSICOLOR_CODE_BX "94"
#define ANSICOLOR_CODE_MX "95"
#define ANSICOLOR_CODE_CX "96"
#define ANSICOLOR_CODE_WX "97"

/* Default foreground color. */
#define ANSICOLOR_CODE_OFF "39"

/* Standard background colors. */
#define ANSICOLOR_CODE_BG_K "40"
#define ANSICOLOR_CODE_BG_R "41"
#define ANSICOLOR_CODE_BG_G "42"
#define ANSICOLOR_CODE_BG_Y "43"
#define ANSICOLOR_CODE_BG_B "44"
#define ANSICOLOR_CODE_BG_M "45"
#define ANSICOLOR_CODE_BG_C "46"
#define ANSICOLOR_CODE_BG_W "47"

/* Bright AIX background colors (not widely supported). */
#define ANSICOLOR_CODE_BG_KX "100"
#define ANSICOLOR_CODE_BG_RX "101"
#define ANSICOLOR_CODE_BG_GX "102"
#define ANSICOLOR_CODE_BG_YX "103"
#define ANSICOLOR_CODE_BG_BX "104"
#define ANSICOLOR_CODE_BG_MX "105"
#define ANSICOLOR_CODE_BG_CX "106"
#define ANSICOLOR_CODE_BG_WX "107"

/* Default background color. */
#define ANSICOLOR_CODE_BG_OFF "49"

/* Miscellaneous font styles. */
#define ANSICOLOR_CODE_BOLD   "1" /* Widely supported. */
#define ANSICOLOR_CODE_FAINT  "2"
#define ANSICOLOR_CODE_ITALIC "3"
#define ANSICOLOR_CODE_UNDER  "4"
#define ANSICOLOR_CODE_BLINK  "5"
#define ANSICOLOR_CODE_RAPID  "6"
#define ANSICOLOR_CODE_INVERT "7" /* Widely supported. */
#define ANSICOLOR_CODE_HIDDEN "8"
#define ANSICOLOR_CODE_STRIKE "9"

/* Miscellaneous font styles' negations. */
#define ANSICOLOR_CODE_BOLD_OFF   "21"
#define ANSICOLOR_CODE_FAINT_OFF  "22"
#define ANSICOLOR_CODE_ITALIC_OFF "23"
#define ANSICOLOR_CODE_UNDER_OFF  "24"
#define ANSICOLOR_CODE_BLINK_OFF  "25"
#define ANSICOLOR_CODE_RAPID_OFF  "26" /* Hypothetical. */
#define ANSICOLOR_CODE_INVERT_OFF "27"
#define ANSICOLOR_CODE_HIDDEN_OFF "28"
#define ANSICOLOR_CODE_STRIKE_OFF "29"

/* Surrogate for zero-effect font style. */
#define ANSICOLOR_CODE_SHOW "28"

/* Special code for resetting all effects. */
#define ANSICOLOR_CODE_RESET "0"

/* Universal code with the same prefix as the other codes. */
#define ANSICOLOR_CODE_N(codenumber) #codenumber

/****************************************
 * Auxiliary macros.
 ****************************************/

/*
 * Take a style (a code name without the `ANSICOLOR_CODE_` prefix)
 * and return its code. Examples:
 * ANSICOLOR_CODE(BOLD) is "1"
 * ANSICOLOR_CODE(N(100)) is "100"
 */
#define ANSICOLOR_CODE(style) ANSICOLOR_CODE_## style

/*
 * Take a specified number of styles and return the font
 * (a quoted list of semicolon-separated codes). Example:
 * ANSICOLOR_FONT_4(BOLD, G, BG_Y, N(4)) is "1;32;43;4"
 */
#define ANSICOLOR_FONT_1(style1) \
	ANSICOLOR_CODE(style1)

#define ANSICOLOR_FONT_2(style1, style2) \
	ANSICOLOR_CODE(style1) ";" ANSICOLOR_FONT_1(style2)

#define ANSICOLOR_FONT_3(style1, style2, style3) \
	ANSICOLOR_CODE(style1) ";" ANSICOLOR_FONT_2(style2, style3)

#define ANSICOLOR_FONT_4(style1, style2, style3, style4) \
	ANSICOLOR_CODE(style1) ";" ANSICOLOR_FONT_3(style2, style3, style4)

/****************************************
 * Low-level macros.
 * Font styles can be disabled overall
 * by defining ANSICOLOR_OFF.
 ****************************************/

/*
 * Set the font. Reset the font. Examples:
 * puts(ANSICOLOR_SET("1;32") "Text" ANSICOLOR_RESET());
 * puts(ANSICOLOR_SET(ANSICOLOR_FONT_2(BOLD, G)) "Text" ANSICOLOR_RESET());
 * puts(ANSICOLOR_SET_2(BOLD, G) "Text" ANSICOLOR_RESET());
 */
#ifndef ANSICOLOR_OFF
#  define ANSICOLOR_SET(font) "\x1b[" font "m"
#else
#  define ANSICOLOR_SET(font) ""
#endif

#define ANSICOLOR_SET_0() \
	""

#define ANSICOLOR_SET_1(style1) \
	ANSICOLOR_SET(ANSICOLOR_FONT_1(style1))

#define ANSICOLOR_SET_2(style1, style2) \
	ANSICOLOR_SET(ANSICOLOR_FONT_2(style1, style2))

#define ANSICOLOR_SET_3(style1, style2, style3) \
	ANSICOLOR_SET(ANSICOLOR_FONT_3(style1, style2, style3))

#define ANSICOLOR_SET_4(style1, style2, style3, style4) \
	ANSICOLOR_SET(ANSICOLOR_FONT_4(style1, style2, style3, style4))

#define ANSICOLOR_RESET() ANSICOLOR_SET(ANSICOLOR_CODE(RESET))

/****************************************
 * High-level macros.
 * They may be nested, but remember:
 * THEIR CLOSING PARENTHESES MUST ADJOIN!
 ****************************************/

/*
 * Apply the font to a string literal. Examples:
 * puts(ANSICOLOR("1;32", "[ok]") " No style here.");
 * puts(ANSICOLOR(ANSICOLOR_FONT_2(BOLD, G), "[ok]") " No style here.");
 * puts(ANSICOLOR_2(BOLD, G, "[ok]") " No style here.");
 */
#define ANSICOLOR(font, string) \
	ANSICOLOR_SET(font) string ANSICOLOR_RESET()

#define ANSICOLOR_0(string) \
	ANSICOLOR_SET_0() string ANSICOLOR_RESET()

#define ANSICOLOR_1(style1, string) \
	ANSICOLOR_SET_1(style1) string ANSICOLOR_RESET()

#define ANSICOLOR_2(style1, style2, string) \
	ANSICOLOR_SET_2(style1, style2) string ANSICOLOR_RESET()

#define ANSICOLOR_3(style1, style2, style3, string) \
	ANSICOLOR_SET_3(style1, style2, style3) string ANSICOLOR_RESET()

#define ANSICOLOR_4(style1, style2, style3, style4, string) \
	ANSICOLOR_SET_4(style1, style2, style3, style4) string ANSICOLOR_RESET()

#endif
