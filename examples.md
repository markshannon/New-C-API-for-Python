# Examples

## Example API functions

### A simple getter function

This function gets the length of a tuple

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
int PyApi_Class_GetName(PyClassRef cls, PyStrRef *result);
```

And here is an implementation for CPython (most versions up to 3.11)
```C
typedef struct _py_class_ref {
    PyTypeObject *pointer;
} PyClassRef;

int
PyApi_Class_GetName(PyClassRef cls, PyStrRef *result)
{
    PyObject *name = PyUnicode_FromString(cls.pointer->tp_name);
    return PyApi_Interop_FromUnicodeObject_C(name, result);
}
```

### A function with failure, but no error

This function unboxes an integer, with possible overflow.
```C

int PyApi_Number_UnboxAsInt(PyIntRef i, intptr_t *value)
{
    PyObject *obj = i.pointer;
    assert (PyLong_check(obj));

    if (PyLong_WillOverflowSsize_t(obj)) {
        *value = _PyLong_Sign(obj);
        return OVERFLOW;
    }
    else {
        *value = PyLong_AsSsize_t(obj);
        return SUCCESS;
    }
}
```

### A function with both failure and error

This function gets a value from a dictionary

```C

typedef enum _py_lookup_kind {
    ERROR = -1,
    FOUND = 0,
    MISSING = 1,
} PyLookupKind;

PyLookupKind PyApi_Dict_GetItem(PyDictRef d, PyRef key, PyRef *result)
{
    PyObject *dp = d.pointer;
    PyObject *kp = key.pointer;
    PyObject *res = _PyDict_GetItemWithError(PyObject *dp, PyObject *kp);
    if (res != NULL) {
        assert(!Py_ErrOccurred());
        ref->pointer = res;
        return SUCCESS;
    }
    if (Py_ErrOccurred()) {
        PyObject *exception = get_normalized_exception();
        ref->pointer = exception;
        return ERROR;
    }
    *result = PyIgnorableRef();
    return MISSING;
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

We can construct the API function that borrows the reference simply:
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
int PyApi_Tuple_FromNonEmptyArray_nC(uintptr_t len, PyRef *values, PyRef *result);
```
can be wrapped in a macro to give the nicer API:
```
int PyApi_Tuple_FromFixedArray(array, result)
```

```
#define PyApi_Tuple_FromFixedArray(array, result) \
    ((sizeof(array) == 0) ? \
        (*result = PyApi_Tuple_Empty(), SUCCESS) \
    : \
        PyApi_Tuple_FromNonEmptyArray(sizeof(array)/sizeof(PyRef), &array, result)
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
int err = PyApi_Tuple_FromFixedArray(args, &new_tuple);
```


### Downcast macros

Here is a possible implementation of a downcast macro:
```
#define PyApi_List_CheckAndDowncast(OBJ, LIST) \
    (PyRef_IsList(OBJ) ? (LIST = PyApi_List_UnsafeCast(OBJ), 1) : 0)
```

