# Examples

## Example API functions

### A simple getter function

This function gets the length of a tuple.
Very simple getters that return a C scalar do not need a `PyContext` parameter.

```C
uintptr_t PyApi_Tuple_GetLength(PyTupleRef t);
```

And here is an implementation for CPython (most versions up to 3.11)
```C
typedef struct _py_tuple_ref {
    PyTupleObject *pointer;
} PyTupleRef;

uintptr_t 
PyApi_Tuple_GetLength(PyTupleRef t)
{
    return (uintptr_t)Py_SIZE(t.pointer);
}

```

### A computed getter function

This function gets the name of a class object
```C
PyStrRef PyApi_Class_GetName(PyContext ctx, PyClassRef cls);
```

And here is an implementation for CPython (most versions up to 3.11)
```C
typedef struct _py_class_ref {
    PyTypeObject *pointer;
} PyClassRef;

PyStrRef
PyApi_Class_GetName(PyContext ctx, PyClassRef cls)
{
    PyObject *name = PyUnicode_FromString(cls.pointer->tp_name);
    return PyApi_Interop_FromUnicodeObject_C(name);
}
```

### A function with failure, but no error

This function unboxes an integer, with possible overflow.
```C

intptr_t PyApi_Number_UnboxAsInt(PyIntRef i, int* overflow)
{
    PyObject *obj = i.pointer;
    assert (PyLong_check(obj));

    if (PyLong_WillOverflowSsize_t(obj)) {
        int sign = _PyLong_Sign(obj);
        *overflow = sign;
        return sign > 0 ? INTPTR_MAX : INTPTR_MIN;
    }
    *overflow = 0;
    return PyLong_AsSsize_t(obj);
}
```

### A function with both failure and error

This function gets a value from a dictionary

```C

PyRef PyApi_Dict_GetItem(PyContext ctx, PyDictRef d, PyRef key, PyExceptionRef *error)
{
    PyObject *dp = d.pointer;
    PyObject *kp = key.pointer;
    PyObject *res = _PyDict_GetItemWithError(PyObject *dp, PyObject *kp);
    if (res != NULL) {
        assert(!Py_ErrOccurred());
        return PyApi_Interop_FromObject_C(res);
    }
    if (Py_ErrOccurred()) {
        PyObject *exception = get_normalized_exception();
        *error = PyApi_Interop_FromException(exception);
        return PyRef_INVALID;
    }
    /* Special case -- failure. No result, but no exception */
    *error = PyRef_NO_EXCEPTION;
    return PyRef_INVALID;
}
```

## Constructing API functions from ABI functions

### Handling references

For the ABI function
```
PyExceptionRef PyApi_Tuple_SetItem_BnC(PyContext ctx, PyTupleRef t, uintptr_t index, PyRef item);
```

We can construct the API function that borrows the reference simply:
```
inline PyExceptionRef
PyApi_Tuple_SetItem(PyContext ctx, PyTupleRef t, uintptr_t index, PyRef item)
{
    PyRef arg2 = PyRef_Dup(ctx, item);
    return PyApi_Tuple_SetItem_BnC(ctx, t, index, arg2)
}
```

### Handling edge cases

Some ABI functions are designed primarily for efficiency, so we
want to wrap them in a friendlier API that handles edge cases.

For example,
```
PyTupleRef PyApi_Tuple_FromNonEmptyArray_nC(PyContext ctx, uintptr_t len, PyRef *values, PyExceptionRef *error);
```
can be wrapped in a macro to give the nicer API:
```
PyTupleRef PyApi_Tuple_FromFixedArray(ctx, array, error)
```

```
#define PyApi_Tuple_FromFixedArray(ctx, array, error) \
    ((sizeof(array) == 0) ? \
        PyApi_Tuple_Empty(ctx)
    : \
        PyApi_Tuple_FromNonEmptyArray(ctx, sizeof(array)/sizeof(PyRef), &array, error)
    )
```
Allowing it be used like this:
```
PyRef args[4] = {
    PyNone,
    arg1,
    arg2,
    PyNone
};
PyTupleRef new_tuple;
int err = PyApi_Tuple_FromFixedArray(ctx, args, &new_tuple);
```


### Downcast macros

Here is a possible implementation of a downcast macro:
```
#define PyApi_List_CheckAndDowncast(OBJ, LIST) \
    (PyRef_IsList(OBJ) ? (LIST = PyApi_List_UnsafeCast(OBJ), 1) : 0)
```

