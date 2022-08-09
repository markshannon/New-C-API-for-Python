
## API design rules

These rules should be applied when adding to the API.
They exist to provide a consid

The overall design of the API must adhere to the desing principles.
Here is one possible design

### Return structs

Many functions return a result, but may also raise an exception.
To handle thsi API functions should return a `struct` containing both
the error code and result or exception.

```C
typedef struct _py_returnval {
    int kind;
    PyRef value;
} PyResult;
```

Different functions may return variations on the above, but the `kind`
must obey the following rules:

A value of zero is always a success, and `value` must be the result.
A negative value is always an error, and `value` must be the exception raised.

Positive values can either be failures or additional success codes.
No function may return both failures and additional success codes.

For exaample, to get a value from a dictionary might have the following API:

```C
typedef enum _py_lookup_kind {
    ERROR = -1,
    FOUND = 0,
    MISSING = 1,
} PyLookupKind;

typedef struct _py_lookup {
    PyLookupKind kind;
    PyRef value;
} PyLookupResult;

PyLookupResult PyAPi_Dict_Get(PyDictRef dict, PyRef key);
```

Even in the case of `MISSING`, `value` should be set to a valid value to
minimize the chance of crashes should `value` be used.
The following use, although incorrect, will not corrupt the VM or memory:
```C
    PyRef result = PyAPi_Dict_Get(self, k).value;
```

### Naming

All API function and struct names should adhere to simple rules.
For example, function names should take the form:
Prefix_NameSpace_Operation[_REF_CONSUMPTION]
E.g.
```C
PyResult PyApi_Tuple_FromArray(uintptr_t len, PyRef *array);
```

### Use standard C99 types, not custom ones.

In other words, use `intptr_t` not `Py_ssize_t`.


### Consumption of argument references

For effficiency, there is a natural consumption of references in some API
functions. For example, appending an item to a list naturally consumes the
reference to the item, but not the list.
We denote borrowed references by `B` and consumed references by `C`.

Consequently we want the low-level API/ABI function to be:

```C
int PyApi_List_Append_BC(PyListRef list, PyRef item);
```

All ABI functionsshoudl get a higher level API function without a suffix.
All non-suffix functions borrow the references to all their arguments.

```C
int PyApi_List_Append(PyListRef list, PyRef item);
```
is equivalent to `PyApi_List_Append_BB`.

Functions taking arrays must consume all the references in the array,
or borrow all references in the array.

The reference behavior must be the safe regardless of the return value or
result. 

Note that this doesn't impact the portability of the API as the borrow
or consume forms can be mechanically create from the other.


### Opaque, linear references

The C-API will refer to Python objects through opaque references
which must have exactly one owner. This design has been shown to
be efficient, robust and portable by the HPy project, where the
references are known as "handles".
As each reference has exactly one owner, there will be no 
incrementing or decrementing of reference counts. References can
be duplicated with
```C
PyRef PyRef_Dup(PyRef ref);
```
and destroyed by
```C
void PyRef_Clear(PyRef ref);
```

Type specific variants will be provided for subtypes like `PyListRef`.


### ABI functions should be efficient, API functions easy to use

There is a tension between ease of use and performance.
For example, it is the common case when creating a tuple that 
the length is known, yet the function needs to treat length zero
differently, returning the empty tuple singleton.

We handle this tension by providing an efficient, but difficult use
ABI function:
```C
PyResult PyApi_Tuple_FromNonEmptyArray_nC(uintptr_tlen, PyRef *array);
```
and the easier to use API function
```C
PyResult PyApi_Tuple_FromArray(uintptr_tlen, PyRef *array);
```

But we can do better, as the API can include macros, we can implement
```C
PyTupleResult PyApi_Tuple_FromFixedArray(array);
```
something like this:
```
#define PyResult PyApi_Tuple_FromFixedArray(array) \
    ((sizeof(array) == 0) ? \
        PyApi_NewRefEmptyTuple() \
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

### The API should include versions of functions that take result types.

For most* API functions, at least those that take one or two `PyRef` arguments,
there should be a version that takes a `PyResult` as the first argument.

This function gets an `M` suffix.

This allows chaining of calls without being overwhelmed by error handling.

Suppose we want to write a function that returns the name of the class of
the argument.

Using the `M` forms we can implement this as:
```C
PyStrResult pop_and_pair(PyRef o)
{
    return Py_Type_GetName_M(PyApi_Object_GetType(o));
}
```

The implementation is straightforward and can be automatically generated:
```
inline PyResult Py_Type_GetName_M(PyResult r) 
{
    if (r.kind < 0) {
        return r;
    }
    return Py_Type_GetName(r.value);
}
```

For the technically minded, this pattern is known as the "error monad".

*Probably all, as we automatically generate these.
