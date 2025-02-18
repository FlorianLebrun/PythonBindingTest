
#include <jit/jit.h>
#include "jit/jit-internal.h"
#include <stdio.h>

extern "C" {
  void jit_dump_function(FILE *stream, jit_function_t func, const char *name);

  void * _cdecl __builtin_apply(void(*function)(), void *arguments, size_t size) {
    printf("Crash on __builtin_apply\n");
    return 0;
  }

  void _cdecl __builtin_return(void *result) {
    printf("Crash on __builtin_return\n");
  }
}
