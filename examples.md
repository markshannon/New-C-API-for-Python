# Examples

## Example API functions

### A simple getter function

This function gets the length of a tuple

```C
uintptr_t PyApi_Tuple_GetLength(PyTupleRef t);
```

And here is an implementation for CPython (most versions up to 3.11)
```C
uintptr_t 
PyApi_Tuple_GetLength(PyTupleRef t)
{
    return 
}

```
### A computed getter function

This function gets the name of a class object
```C
PyResult PyApi_Class_GetName(PyClassRef cls);
```

And here is an implementation for CPython (most versions up to 3.11)
```C
typedef struct _py_class_ref {
    PyTypeObject *pointer;
} PyClassRef;

PyResult
PyApi_Class_GetName(PyClassRef cls)
{
    PyObject *name = PyUnicode_FromString(cls.pointer->tp_name);
    return PyApi_Interop_FromObject_C(name);
}
```

### A function with failure, but no error

This function unboxes an integer, with possible overflow.
```C
typedef struct _py_int_result {
    int kind;
    intptr_t value;
} PyIntResult;

PyIntResult PyApi_Number_UnboxAsInt(PyIntRef i)
{
    PyObject *obj = i.pointer;
    assert (PyLong_check(obj));

    if (PyLong_WillOverflowSsize_t(obj)) {
        return (PyIntResult) { OVERFLOW, _PyLong_Sign(obj) };
    }
    else {
        uintptr_t val = PyLong_AsSsize_t(obj);
        return (PyIntResult) { SUCCESS, val };
    }
}
```

### A function with both failure and error

This function gets a value from a dictionary

```C
PyResultWithFailure PyApi_Dict_GetItem(PyDictRef d, PyRef key)
{
    PyObject *dp = d.pointer;
    PyObject *kp = key.pointer;
    PyObject *res = _PyDict_GetItemWithError(PyObject *dp, PyObject *kp);
    if (res != NULL) {
        assert(!Py_ErrOccurred());
        return (PyResultWithFailure) { SUCCESS, res};
    }
    if (Py_ErrOccurred()) {
        PyObject *exception = get_normalized_exception();
        return (PyResultWithFailure) { ERROR, exception};
    }
    return (PyResultWithFailure) { FAILURE, PyIgnorableRef() };
}
```

`PyIgnorableRef()` should return a valid `PyRef` that can be safely ignored,
but will not invalid the state of the VM if it is used a normal reference.

## Constructing API functions from ABI functions

### Handling references

For the ABI function
```
int PyApi_Tuple_SetItem_BnC(PyTupleRef t, uintptr_t index, PyRef item);
```

We can construct the API function that borrows the reference easily:
```
inline int
PyApi_Tuple_SetItem(PyTupleRef t, uintptr_t index, PyRef item)
{
    PyRef arg2 = PyRef_Dup(item);
    return PyApi_Tuple_SetItem_BnC(t, index, arg2)
}
```

### Handling edge cases

Some ABI functions are designed primarily for efficiency, so we
want to wrap them in a friendlier API that handles edge cases.

For example,
```
PyResult PyApi_Tuple_FromNonEmptyArray_nC(uintptr_t len, PyRef *values);
```
can be wrapped in a macro to give the nicer API:
```
PyResult PyApi_Tuple_FromFixedArray(array)
```

```
#define PyApi_Tuple_FromFixedArray(array) \
    ((sizeof(array) == 0) ? \
        (PyResult) { SUCCESS, PyApi_Tuple_Empty() } \
    : \
        PyApi_Tuple_FromNonEmptyArray(sizeof(array)/sizeof(PyRef), &array)
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
PyTupleResult new_tuple = PyApi_Tuple_FromFixedArray(args);
```
