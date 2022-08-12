
# API design rules

These rules should be applied when adding to the API.
They exist to provide a consistent API that adheres to the 
[design principles](./DesignPrinciples.md).

## Opaque, linear references

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
void PyRef_Free(PyRef ref);
```

Type specific variants will be provided for subtypes like `PyListRef`.

## No functions that mutate immutable objects

The is a consequence of the "No invalid states" design principle.
The legacy API allows inplace mutation of tuples, strings and other 
immutable object. These will not be allowed in the new API.

## Return structs

Many functions return a result, but may also raise an exception.
To handle this, all API functions that can return a value should
return a `struct` containing both the error code and result or exception.

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

For example, to get a value from a dictionary might have the following API:

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

## Naming

All API function and struct names should adhere to simple rules.
For example, function names should take the form:
Prefix_NameSpace_Operation[_REF_CONSUMPTION]
E.g.
```C
PyResult PyApi_Tuple_FromArray(uintptr_t len, PyRef *array);
```

## Use standard C99 types, not custom ones.

In other words, use `intptr_t` not `Py_ssize_t`.
This helps portability, and wrapping for other languages.

## No variable length argument lists.

In other words no `...` at the end of the parameters.
These functions tend to be cumbersome and unlikely to perform as well an
array and length pair of arguments.
Wrapping for other languages may not always be possible.

## Consumption of argument references

For effficiency, there is a natural consumption of references in some API
functions. For example, appending an item to a list naturally consumes the
reference to the item, but not the list.
We denote borrowed references by `B` and consumed references by `C`.

Consequently we want the low-level API/ABI function to be:

```C
int PyApi_List_Append_BC(PyListRef list, PyRef item);
```

All ABI functions should get a higher level API function without a suffix.
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


## ABI functions should be efficient, API functions easy to use

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

However, we can make this even easier to use by making a macro that 
takes an array directly.
```C
PyTupleResult PyApi_Tuple_FromFixedArray(array);
```
See the [examples](./examples.md) for the implementation.

## The API should include versions of functions that take result types.

For most* API functions, at least those that take one or two `PyRef` arguments,
there should be a version that takes a `PyResult` as the first argument.

This function gets an `M` suffix.

This allows chaining of calls without being overwhelmed by error handling.
To support this chaining any `M` arguments consume the reference in the
`PyResult` value.

Suppose we want to write a function that returns the name of the class of
the argument.

Using the `M` forms we can implement this as:
```C
PyStrResult get_typename(PyRef o)
{
    return Py_Type_GetName_M(PyApi_Object_GetType(o));
}
```
This correctly handles both errors and references.

The implementation of the `M` formas is straightforward and can be automatically generated:
```
inline PyResult Py_Type_GetName_M(PyResult r) 
{
    if (r.kind < 0) {
        return r;
    }
    return Py_Type_GetName_C(r.value);
}
```

For the technically minded, this pattern is known as the "error monad".

*Probably all, as we automatically generate these.

## Return and take specific types where possible

To reduce the number of dynamic type errors, we should make the API
as type-specific as we can reasonably do.
For example instead of specifying `PyApi_Function_GetCode()`
as
```C
PyRef PyApi_Function_GetCode(PyRef f)
```
we should specify it as
```C
PyCodeRef PyApi_Function_GetCode(PyFunctionRef f);
```

This may force us to add some extra casts to support the `M` form,
but should keep code cleaner overall.

## Provide a safe and easy to use set of casts

If we want to use specific types, we need casts.

### Upcasts

Upcasts are always safe, so don't need any error handling.
Upcasts will generally take the form `PyApi_TypeName_Upcast`
e.g.
```C
PyRef PyApi_List_Upcast(PyListRef l);
```

### Downcasts

Downcasts are tricky, because we can't return a more type specific ``Result`` type.
Either the ``Result`` is unsafe, due to potential errors, or it is useless as
the result of the cast is as general as its input.

Consequently the API contains macros to wrap the test then unsafe cast idiom.

For example support we want to treat an reference as a reference to a `list`.

We cannot just cast it:
```
PyListRef list = PyApi_List_UnsafeCast(obj);
```
As the name suggests, this is unsafe.

But, the following is safe:
```
if (PyApi_IsList(obj)) {
    PyListRef list = PyApi_List_UnsafeCast(obj);
}
```

To discourage the use of explicit, unsafe casts the API will include "check and downcast" macros:
```
PyApi_List_CheckAndDowncast(OBJ, LIST)
```

Which would be used as follows:
```
extern void do_something_with_list(PyListRef l);

void do_something_with_maybe_list(PyRef ref)
{
    PyListRef l;
    if (PyApi_List_CheckAndDowncast(ref, l)) {
        do_something_with_list(l);
    }
}
```

### No ABI mode

There is a tension between performance and portability. The performance impact of using portable 
function calls for low-level operations may be unacceptable for some extensions and tools.

To enable these extensions and tools to use the API, albeit at some cost in portability, there will be
a "No ABI" mode.

The "No ABI" mode would be turned on by compiling with the `PYAPI_NO_ABI` macro, used thus:
```
#define PYAPI_NO_ABI 1
#include "PyAPI.h"
```

The "No ABI" mode would expose more efficient implementations of API functions, but would not be portable
across different versions, or different implementations.

For example, many of the class checks and casts can implemented in a few instructions as an inline function
or macro, but such an implementation ties a build of code using it to a single Python implementation.

