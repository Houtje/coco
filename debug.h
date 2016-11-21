#ifndef _DEBUG_H
#define _DEBUG_H
#include <stdio.h>
#include <stdarg.h>

#if defined(__cplusplus)
extern "C" {
#endif

void pmesg(int level, const char *format, ...);

#if defined(__cplusplus)
}
#endif

#endif
