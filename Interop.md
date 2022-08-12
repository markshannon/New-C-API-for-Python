# Interoperability API

The interopability API consists of functions for converting
`PyObject *` to `PyRef` and `PyResult`, and vice versa

## Converting `PyObject *` to `PyRef` and `PyResult`

In general converting a `PyObject *` to a `PyRef` is unsafe as it loses
information about exceptions.

```C
PyRef PyApi_Interop_FromObjectUnsafe_C(PyObject *obj);
```

The safe variant, which bundles the current exception and does consistency checks:
```C
PyResult PyApi_Interop_FromObject_C(PyObject *obj);
```

## Converting `PyRef` and `PyResult` to `PyObject *`

Both forms consume the argument.

```C
PyObject *PyApi_Interop_ToObject_C(PyRef ref);
PyObject *PyApi_Interop_ToObject_M(PyResult ref);
```

The `PyApi_Interop_ToObject_C` never returns `NULL`, nor sets an exception.
The `PyApi_Interop_ToObject_M` may return `NULL` and set an exception.

## Implementation of the error handling forms

Athough technically an implementation detail, it helps understanding
and correct use if the implemenation of the error handling forms are shown.

```C
PyResult PyApi_Interop_FromObject_C(PyObject *obj)
{
    int kind;
    PyObject *exception = NULL;
    if (PyErr_Occurred()) {
        exception = get_normalized_exception();
        if (object != NULL) {
            // Both object and exception
            PyObject *new_exception = _PyErr_CreateException(
                PyExc_SystemError,
                "value is not-NULL, but an exception is set"
            );
            PyException_SetCause(new_exception, exception);
            Py_DECREF(exception);
            Py_DECREF(obj);
            obj = new_exception;
            res.kind = ERROR;
        }
        else {
            obj = exception;
        }
        kind = ERROR;
    }
    else {
        if (obj == NULL) {
            // Neither result nor exception 
            exception = _PyErr_CreateException(
                PyExc_SystemError,
                "value is NULL without setting an exception"
            );
            obj = exception;
        }
        else {
            kind = SUCCESS;
        }
    }
    PyRef value = PyApi_Interop_FromObjectUnsafe(obj);
    return (PyResult){kind, value};
}
```

```C
PyObject *PyApi_Interop_ToObject_M(PyResult ref)
{
    PyObject *val = PyApi_Interop_ToObject_C(ref.value);
    if (ref.kind < 0) {
        PyErr_SetObject(val, NULL);
        Py_DECREF(val);
        return NULL;
    }
    else {
        return val;
    }
}
```





