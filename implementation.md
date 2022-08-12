# Implementing the new C API in CPython

There are approximately 44 thousand occurences of `PyObject *` in the CPython codebase.
That is a lot to change.

However, we don't need to change all the code that uses `PyObject *` to `PyRef` overnight.
In fact until we change the implementation of `PyRef` to tagged pointers, or similar, we
don't need to change anything at all.

Starting with the simplest representation of `PyRef` as
```
typedef struct {
    PyObject *ptr;
} PyRef;
```

Most uses of `PyObject *` are one of a few simple operations, such as `Py_INCREF()`, `Py_DECREF()`
and `Py_TYPE()`.

Changing `Py_TYPE()` is easy enough.
`Py_TYPE(obj)` becomes `PyAPI_Object_GetClass(obj)`. As long as `PYAPI_NO_ABI` is defined, it remains efficient.

As a stopgap, we can add `PyRef_INCREF()`, `PyRef_DECREF()`.
Ultimately they will have to go, but we can leave them in for a few years.

Most other uses of `PyObject *` involving passing it to another C API function, or casting to a more
specific class. With the possible future exception of `int` and `float`, we can continue to cast.
`(PyXXXObject *)obj` becomes `PyApi_XXX_Unsafecast(obj)`.
Converting to safe casts can be done later.

Adding two inline functions should help as well.
```
PyRef TO_REF(PyObject *);
PyObject *TO_PTR(PyRef ref);
```