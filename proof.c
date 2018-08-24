#include <string.h>
#include <stdlib.h>
#include <bbmacro/static.h>
#include <bbmacro/vector.h>
#include <bbmacro/memory.h>

int a[10], *a_end = bbstatic_end(a);
bbstatic_assert(10 == bbstatic_len(a));

/* Core. */

BVECTOR_STRUCT(bc3, int);
BVECTOR_CORE_DECLARATIONS(bc3, int, extern);
BVECTOR_CORE_IMPLEMENTATION(bc3, int);
BVECTOR_CORE_INTERFACE(bc2, int, extern);
BVECTOR_CORE_IMPLEMENTATION(bc2, int);
BVECTOR_CORE(bc1, int);

FVECTOR_STRUCT(fc3, int);
FVECTOR_CORE_DECLARATIONS(fc3, int, extern);
FVECTOR_CORE_IMPLEMENTATION(fc3, int);
FVECTOR_CORE_INTERFACE(fc2, int, extern);
FVECTOR_CORE_IMPLEMENTATION(fc2, int);
FVECTOR_CORE(fc1, int);

/* Auto. */

BVECTOR_STRUCT(ba3, int);
BVECTOR_DECLARATIONS(ba3, int, extern);
BVECTOR_IMPLEMENTATION(ba3, int, bbmemory_alloc, free, bbmemory_increase);
BVECTOR_INTERFACE(ba2, int, extern);
BVECTOR_IMPLEMENTATION(ba2, int, bbmemory_alloc, free, bbmemory_increase);
BVECTOR(ba1, int, bbmemory_alloc, free, bbmemory_increase);

FVECTOR_STRUCT(fa3, int);
FVECTOR_DECLARATIONS(fa3, int, extern);
FVECTOR_IMPLEMENTATION(fa3, int, bbmemory_alloc, free, bbmemory_increase);
FVECTOR_INTERFACE(fa2, int, extern);
FVECTOR_IMPLEMENTATION(fa2, int, bbmemory_alloc, free, bbmemory_increase);
FVECTOR(fa1, int, bbmemory_alloc, free, bbmemory_increase);

/* Default auto. */

BVECTOR_STRUCT(bd3, int);
BVECTOR_DECLARATIONS(bd3, int, extern);
BVECTOR_DEFAULT_IMPLEMENTATION(bd3, int);
BVECTOR_INTERFACE(bd2, int, extern);
BVECTOR_DEFAULT_IMPLEMENTATION(bd2, int);
BVECTOR_DEFAULT(bd1, int);

FVECTOR_STRUCT(fd3, int);
FVECTOR_DECLARATIONS(fd3, int, extern);
FVECTOR_DEFAULT_IMPLEMENTATION(fd3, int);
FVECTOR_INTERFACE(fd2, int, extern);
FVECTOR_DEFAULT_IMPLEMENTATION(fd2, int);
FVECTOR_DEFAULT(fd1, int);

/* Legacy. */

BBDECLARE_BVECTOR(bpub, int, extern);
BBDECLARE_FVECTOR(fpub, int, extern);

BBDEFINE_BVECTOR(bpub, int, bbmacro_alloc, free, bbmacro_increase);
BBDEFINE_FVECTOR(fpub, int, bbmacro_alloc, free, bbmacro_increase);

BBSTATIC_BVECTOR(bpriv, int);
BBSTATIC_FVECTOR(fpriv, int);
