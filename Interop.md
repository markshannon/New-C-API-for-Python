# Interoperability API

The interopability API consists of functions for converting
`PyObject *` to `PyRef`, and vice versa.
These functions are for internal use, so do not take a `PyContext`.

## Converting `PyObject *` to `PyRef`

In general, converting a `PyObject *` to a `PyRef` is unsafe as it loses
information about exceptions. Therefore conversion functions need to
return a `kind` as well as a `PyRef`.

```C
PyRef PyApi_Interop_FromObjectUnsafe_C(PyObject *obj);
```

The safe variant, which bundles the current exception and does consistency checks:
```C
int PyApi_Interop_FromObject_C(PyObject *obj, PyRef *result);
```

## Converting `PyRef` to `PyObject *`

This function consumes the argument.

```C
PyObject *PyApi_Interop_ToObject_C(PyRef ref);
```

The `PyApi_Interop_ToObject_C` never returns `NULL`, nor sets an exception.

## Implementation of the error handling forms

Athough technically an implementation detail, it helps understanding
and correct use if the implemenation of the error handling forms are shown.

```C

PyRef PyApi_Interop_FromObjectUnsafe_C(PyObject *obj)
{
    assert(obj != NULL);
    assert(!PyErr_Occurred());
    return (PyRef) { obj };
}

PyRef PyApi_Interop_FromObject_C(PyObject *obj, PyExceptionRef *exc)
{
    if (PyErr_Occurred()) {
        PyObject *exception = get_normalized_exception();
        if (object != NULL) {
            // Both object and exception
            PyObject *new_exception = _PyErr_CreateException(
                PyExc_SystemError,
                "value is not-NULL, but an exception is set"
            );
            PyException_SetCause(new_exception, exception);
            Py_DECREF(exception);
            Py_DECREF(obj);
            exception = new_exception;
        }
        *exc = PyApi_Interop_FromException(exception);
        return PyRef_INVALID;
    }
    else {
        if (obj == NULL) {
            // Neither result nor exception 
            PyObject *exception = _PyErr_CreateException(
                PyExc_SystemError,
                "value is NULL without setting an exception"
            );
            *exc = PyApi_Interop_FromException(exception);
            return PyRef_INVALID;
        }
    }
    return PyApi_Interop_FromObjectUnsafe(obj);
}
```

```C
PyObject *PyApi_Interop_ToObject_C(PyRef ref)
{
    return ref.value;
}
```





