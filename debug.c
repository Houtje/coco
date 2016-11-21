#include "debug.h"

extern int msglevel; /* the higher, the more messages... */

void pmesg(int level, const char* format, ...) {
  va_list args;

  if (level <= msglevel) {
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
  }
}
