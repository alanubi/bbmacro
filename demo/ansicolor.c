#include <stdio.h>
#include <bbmacro/ansicolor.h>

#define style(code) \
	fputs("  [" ANSICOLOR_1(code, "A text") "] " #code, stdout)

int main(void)
{
	puts(ANSICOLOR_1(BOLD, "Widely supported colors."));

	style(K); style(BG_K); putchar('\n');
	style(R); style(BG_R); putchar('\n');
	style(G); style(BG_G); putchar('\n');
	style(Y); style(BG_Y); putchar('\n');
	style(B); style(BG_B); putchar('\n');
	style(M); style(BG_M); putchar('\n');
	style(C); style(BG_C); putchar('\n');
	style(W); style(BG_W); putchar('\n');

	puts(ANSICOLOR_1(BOLD, "Not widely supported colors."));

	style(KX); style(BG_KX); putchar('\n');
	style(RX); style(BG_RX); putchar('\n');
	style(GX); style(BG_GX); putchar('\n');
	style(YX); style(BG_YX); putchar('\n');
	style(BX); style(BG_BX); putchar('\n');
	style(MX); style(BG_MX); putchar('\n');
	style(CX); style(BG_CX); putchar('\n');
	style(WX); style(BG_WX); putchar('\n');

	puts(ANSICOLOR_1(BOLD, "Default colors."));

	style(OFF); style(BG_OFF); putchar('\n');

	puts(ANSICOLOR_1(BOLD, "Miscellaneous font styles."));

	style(BOLD  ); style(BOLD_OFF  ); putchar('\n');
	style(FAINT ); style(FAINT_OFF ); putchar('\n');
	style(ITALIC); style(ITALIC_OFF); putchar('\n');
	style(UNDER ); style(UNDER_OFF ); putchar('\n');
	style(BLINK ); style(BLINK_OFF ); putchar('\n');
	style(RAPID ); style(RAPID_OFF ); putchar('\n');
	style(INVERT); style(INVERT_OFF); putchar('\n');
	style(HIDDEN); style(HIDDEN_OFF); putchar('\n');
	style(STRIKE); style(STRIKE_OFF); putchar('\n');

	puts(ANSICOLOR_1(BOLD, "Special codes."));

	style(SHOW  ); style(RESET ); putchar('\n');

	puts(ANSICOLOR_1(BOLD, "Examples of multiple attributes."));

	puts("  [" ANSICOLOR_0(
		"Sample text") "] "
		"0: -");

	puts("  [" ANSICOLOR_2(BOLD, G,
		"Sample text") "] "
		"2: BOLD-G");

	puts("  [" ANSICOLOR_3(STRIKE, INVERT, BG_B,
		"Sample text") "] "
		"3: STRIKE-INVERT-BG_B");

	puts("  [" ANSICOLOR_4(UNDER, BOLD, INVERT, Y,
		"Sample text") "] "
		"4: UNDER-BOLD-INVERT-Y");

	puts("  [" ANSICOLOR_2(STRIKE, UNDER, ANSICOLOR_3(BOLD, C, BG_M,
		"Sample text")) "] "
		"2+3: STRIKE-UNDER-BOLD-C-BG_M");

	return 0;
}
