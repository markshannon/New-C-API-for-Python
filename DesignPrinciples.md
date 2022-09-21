
# Design principles

The API will adhere, as much as possible, to the following design principles.
The priniciples are listed in order of importance, with the most important ones first.

## No invalid states

No safe input[1] to the an API can create an invalid state in the virtual machine.
This principle must be applied to all API functions, without exception.
Examples of this are:

* If a function accepts pointers, it must accept `NULL`.
* If a function takes a `signed` integer as an input for a length,
  it must handle negative numbers.

[1] A safe input is one that does not break obvious invariants.
For example, if an API takes an array and a length, those values must match.
Likewise, inputs must be type-safe.

## Minimize the chance of the user supplying invalid input.

This requires judgement, and depends on the use case. Nevertheless it is an important principle.
For example, by making `PyRef` a struct, it cannot be simply cast to a `PyTupleRef`.

## Make it difficult for users to ignore error conditions

Generally this means returning error codes in a way that is difficult to ignore.

## The API should be efficient as possible

We assume that users of the API are using C, or other low-level language for performance.
If users avoid the C-API, delving into CPython internals, it undermines the point of having 
the C-API

## Completeness

The C-API should be complete. There should be no need to access VM internals.
This means that the C-API needs to cover all Python features, and most of the VM functionality.

## No privileged users

The standard library will use the same API as third-party code, without exception.
This helps to ensure completeness and encourages implementers to make the API efficient.

## Consistency

The API should be consistent in naming, and usage. It should be possible to infer
what an API function does from its name and argument.

## Minimum of implicit state

Some implicit state is necessary, but most, if not all, should be explicit.
Passing state explicitly allows control over which extension defined functions
have access to what state, improving robustness.

## API and ABI equivalence

All code written to the API will continue to work on future versions of Python
without recompilation. Recompilation using newer versions may be more efficient,
but code compiled to older versions of the API will continue to work.

## API stability

Once added to the API, a feature will be removed only if there is a very
strong reason to do so.

The semantics and interface of a function or struct will never change.
It will either remain unchanged or be removed, and possibly replaced.

## The API should be portable across Python implementations and future proof

The current design of CPython is constrained by the C-API.
We want to provide a faster Python for all users, and the C-API
should not prevent that. The HPy project shows that this can be done efficiently.

## The API should be pure C.

That means no `#ifdef __cplusplus` or similar constructs.
We do this, not because we don't want people to use C++, but because
we want them to be able to use Rust, or whatever other low-level 
language they want. A C API offers a common basis for all languages.
