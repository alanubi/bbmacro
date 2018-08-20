#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <bbmacro/static.h>
#include <bbmacro/vector.h>
#include <bbmacro/memory.h>

int a[10], *a_end = bbstatic_end(a);
bbstatic_assert(10 == bbstatic_len(a));

BBDECLARE_BVECTOR(bpub, int, extern);
BBDECLARE_FVECTOR(fpub, int, extern);

BBDEFINE_BVECTOR(bpub, int, bbmacro_alloc, free, bbmacro_increase);
BBDEFINE_FVECTOR(fpub, int, bbmacro_alloc, free, bbmacro_increase);

BBSTATIC_BVECTOR(bpriv, int);
BBSTATIC_FVECTOR(fpriv, int);
