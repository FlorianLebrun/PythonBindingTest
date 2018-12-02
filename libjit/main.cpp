
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

struct TestsContext {
  jit_context_t context;

  TestsContext() {
    /* Create a context to hold the JIT's primary state */
    context = jit_context_create();
  }
  ~TestsContext() {
    /* Clean up */
    jit_context_destroy(context);
  }
  void t1()
  {

    /* Lock the context while we build and compile the function */
    jit_context_build_start(context);

    /* Build the function signature */
    jit_type_t signature;
    jit_type_t params[6];
    params[0] = jit_type_int;
    params[1] = jit_type_int;
    params[2] = jit_type_int;
    params[3] = jit_type_int;
    params[4] = jit_type_int;
    params[5] = jit_type_int;
    signature = jit_type_create_signature(jit_abi_stdcall, jit_type_int, params, 6, 1);

    /* Create the function object */
    jit_function_t function;
    function = jit_function_create(context, signature);
    jit_type_free(signature);

    /* Construct the function body */
    jit_value_t x = jit_value_get_param(function, 0);
    jit_value_t y = jit_value_get_param(function, 1);
    jit_value_t z = jit_value_get_param(function, 2);
    jit_value_t a = jit_value_get_param(function, 3);
    jit_value_t b = jit_value_get_param(function, 4);
    jit_value_t c = jit_value_get_param(function, 5);
    jit_value_t temp1;
    temp1 = jit_insn_add(function, x, y);
    temp1 = jit_insn_add(function, temp1, z);
    temp1 = jit_insn_add(function, temp1, a);
    temp1 = jit_insn_add(function, temp1, b);
    /*temp1 = jit_insn_add(function, temp1, c);*/
    jit_insn_return(function, temp1);

    /* Compile the function */
    jit_dump_function(stdout, function, "sum");
    jit_function_compile(function);

    /* Unlock the context */
    jit_context_build_end(context);

    /* Execute the function and print the result */
    typedef int(__stdcall *sum_f)(int, int, int, int, int, int);
    printf("mul_add(3, 5, 2, 7, 8, 9) = %d\n",
      ((sum_f)function->entry_point)(3, 5, 2, 7, 8, 9)
    );
  }
};

int main(int argc, char **argv)
{
  TestsContext tests;
  tests.t1();
  return 0;
}
