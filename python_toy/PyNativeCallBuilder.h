#ifndef PyNativeCallBuilder_h_
#define PyNativeCallBuilder_h_

#include <Python.h>
#include <structmember.h>

struct PyMethodArg {
  const char* name;
  int kind;
};

struct PyMethodSignature {
  const char* doc;
  int result;
  int num_args;
  PyMethodArg args[];
};

#define METH_NATIVE 0x0100

PyObject* PyModule_CreateWithNative(PyModuleDef* def);

PyObject* PyErr_NumArguments(Py_ssize_t given, Py_ssize_t expected);
int PyJIT_CheckFastArguments(PyObject *const *args, Py_ssize_t nargs, Py_ssize_t n);
int PyJIT_CheckTupleArguments(PyTupleObject * args, Py_ssize_t n);
/*
static PyObject* interop_myMethod(PyObject * self, PyObject *const *args, Py_ssize_t nargs) {
  if (nargs != 1) return PyErr_NumArguments(nargs, 1);
  const char* x = PyJIT_UnboxStringUTF8(args[0]);
  if (PyErr_Occurred()) return NULL;
  return myMethod(x);
}
*/
#endif
