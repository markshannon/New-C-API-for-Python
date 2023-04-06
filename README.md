# New C-API for Python

This repository is for developing the new C-API for Python.
It will contain no implementation, but will serve as a repository
of design principles, rules, examples and other such bits and pieces.
it will also serve as a record of the discussions involved.

## Why do we need a new C API?

The current C API has expanded over decades, in an unplanned way.
Pieces get added without consideration of future maintainence,
and in a way that exposes implementation details.

This makes it hard to use, restrictive of how it can be implemented,
and in many cases unsafe.

We cannot incrementally change the current API, as each change
will cause breakage and backwards incompatibility issues, leaving
extension modules constantly broken.

Rather than change the existing C API it is better to create an entirely new API,
and deprecate the old one. This allows extension authors to switch to the new API
at a time of their choosing, rather than constantly scrambling to keep up.

## Design principles

The new C-API will follow a dozen or so [design principles](./DesignPrinciples.md).
These are the high-level concepts that determine the nature of the API.

## Design rules

It would be laborious and error prone to consider and apply the design principles
each time a new function, struct or type were added to the API.
To enable developers to follow the design principles when extending the API,
there are a number of [design rules](./DesignRules.md) for them to follow.
The intention is that by following the rules, the design principles should be observed.
Some judgement will still be required, though.

## Extent of the API

There about 1500 functions marked as `Py_API_FUNC` and about 200 objects
marked in as `Py_ABI_DATA` in the current API.

Many of these are artifacts of the implementation, but we would still expect
the API to contain many hundreds of functions.

## Organization of the API

The API should be organized in categories, reflected in the namespaces of the API.
We want to break the API into namepsaces, so that it can be discoverable.

We anticipate that many core objects will get their own namespace, for example:

* Object
* Tuple
* List
* Str
* Bytes

Various aspects of the runtime should also get their own namespace:

* Interpreter
* GC
* FrameStack
* Operations (numerical, logical, etc.)

## Interoperation with the legacy API

We do not expect packages to be ported to the new API in one go.
To help porting we will provide an [interopability API](./Interop.md)

## Implementation schedule and removal of the legacy C API

This is very much provisional at this point.

* 2023 (3.12): New C API specification complete. Deprecation of unsafe parts of legacy C API.
* 2024 (3.13): New C API implementation in CPython complete. 
* 2025 (3.14): Removal of unsafe parts of legacy C API. Deprecation of legacy C API.
* 2026 (3.15): Add warnings of parts of legacy C API with negative impact on performance.
* 2027 (3.16): Add warnings on any use of legacy C API
* 2028 (3.17): Remove parts of legacy C API with negative impact on performance.
* 2029 (3.18)
* 2030 (3.19)
* 2031 (3.20/4.0): Removal of legacy C API

The removal of the legacy C API will happen in three stages:

* 2025 (3.14): Removal of the unsafe parts of the API: parts of the API that return borrowed references, or mutate immutable objects.
* 2028 (3.17): Removal of performance limiting parts of the API. For example, parts of the API that prevent improvements to internal data structures.
* 2031 (3.20/4.0): Removal of the rest of the legacy C API.


## Documentation

### API documentation

Each function and struct will be fully documented.

If it isn't documented it isn't part of the API.
If it is part of the API it will be documented.

### Porting documentation

For functions and structs in the legacy API, we will add documentation describing how code
should be ported to the new API.

## Examples

Here are some [example API functions with implementations](./examples.md)

## Implementation in CPython

Porting CPython to the new C-API will be a lot of work, but there is a [plan](./implementation.md)
