#include <jit/jit.h>
#include <Python.h>
#include <structmember.h>
#include <malloc.h>
#include <stdio.h>

#pragma comment(lib, "python37.lib")

jit_nint PyJIT_GetBool(PyObject* value) {
  return PyLong_AsLong(value);
}

jit_sbyte PyJIT_GetByte(PyObject* value) {
  return PyLong_AsLong(value);
}
jit_short PyJIT_GetShort(PyObject* value) {
  return PyLong_AsLong(value);
}
jit_int PyJIT_GetInt(PyObject* value) {
  return PyLong_AsLong(value);
}
jit_long PyJIT_GetLong(PyObject* value) {
  return PyLong_AsLong(value);
}
jit_nint PyJIT_GetNInt(PyObject* value) {
  return PyLong_AsLong(value);
}

jit_ubyte PyJIT_GetUByte(PyObject* value) {
  return PyLong_AsUnsignedLong(value);
}
jit_ushort PyJIT_GetUShort(PyObject* value) {
  return PyLong_AsUnsignedLong(value);
}
jit_uint PyJIT_GetUInt(PyObject* value) {
  return PyLong_AsUnsignedLong(value);
}
jit_ulong PyJIT_GetULong(PyObject* value) {
  return PyLong_AsUnsignedLong(value);
}
jit_nuint PyJIT_GetNUInt(PyObject* value) {
  return PyLong_AsUnsignedLong(value);
}

jit_float32 PyJIT_GetFloat32(PyObject* value) {
  return PyFloat_AsDouble(value);
}
jit_float64 PyJIT_GetFloat64(PyObject* value) {
  return PyFloat_AsDouble(value);
}
jit_nfloat PyJIT_GetNFloat(PyObject* value) {
  return PyFloat_AsDouble(value);
}

const char* PyJIT_GetStringUTF8(PyObject* value) {
  return PyUnicode_AsUTF8AndSize(value, NULL);
}

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

struct PyMethodArg {
  const char* name;
  int kind;

};

struct PyMethodSignature {
  const char* doc;
  int num_args;
  PyMethodArg args[];
};

struct PyNativeCallBuilder {
  jit_context_t context;
  jit_type_t sig_PyFastCall;
  jit_type_t sig_PyErr_NumArguments;
  jit_type_t sig_PyErr_Occurred;

  PyNativeCallBuilder() {
    context = jit_context_create();
    this->lock();

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
    jit_context_build_start(this->context);
  }
  void unlock() {
    jit_context_build_end(this->context);
  }
  jit_type_t getUnpackSignature(jit_type_t type) {
    jit_type_t params[1] = { jit_type_void_ptr };
    return jit_type_create_signature(jit_abi_cdecl, type, params, 1, 1);
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
      called_args[0] = PyJIT_Unpack{typename at 0}(args[0]);
      ...
      called_args[n-1] = PyJIT_Unpack{typename at n-1}(args[n-1]);

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

    //> called_args[%i] = PyJIT_Unpack{ typename at %i }(args[%i]);
    jit_value_t* vv_called_args = (jit_value_t*)alloca(sizeof(jit_value_t)*n);
    for (int i = 0; i < n; i++) {

      //> item = args[%i];
      jit_value_t c_i = jit_value_create_nint_constant(F, jit_type_int, i);
      jit_value_t v_item = jit_insn_load_elem(F, v_args, c_i, jit_type_void_ptr);

      //> called_args[%i] = call PyJIT_Unpack(item)
      jit_value_t vv_args[1] = { v_item };
      vv_called_args[i] = jit_insn_call_native(F, "PyJIT_Unpack", PyJIT_GetStringUTF8, 
        this->getUnpackSignature(jit_type_void_ptr), vv_args, 1, JIT_CALL_NOTHROW);
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
    jit_value_t v_has_err = jit_insn_call_native(F, "called", called, 
      sig_called, vv_called_args, n, JIT_CALL_TAIL);

    /* Compile the function */
    jit_function_compile(F);
    this->unlock();
    return (PyCFunction)jit_function_to_closure(F);
  }
};

static PyNativeCallBuilder* nativeCallBuilder = new PyNativeCallBuilder();

#define METH_NATIVE 0x0100

/*
_PyCFunctionFast myMethod_ptr = 0;
static PyObject* interop_method(PyObject * self, PyObject *const *args, Py_ssize_t nargs) {
  PyObject* r = myMethod_ptr(self, args, nargs);
  return r;
}*/

PyObject* PyModule_CreateWithNative(PyModuleDef* def) {
  if (def->m_methods) {
    for (PyMethodDef* method = def->m_methods; method->ml_name; method++) {
      if (method->ml_flags & METH_NATIVE) {
        PyMethodSignature* desc = (PyMethodSignature*)method->ml_doc;
        method->ml_flags ^= METH_NATIVE | METH_FASTCALL;
        method->ml_doc = desc->doc;
        method->ml_meth = (PyCFunction)nativeCallBuilder->getCFunction(desc, method->ml_meth);
        printf("native call '%s'\n", method->ml_name);
      }
    }
  }
  return PyModule_Create(def);
}

struct ModuleState {
  PyObject *myError;

  static int _traverse(PyObject *module, visitproc visit, void *arg) {
    ModuleState* state = (ModuleState*)PyModule_GetState(module);
    Py_VISIT(state->myError);
    return 0;
  }

  static int _clear(PyObject *module) {
    ModuleState* state = (ModuleState*)PyModule_GetState(module);
    Py_CLEAR(state->myError);
    return 0;
  }
};

static PyObject* error_out(PyObject *module) {
  ModuleState* state = (ModuleState*)PyModule_GetState(module);
  PyErr_SetString(state->myError, "something bad happened");
  return NULL;
}

PyMethodSignature myMethod_sig = {
  "doc of method", 1,
  {"x", T_STRING, "doc of x"},
};

static PyObject * myMethod(const char * x) {
  PyObject * ret;

  // build the resulting string into a Python object.
  ret = PyUnicode_FromString("python_toy world!");

  return ret;
}

static PyMethodDef moduleMethods[] = {
  { "error_out", (PyCFunction)error_out, METH_NOARGS, NULL },
  { "myMethod", (PyCFunction)myMethod, METH_NATIVE, (char*)&myMethod_sig },
  { NULL, NULL, 0, NULL }
};

static struct PyModuleDef moduleDef = {
  PyModuleDef_HEAD_INIT,
  "python_toy",
  "Simple buildtin module",
  sizeof(ModuleState),
  moduleMethods,
  NULL,
  ModuleState::_traverse,
  ModuleState::_clear,
  NULL
};

PyMODINIT_FUNC PyInit_python_toy(void)
{
  PyObject *module = PyModule_CreateWithNative(&moduleDef);
  if (module == NULL) return 0;

  ModuleState* state = (ModuleState*)PyModule_GetState(module);

  state->myError = PyErr_NewException("myextension.Error", NULL, NULL);
  if (state->myError == NULL) {
    Py_DECREF(module);
    return 0;
  }

  return module;
}


