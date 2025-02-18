
#include <jit/jit.h>
#include "libjit/jit/jit-internal.h"
#include <stdio.h>


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

  template <typename Tvalue>
  void check_integer_sum(jit_type_t valueType)
  {
    int numParameter = 6;

    /* Lock the context while we build and compile the function */
    jit_context_build_start(context);

    /* Build the function signature */
    jit_type_t signature;
    jit_type_t* params = (jit_type_t*)alloca(sizeof(jit_type_t)*numParameter);
    for (int i = 0; i < numParameter; i++) params[i] = valueType;
    signature = jit_type_create_signature(jit_abi_stdcall, valueType, params, numParameter, 1);

    /* Create the function object */
    jit_function_t function;
    function = jit_function_create(context, signature);
    jit_type_free(signature);

    /* Construct the function body */
    jit_value_t x = jit_value_get_param(function, 0);
    for (int i = 1; i < numParameter; i++)
      x = jit_insn_add(function, x, jit_value_get_param(function, i));
    jit_insn_return(function, x);

    /* Compile the function */
    //jit_dump_function(stdout, function, "sum");
    jit_function_compile(function);

    /* Unlock the context */
    jit_context_build_end(context);

    /* Execute the function */
    typedef Tvalue(__stdcall *sum_f)(Tvalue, Tvalue, Tvalue, Tvalue, Tvalue, Tvalue);
    Tvalue result = ((sum_f)jit_function_to_closure(function))(3, 5, 2, 7, 8, 9);

    /* Print the result */
    const char* message;
    switch (valueType->kind) {
    case JIT_TYPE_FLOAT32:
      message = "sum(3, 5, 2, 7, 8, 9) = %f (expect %d)\n"; break;
    case JIT_TYPE_FLOAT64:
      message = "sum(3, 5, 2, 7, 8, 9) = %lf (expect %d)\n"; break;
    case JIT_TYPE_NFLOAT:
      message = "sum(3, 5, 2, 7, 8, 9) = %Lf (expect %d)\n"; break;
    default:
      message = "sum(3, 5, 2, 7, 8, 9) = %d (expect %d)\n";
    }
    printf(message, result, 3 + 5 + 2 + 7 + 8 + 9);
  }
  void t1()
  {
    this->check_integer_sum<jit_float32>(jit_type_float32);
    this->check_integer_sum<jit_float64>(jit_type_float64);
    this->check_integer_sum<jit_nfloat>(jit_type_nfloat);

    this->check_integer_sum<jit_nint>(jit_type_nint);
    this->check_integer_sum<jit_long>(jit_type_long);
    this->check_integer_sum<jit_int>(jit_type_int);
    this->check_integer_sum<jit_short>(jit_type_short);
    this->check_integer_sum<jit_sbyte>(jit_type_sbyte);

    this->check_integer_sum<jit_nuint>(jit_type_nuint);
    this->check_integer_sum<jit_ulong>(jit_type_ulong);
    this->check_integer_sum<jit_uint>(jit_type_uint);
    this->check_integer_sum<jit_ushort>(jit_type_ushort);
    this->check_integer_sum<jit_ubyte>(jit_type_ubyte);
  }
};

int main(int argc, char **argv)
{
  TestsContext tests;
  tests.t1();
  return 0;
}
