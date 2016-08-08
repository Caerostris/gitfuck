#ifndef _GF_ASM_H_JK34L5JKL2544RFJWK
#define _GF_ASM_H_JK34L5JKL2544RFJWK

#include <time.h>
#include <limits.h>

#define GF_LINE_MAX NAME_MAX

#ifdef __APPLE__
#ifndef st_mtime
#define st_mtime st_mtimespec.tv_sec
#endif
#endif

struct gf_line {
	time_t tv_sec;
	char text[GF_LINE_MAX];
};

#endif // _GF_ASM_H_JK34L5JKL2544RFJWK

