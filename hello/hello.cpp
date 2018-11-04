#include <Python.h>

#pragma comment(lib, "python37.lib")

static PyObject * hello_wrapper(PyObject * self, PyObject * args)
{
  char * input;
  PyObject * ret;

  // parse arguments
  if (!PyArg_ParseTuple(args, "s", &input)) {
    return NULL;
  }

  // build the resulting string into a Python object.
  ret = PyUnicode_FromString("hello world!");

  return ret;
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

static PyObject *
error_out(PyObject *module) {
  ModuleState* state = (ModuleState*)PyModule_GetState(module);
  PyErr_SetString(state->myError, "something bad happened");
  return NULL;
}

static PyMethodDef moduleMethods[] = {
  { "error_out", (PyCFunction)error_out, METH_NOARGS, NULL },
  { "hello", hello_wrapper, METH_VARARGS, "Say hello" },
  { NULL, NULL, 0, NULL }
};

static struct PyModuleDef moduleDef = {
  PyModuleDef_HEAD_INIT,
  "hello",
  NULL,
  sizeof(ModuleState),
  moduleMethods,
  NULL,
  ModuleState::_traverse,
  ModuleState::_clear,
  NULL
};

PyMODINIT_FUNC PyInit_hello(void)
{
  PyObject *module = PyModule_Create(&moduleDef);
  if (module == NULL) return 0;

  ModuleState* state = (ModuleState*)PyModule_GetState(module);

  state->myError = PyErr_NewException("myextension.Error", NULL, NULL);
  if (state->myError == NULL) {
    Py_DECREF(module);
    return 0;
  }

  return module;
}


