#ifndef _GF_ASM_H_JK34L5JKL2544RFJWK
#define _GF_ASM_H_JK34L5JKL2544RFJWK

#include <time.h>
#include <limits.h>

#define GF_LINE_MAX NAME_MAX

struct gf_line {
	struct timespec timespec;
	char text[GF_LINE_MAX];
};

#endif // _GF_ASM_H_JK34L5JKL2544RFJWK

