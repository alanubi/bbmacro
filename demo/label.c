#include <stdio.h>
#include <bbmacro/label.h>

void A(void)
{
	int value = 0;
	do {
		int square;

		switch (value) {
		when (0) fputs("Zero", stdout);
		when (1) fputs("One" , stdout);
		when (2) fputs("Two" , stdout);
		otherwise fputs("Many", stdout);
		}

		square = value * value;
		SURE (square <= 5, goto endloop);
		puts(" <= sqrt(5)");

		++value;
	} LOOP (endloop);
	puts(" > sqrt(5)");
}

void B(void)
{
	int value = 0;
Next:
	printf("%i: ", value);

	SURE (value % 2 == 0, goto odd);
	SURE (value % 4 == 0, goto even);
	puts("multiple of four");
	SKIP (even) puts("even");
	SKIP (odd) puts("odd");

	SURE (++value == 10, goto Next);
}

int main(void)
{
	puts("Demo A:");
	A();
	puts("Demo B:");
	B();
	return 0;
}
