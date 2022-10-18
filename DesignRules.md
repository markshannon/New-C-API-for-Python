
# API design rules

These rules should be applied when adding to the API.
They exist to provide a consistent API that adheres to the 
[design principles](./DesignPrinciples.md).

## All functions to take an opaque context

Passing a `context` parameter to API functions forces extension
code to operate on the correct context, and prevents them from
performing operations that are not safe from the given context.

`PyContext` is the full context passed to most extension functions
and that is expected by most API functions.

There are also more limited contexts that get passed to some
extension functions and allow only a more limited interaction
with the virtual machine.

For example `PyMemContext` is passed to destructor functions
which prevents them from doing much more than freeing `PyRef`s
and memory.

## Opaque, linear references

The C-API will refer to Python objects through opaque references
which must have exactly one owner. This design has been shown to
be efficient, robust and portable by the HPy project, where the
references are known as "handles".
As each reference has exactly one owner, there will be no 
incrementing or decrementing of reference counts. References can
be duplicated with
```C
PyRef PyRef_Dup(PyContext ctx, PyRef ref);
```
and destroyed by
```C
void PyRef_Close(PyContext ctx, PyRef ref);
void PyRef_Free(PyMemContext mctx, PyRef ref);
```

Type specific variants will be provided for subtypes like `PyListRef`.

## No functions that mutate immutable objects

The is a consequence of the "No invalid states" design principle.
The legacy API allows inplace mutation of tuples, strings and other 
immutable object. These will not be allowed in the new API.

## All functions have an error "out" parameter, or return the error

### Functions that have results

Many functions return a result, but may also raise an exception.
To handle this, all such API functions should have an `error` out
parameter, of the form `PyExceptionRef *error`.

The error pointer should always be the final parameter.

API functions must obey the following rules:

* If no valid result can be returned, the the result value should be `PyRef_INVALID`.
* If the result is valid, then the memory pointer to by `error` should be untouched.

Some functions can fail without an error. Failure should be represented by returning
`PyRef_INVALID` and `*error = PyRef_NO_EXCEPTION`.

For example, to get a value from a dictionary might have the following API:

```C
PyRef PyAPi_Dict_Get(PyContext ctx, PyDictRef dict, PyRef key, PyExceptionRef *value);
```

If the result is `PyRef_INVALID` then the failure and error cases can be differentiated
by testing `*error == PyRef_NO_EXCEPTION`.

### Functions without results

Some functions, e.g. `PyApi_List_Append()` do not produce a result, but can raise.
Those functions should return a `PyExceptionRef`.
```C
PyExceptionRef PyApi_List_Append(PyContext ctx, PyListRef list, PyRef item);
```
Success is indicated by returning `PyRef_NO_EXCEPTION`.

## Naming

All API function and struct names should adhere to simple rules.
For example, function names should take the form:
Prefix_NameSpace_Operation[_REF_CONSUMPTION]
E.g.
```C
PyTupleRef PyApi_Tuple_FromArray(PyContext ctx, uintptr_t len, PyRef *array, PyExceptionRef *error);
```

## Use C99 <stdint.h> types

### Use C99 integers types, not custom ones

In other words, use `intptr_t` not `Py_ssize_t`.
This helps portability, and wrapping for other languages.

### Use C99 integers types, not legacy ones

Use `int32_t`, `intptr_t`, etc. Never use `long` as it differs in size even on the same hardware.
The use of `int` is sometimes acceptable, when it is used as an enumeration, or small range.
If the return value can represent a value, then a `<stdint.h>` type should be used.

E.g.
* `int PyApi_Byte_GetItem(PyRef *array, intptr_t index, PyExceptionRef *error)` is OK.
* But `int PyApi_Tuple_GetSize(PyTupleRef *ref)` is not OK as it might overflow.
* It should be `uintptr_t PyApi_Tuple_GetSize(PyTupleRef *ref)`

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
PyExceptionRef PyApi_List_Append_BC(PyContext ctx, PyListRef list, PyRef item);
```

All ABI functions should get a higher level API function without a suffix.
All non-suffix functions borrow the references to all their arguments.

```C
PyExceptionRef PyApi_List_Append(PyContext ctx, PyListRef list, PyRef item);
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
PyTupleRef PyApi_Tuple_FromNonEmptyArray_nC(PyContext ctx, uintptr_tlen, PyRef *array, PyExceptionRef *error);
```
and the easier to use API function
```C
PyTupleRef PyApi_Tuple_FromArray(PyContext ctx, uintptr_t len, PyRef *array, PyExceptionRef *error);
```

However, we can make this even easier to use by making a macro that 
takes an array directly.
```C
PyTupleRef PyApi_Tuple_FromFixedArray(ctx, array, error);
```
See the [examples](./examples.md) for the implementation.

## Return and take specific types where possible

To reduce the number of dynamic type errors, we should make the API
as type-specific as we can reasonably do.
For example instead of specifying `PyApi_Function_GetCode()`
as
```C
PyRef PyApi_Function_GetCode(PyContext ctx, PyRef f, PyExceptionRef *error)
```
we should specify it as
```C
PyCodeRef PyApi_Function_GetCode(PyContext ctx, PyFunctionRef f);
```
which doesn't need an `error` parameter as it cannot fail.

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

Downcasts are tricky, because we can't return a more type specific ``PyRef`` type.
Either the ``PyRef`` is unsafe, due to potential errors, or it is useless as
the result of the cast, being as general as its input.

* `PyListRef PyApi_List_DownCast(PyRef obj)`: unsafe
* `PyRef PyApi_List_DownCast(PyRef obj)`: useless

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
extern void do_something_with_list(PyContext ctx, PyListRef l);

void do_something_with_maybe_list(PyContext ctx, PyRef ref)
{
    PyListRef l;
    if (PyApi_List_CheckAndDowncast(ref, l)) {
        do_something_with_list(ctx, l);
    }
}
```

### Organizing the API to ensure ABI compatibility.

* The API will be defined by `PyAPI.h`.
* `PyABI.h` will define the ABI.
* `PyAPI.h` will not contain any `extern` declarations.
* `PyAPI.h` may have macros and inline functions.
* All `extern` declarations must be in `PyABI.h`.

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

Internally, the `PyABI.h` would conceptually be something like:
```C
#ifdef  PYAPI_NO_ABI
#include "PyApi_unstable.h"
#else
#include "PyAbi_portable.h"
#endif
#include "PyAbi_common.h"
```
