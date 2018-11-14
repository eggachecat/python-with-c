#include <Python.h>
#include <stdio.h>
#include <numpy/arrayobject.h>

int sa_add(int a, int b)
{
    return a + b + 37;
}

int sa_mul(int a, int b)
{
    return a * b + 37;
}

PyObject *wrap_sa_add(PyObject *self, PyObject *args)
{
    int a, b, result;
    if (!PyArg_ParseTuple(args, "ii", &a, &b))
        return NULL;
    result = sa_add(a, b);

    return Py_BuildValue("i", result);
}

PyObject *wrap_sa_mul(PyObject *self, PyObject *args, PyObject *keywds)
{
    int a, result;
    int b = 1;
    static char *kwlist[] = {"b", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i|i", kwlist, &a, &b))
        return NULL;

    result = sa_mul(a, b);

    return Py_BuildValue("i", result);
}

static PyObject *
keywdarg_parrot(PyObject *self, PyObject *args, PyObject *keywds)
{
    int voltage;
    const char *state = "a stiff";
    const char *action = "voom";
    const char *type = "Norwegian Blue";

    static char *kwlist[] = {"voltage", "state", "action", "type", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i|sss", kwlist,
                                     &voltage, &state, &action, &type))
        return NULL;

    printf("-- This parrot wouldn't %s if you put %i Volts through it.\n",
           action, voltage);
    printf("-- Lovely plumage, the %s -- It's %s!\n", type, state);

    Py_RETURN_NONE;
}

static PyObject *sa_print_hello_world(PyObject *self, PyObject *args)
{
    printf("Hello World\n");
    Py_RETURN_NONE;
}

static PyMethodDef sa_module_methods[] = {
    {"print_hello_world",
     sa_print_hello_world,
     METH_NOARGS,
     "Print 'hello world' from a method defined in a C extension."},
    {"sa_add",
     wrap_sa_add,
     METH_VARARGS,
     "Add Two numbers with addition 37"},
    {"parrot",
     (PyCFunction)keywdarg_parrot,
     METH_VARARGS | METH_KEYWORDS,
     "Print a lovely skit to standard output."},
    {"sa_mul",
     (PyCFunction)wrap_sa_mul,
     METH_VARARGS | METH_KEYWORDS,
     "Mul Two numbers with addition 37"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef sa_module_definition = {
    PyModuleDef_HEAD_INIT,
    "sa_module",
    "A Python module that prints 'hello world' from C code.",
    -1,
    sa_module_methods};

PyMODINIT_FUNC PyInit_sa_module(void)
{
    import_array();# very important!!!
    Py_Initialize();

    return PyModule_Create(&sa_module_definition);
}
