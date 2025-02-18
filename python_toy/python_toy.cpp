#include "PyNativeCallBuilder.h"
#include <structmember.h>

#include <stdio.h>

#pragma comment(lib, "python37.lib")


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
  "doc of method", T_STRING, 2, {
    {"x", T_STRING},
    {"y", T_INT},
  }
};

static const char* myMethod(const char * x, int y) {
  PyObject * ret;

  // build the resulting string into a Python object.
  ret = PyUnicode_FromString("python_toy world!");

  return "hello";
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


