# New C-API for Python

This repository is for developing the new C-API for Python.
it will contain no implementation, but will serve a repository
of design principles, rules and organization.
As well as maintaining a record of the discussions involved.

# Design principles

The new C-API will follow a dozen or so [design principles](./DesignPrinciples.md).
These are the high-level concepts that determine the nature of the API.

## Design rules

It would be laborious and error prone to consider and apply the design principles
each time a new function were added to the API.
To enable developers to follow the design principles when extending the API,
there are a number of [design rules](./DesignRules.md) for them to follow.
The intention is that by following the rules, the design principles should be observed.
Some judgement will still be required, though.

## Extent of the API

There about 1500 functions marked as `Py_API_FUNC` and about 200 objects
marked in as `Py_ABI_DATA` in the current API.

Many of these are artifacts of the implementation, but we would still expect
the API to contain many hundreds, maybe a thousand functions.

## Organization of the API

The API should be organized in categories, reflected in the namespaces of the API.
We want to break the API into namepsaces, and to be discoverable.

We anticipate that many core objects will get their own namespace, for example:

* Object
* Tuple
* List
* Str
* Bytes

Also various aspects of the runtime should also get their own namespace:

* Interpreter
* GC
* FrameStack
* Operations

## Interoperation with the legacy API

We do not expect packages to be ported to the new API in one go.
To help porting we will provide an [interop API](./Interop.md)

## Documentation

### API documentation

The documentation will follow the [Diataxis documentation framework](https://diataxis.fr/)

### Porting documentation

For each function in the legacy API, we will add documentation describing how code
using it should be ported to the new API.