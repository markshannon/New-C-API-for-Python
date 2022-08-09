

## Design principles

The API will adhere, as much as possible, to the following design principles.
The priniciples are listed in order of importance, with the most important ones first.

### No invalid states

No safe input[1] to the an API can create an invalid state in the virtual machine.
This principle must be applied to all API functions, without exception.
Examples of this are:

* If a function accepts pointers, it must accept `NULL`.
* If a function takes a `signed` integer as an input for a length, it must handle negative numbers.

[1] A safe input is one that does not break obvious invariants.
For example, if an API takes an array and a length, those values must match.
Likewise, inputs must be type-safe.

### Minimize the chance of the user supplying invalid input.

This requires judgement, and depends on the use case. Nevertheless it is an important principle.

### Make it difficult for users to ignore error conditions

Generally this means returning error codes in a way that is difficult to ignore.

### The API should be efficient as possible

We assume that users of the API are using C, or other low-level language for performance.
If users avoid the C-API, delving into CPython internals, it undermines the point of having 
the C-API

### Completeness

The C-API should be complete. There should be no need to access VM internals.
This means that the C-API need to cover all language features, and most of the VM functionality.

### No privileged users

The standard library will only use the same API as third-pary code.
This helps to ensure completeness and encourages implementers to make the API efficient.

### Consistency

The API should be consistent in naming, and usage. It should be possible to know
what an API function does from its name and argument. At least, once familiar with the API.

### API and ABI equivalence

Any code written using the C-API will conform to the ABI.
This a forwards-compatibility guarantee only.
E.g., code written using the C-API for 3.15 will work unmodified
on 3.16, but the opposite is not true.

This doesn't mean that all API functions are part of the ABI, but that they must call down to the ABI,
and that once in the ABI, they must remain there.

### API stability

Once added to the C-API, a feature will be removed only if there is a very strong reason (read security)
issue to do so.
The semantics and interface of a function or struct will never change.
It will either remain unchanged, or be removed, and possibly replaced.
   
### The API should be portable and future proof

The current design of CPython is constrained by the C-API.
We want to provide a faster Python for all users, and the C-API
should not prevent that. The HPy project shows that this can be done efficinetly.

### The API should be pure C.

That means no `#ifdef __cplusplus` or similar constructs.
We do this, not because we don't want people to use C++, but because
we want them to be able to use Rust, Nim, or whatever other low-level 
language they want. A C API offers a common basis for wrapping.
