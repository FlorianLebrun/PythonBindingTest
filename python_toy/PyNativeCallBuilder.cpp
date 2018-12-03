#include "PyNativeCallBuilder.h"
#include <jit/jit.h>
#include <malloc.h>

static jit_context_t context = 0;

struct IPyTypeBoxing {
  virtual jit_value_t generateUnbox(jit_function_t fn, jit_value_t value) = 0;
  virtual jit_value_t generateBox(jit_function_t fn, jit_value_t value) = 0;
  virtual void generateClean(jit_function_t fn, jit_value_t value) {}
};

struct PyObjectBoxing : IPyTypeBoxing {
  virtual jit_value_t generateUnbox(jit_function_t fn, jit_value_t value) {
    return value;
  }
  virtual jit_value_t generateBox(jit_function_t fn, jit_value_t value) {
    return value;
  }
};

struct PyIntBoxing : IPyTypeBoxing {
  jit_type_t sig_Unbox;
  jit_type_t sig_Box;
  jit_type_t type;
  PyIntBoxing() {
    this->type = jit_type_long;
    {
      jit_type_t params[1] = { jit_type_void_ptr };
      this->sig_Unbox = jit_type_create_signature(jit_abi_cdecl, this->type, params, 1, 1);
    }
    {
      jit_type_t params[1] = { this->type };
      this->sig_Box = jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, 1, 1);
    }
  }
  virtual jit_value_t generateUnbox(jit_function_t fn, jit_value_t value) {
    return jit_insn_call_native(fn, "PyLong_AsLong", PyLong_AsLong,
      this->sig_Unbox, &value, 1, JIT_CALL_NOTHROW);
  }
  virtual jit_value_t generateBox(jit_function_t fn, jit_value_t value) {
    return jit_insn_call_native(fn, "PyLong_FromLong", PyLong_FromLong,
      this->sig_Box, &value, 1, JIT_CALL_NOTHROW);
  }
};

struct PyUIntBoxing : IPyTypeBoxing {
  jit_type_t sig_Unbox;
  jit_type_t sig_Box;
  jit_type_t type;
  PyUIntBoxing() {
    this->type = jit_type_ulong;
    {
      jit_type_t params[1] = { jit_type_void_ptr };
      this->sig_Unbox = jit_type_create_signature(jit_abi_cdecl, this->type, params, 1, 1);
    }
    {
      jit_type_t params[1] = { this->type };
      this->sig_Box = jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, 1, 1);
    }
  }
  virtual jit_value_t generateUnbox(jit_function_t fn, jit_value_t value) {
    return jit_insn_call_native(fn, "PyLong_AsLong", PyLong_AsUnsignedLong,
      this->sig_Unbox, &value, 1, JIT_CALL_NOTHROW);
  }
  virtual jit_value_t generateBox(jit_function_t fn, jit_value_t value) {
    return jit_insn_call_native(fn, "PyLong_FromLong", PyLong_FromUnsignedLong,
      this->sig_Box, &value, 1, JIT_CALL_NOTHROW);
  }
};

struct PyStringBoxing : IPyTypeBoxing {
  jit_type_t sig_Unbox;
  jit_type_t sig_Box;
  jit_type_t type;
  PyStringBoxing() {
    this->type = jit_type_void_ptr;
    {
      jit_type_t params[1] = { jit_type_void_ptr };
      this->sig_Unbox = jit_type_create_signature(jit_abi_cdecl, this->type, params, 1, 1);
    }
    {
      jit_type_t params[1] = { this->type };
      this->sig_Box = jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, 1, 1);
    }
  }
  static const char* UnboxStringUTF8(PyObject* value) {
    return PyUnicode_AsUTF8AndSize(value, NULL);
  }
  static PyObject* BoxStringUTF8(const char* value) {
    return PyUnicode_FromString(value);
  }
  virtual jit_value_t generateUnbox(jit_function_t fn, jit_value_t value) {
    return jit_insn_call_native(fn, "UnboxStringUTF8", PyStringBoxing::UnboxStringUTF8,
      this->sig_Unbox, &value, 1, JIT_CALL_NOTHROW);
  }
  virtual jit_value_t generateBox(jit_function_t fn, jit_value_t value) {
    return jit_insn_call_native(fn, "PyLong_FromLong", PyStringBoxing::BoxStringUTF8,
      this->sig_Box, &value, 1, JIT_CALL_NOTHROW);
  }
};

struct PyNativeCallBuilder {
  jit_type_t sig_PyFastCall;
  jit_type_t sig_PyErr_NumArguments;
  jit_type_t sig_PyErr_Occurred;
  IPyTypeBoxing* int_boxing;
  IPyTypeBoxing* uint_boxing;
  IPyTypeBoxing* string_boxing;
  IPyTypeBoxing* object_boxing;

  PyNativeCallBuilder() {
    context = jit_context_create();
    this->lock();

    this->int_boxing = new PyIntBoxing();
    this->uint_boxing = new PyUIntBoxing();
    this->string_boxing = new PyStringBoxing();
    this->object_boxing = new PyObjectBoxing();

    // Build standard signatures
    // ---- py_fastcall
    {
      jit_type_t params[3] = { jit_type_void_ptr , jit_type_void_ptr , jit_type_nint };
      this->sig_PyFastCall = jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, 3, 1);
    }
    // ---- PyErr_NumArguments
    {
      jit_type_t params[2] = { jit_type_nint , jit_type_nint };
      this->sig_PyErr_NumArguments = jit_type_create_signature(jit_abi_cdecl, jit_type_int, params, 2, 1);
    }
    // ---- PyErr_Occurred
    {
      this->sig_PyErr_Occurred = jit_type_create_signature(jit_abi_cdecl, jit_type_int, NULL, 0, 1);
    }

    this->unlock();
  }
  ~PyNativeCallBuilder() {
    jit_context_destroy(context);
  }
  void lock() {
    jit_context_build_start(context);
  }
  void unlock() {
    jit_context_build_end(context);
  }
  IPyTypeBoxing* getBoxing(int type) {
    switch (type) {
    case T_STRING:
      return this->string_boxing;

    case T_BYTE:
    case T_SHORT:
    case T_INT:
    case T_LONG:
    case T_CHAR:
      return this->int_boxing;

    case T_UBYTE:
    case T_USHORT:
    case T_UINT:
    case T_ULONG:
      return this->uint_boxing;

    case T_OBJECT:
      return this->object_boxing;

    case T_FLOAT:
    case T_DOUBLE:
    default:
      return 0;
    }
  }
  jit_type_t getMethodSignature(PyMethodSignature* desc) {
    jit_type_t* params = (jit_type_t*)alloca(sizeof(jit_type_t)*desc->num_args);
    for (int i = 0; i < desc->num_args; i++) {
      params[i] = jit_type_void_ptr;
    }
    return jit_type_create_signature(jit_abi_cdecl, jit_type_void_ptr, params, desc->num_args, 1);
  }
  PyCFunction getCFunction(PyMethodSignature* desc, void* called) {
    this->lock();

    /* Create the function object */
    jit_function_t F = jit_function_create(context, this->sig_PyFastCall);
    int n = desc->num_args;
    /*
    static PyObject* interop_method(PyObject * self, PyObject *const *args, Py_ssize_t nargs) {

      if (nargs != n) return PyErr_NumArguments(nargs, n);

      any_t called_args[n];
      called_args[0] = PyJIT_Unbox{typename at 0}(args[0]);
      ...
      called_args[n-1] = PyJIT_Unbox{typename at n-1}(args[n-1]);

      if (PyErr_Occurred()) return NULL;

      return called(...called_args);
    }
    */

    /* Arguments values */
    jit_value_t v_self = jit_value_get_param(F, 0);
    jit_value_t v_args = jit_value_get_param(F, 1);
    jit_value_t v_nargs = jit_value_get_param(F, 2);

    /* Constants values */
    jit_value_t c_0 = jit_value_create_nint_constant(F, jit_type_int, 0);
    jit_value_t c_n = jit_value_create_nint_constant(F, jit_type_int, n);

    //> if (nargs != n) return PyErr_NumArguments(nargs, n);
    {
      //> if(nargs != n) goto check_narg;
      jit_value_t cmp_nargs_0 = jit_insn_eq(F, v_nargs, c_n);
      jit_label_t lbl_check_narg = jit_label_undefined;
      jit_insn_branch_if(F, cmp_nargs_0, &lbl_check_narg);

      //> call PyErr_NumArguments(nargs, n)
      jit_value_t vv_args[2] = { v_nargs, c_n };
      jit_insn_call_native(F, "PyErr_NumArguments", PyErr_NumArguments,
        this->sig_PyErr_NumArguments, vv_args, 2, JIT_CALL_NOTHROW | JIT_CALL_TAIL);

      //> check_narg:
      jit_insn_label(F, &lbl_check_narg);
    }

    //> called_args[%i] = PyJIT_Unbox{ typename at %i }(args[%i]);
    jit_value_t* vv_called_args = (jit_value_t*)alloca(sizeof(jit_value_t)*n);
    for (int i = 0; i < n; i++) {

      //> item = args[%i];
      jit_value_t c_i = jit_value_create_nint_constant(F, jit_type_int, i);
      jit_value_t v_item = jit_insn_load_elem(F, v_args, c_i, jit_type_void_ptr);

      //> called_args[%i] = call PyJIT_Unbox(item)
      IPyTypeBoxing* boxing = this->getBoxing(desc->args[i].kind);
      vv_called_args[i] = boxing->generateUnbox(F, v_item);
    }

    //> if (PyErr_Occurred()) return NULL;
    {
      //> has_err = PyErr_Occurred()
      jit_value_t v_has_err = jit_insn_call_native(F, "PyErr_Occurred", PyErr_Occurred,
        this->sig_PyErr_Occurred, NULL, 0, JIT_CALL_NOTHROW);

      //> if(has_err) goto check_has_err;
      jit_label_t lbl_check_has_err = jit_label_undefined;
      jit_insn_branch_if_not(F, v_has_err, &lbl_check_has_err);

      //> return NULL;
      jit_insn_return(F, c_0);

      //> check_has_err:
      jit_insn_label(F, &lbl_check_has_err);
    }


    //> return called(...called_args);
    jit_type_t sig_called = this->getMethodSignature(desc);
    jit_value_t v_result = jit_insn_call_native(F, "called", called,
      sig_called, vv_called_args, n, 0);

    //> called_args[%i] = PyJIT_Clean{ typename at %i }(args[%i]);
    for (int i = 0; i < n; i++) {
      IPyTypeBoxing* boxing = this->getBoxing(desc->args[i].kind);
      boxing->generateClean(F, vv_called_args[i]);
    }

    //> called_args[%i] = call PyJIT_Box(result)
    {
      IPyTypeBoxing* boxing = this->getBoxing(desc->result);
      v_result = boxing->generateBox(F, v_result);
      jit_insn_return(F, v_result);
    }

    /* Compile the function */
    jit_function_compile(F);
    this->unlock();
    return (PyCFunction)jit_function_to_closure(F);
  }
};

PyObject* PyErr_NumArguments(Py_ssize_t given, Py_ssize_t expected) {
  PyErr_Format(PyExc_TypeError, "function takes %d argument(s) (%d given)", expected, given);
  return NULL;
}

int PyJIT_CheckFastArguments(PyObject *const *args, Py_ssize_t nargs, Py_ssize_t n) {
  if (nargs != n) {
    PyErr_NumArguments(nargs, n);
    return 1;
  }
  return 0;
}

int PyJIT_CheckTupleArguments(PyTupleObject * args, Py_ssize_t n) {
  if (!(((PyObject*)args)->ob_type->tp_flags & Py_TPFLAGS_TUPLE_SUBCLASS)) {
    PyErr_Format(PyExc_TypeError, "function call arguments (tuple expected)");
    return 1;
  }
  return PyJIT_CheckFastArguments(args->ob_item, ((PyVarObject*)args)->ob_size, n);
}

static PyNativeCallBuilder* nativeCallBuilder = new PyNativeCallBuilder();

_PyCFunctionFast myMethod_ptr = 0;
static PyObject* interop_method2(PyObject * self, PyObject *const *args, Py_ssize_t nargs) {
  PyObject* r = myMethod_ptr(self, args, nargs);
  return r;
}

PyObject* PyModule_CreateWithNative(PyModuleDef* def) {
  if (def->m_methods) {
    for (PyMethodDef* method = def->m_methods; method->ml_name; method++) {
      if (method->ml_flags & METH_NATIVE) {
        PyMethodSignature* desc = (PyMethodSignature*)method->ml_doc;
        myMethod_ptr = (_PyCFunctionFast)nativeCallBuilder->getCFunction(desc, method->ml_meth);
        method->ml_flags ^= METH_NATIVE | METH_FASTCALL;
        method->ml_doc = desc->doc;
        method->ml_meth = (PyCFunction)interop_method2;// (PyCFunction)nativeCallBuilder->getCFunction(desc, method->ml_meth);
        printf("native call '%s'\n", method->ml_name);
      }
    }
  }
  return PyModule_Create(def);
}
