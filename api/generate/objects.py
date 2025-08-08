import builtins
from unicodedata import name
from .support import *

class Long:

    def FromInt32(val: int32_t) -> Self: ...

    def FromUInt32(val: int32_t) -> Self: ...

    def FromInt64(val: int32_t) -> Self: ...

    def FromUInt64(val: int32_t) -> Self: ...

    def ToInt32(self) -> int32_t: ...

    def ToInt64(self) -> int64_t: ...


class Sequence:

    def GetItem(self, index: Long):
        "Returns the item at `index`. Raises if index is out-of-bounds"

    def GetItem_i(self, index: uintptr_t):
        "Returns the item at `index`. Raises if index is out-of-bounds"

    @no_fail
    def GetSize(self) -> uintptr_t:
        ...

    def GetLength(self):
        ...


class Tuple(Sequence):

    @no_fail
    def Empty() -> Self:
        "Returns the empty tuple"

    @preferred("Cn")
    def FromNonEmptyArray(array: [object], length: uintptr_t) -> Self:
        "Returns a new non-empty tuple from `array`. `length` must be greater than zero"

    def FromArray(array: [object], length: uintptr_t) -> Self:
        "Returns a new non-empty tuple from `array`."

class Dict:

    def Get(self, key, default): ...

    def GetItem(self, key): ...

    def GetItem_s(self, key): ...

    def New() -> Self: ...


class List(Sequence):

    def New() -> Self: ...

    @preferred("BC")
    def Append(self, item) -> Void: ...

    def Pop(self): ...

    def FromArray(array: [object], length: uintptr_t) -> Self:
        "Returns a new list from `array`."

    def ExtendArray(self, array: [object], length: uintptr_t) -> Self:
        "Extends the list from `array`."

    def Extend(self, sequence) -> Void: ...

    def Insert(self, index, item) -> Void: ...

    def Insert_i(self, index: intptr_t, item) -> Void: ...

    def GetSlice(self, low: intptr_t, high: intptr_t) -> Self: ...

    def SetSlice(self, low: intptr_t, high: intptr_t, sequence) -> Self: ...

    def DelSlice(self, low: intptr_t, high: intptr_t) -> Self: ...

    def AsTuple(self) -> Tuple:
        "Return a new tuple created from this list"

    def AsTupleAndClear(self) -> Tuple:
        """Return a new tuple created from this list and clear this list.
        This may be more efficient than creating the tuple, then freeing the list"""

    def Reverse(self) -> Void: ...

    def Sort(self) -> Void: ...

    @no_fail
    def Clear(self) -> Void: ...


@function_pointer
def BinaryOperator(left, right): ...

@function_pointer
def VectorCall(callable, args: [object], nargsf: intptr_t, kwnames: Tuple): ...


#Forward declaration
class Str: 
    pass


class Class:
    
    def AddBinaryOperator(op: uint8_t, func: BinaryOperator) -> Void: ...

    def AddVectorCallMethod(name: Str, func: VectorCall) -> Void: ...

    def New(self): ...


@no_fail
def IsNone(obj) -> bool: ...

@no_fail
def none(): ...
none.__name__ = "None"

@no_fail
def IsTrue(obj) -> bool: ...

@no_fail
def true(): ...
true.__name__ = "True"

@no_fail
def IsFalse(obj) -> bool: ...

@no_fail
def false(): ...
false.__name__ = "False"

builtin_base_exception = BaseException
for name, cls in builtins.__dict__.items():
    # Maybe we don't want every last exception class,
    # but that's the simplest approach for now.
    if isinstance(cls, type) and name[0] != "_":
        @no_fail
        def f() -> Class: ...
        f.__name__ = name
        globals()["class_" + name] = f
del name, cls, builtin_base_exception


class Str:

    def FromUtfString(data: utf_string, length: uintptr_t)  -> Self: ...

    def Join(self, array: [Self]) -> Self: ...

    def GetItem(self, index: uintptr_t): ...

    @no_fail
    def GetSize(self) -> uintptr_t: ...


class Bytes:

    def FromCData(data: "const char*", length: uintptr_t)  -> Self: ...

    def GetItem(self, index: uintptr_t): ...

    @no_fail
    def GetSize(self) -> uintptr_t: ...

    def CopyToBuffer(self, start: uintptr_t, end: uintptr_t, buffer: "const char*") -> Void: ...


#Builders
class StrBuilder:

    def New(capacity: uintptr_t) -> Self: ...

    def AppendStr(Self, s:Str) -> Void: ...

    def AppendUtf8String(Self, s:utf_string) -> Void: ...

    @preferred("C")
    def ToStr(Self) -> Str: ...


class TupleBuilder:

    def New(capacity: uintptr_t) -> Self: ...

    def Add(Self, item) -> Void: ...

    @preferred("C")
    def ToTuple(Self) -> Tuple: ...


@namespace
class Object:

    @specialization(Tuple)
    @specialization(List)
    @specialization(Dict)
    def GetItem(obj, key): ...

    @specialization(Tuple)
    @specialization(List)
    def GetItem_i(obj, key: intptr_t): ...

    @specialization(Dict)
    def GetItem_s(obj, key: utf_string): ...

    @specialization(Tuple)
    @specialization(List)
    @specialization(Dict)
    def SetItem(obj, key, value) -> Void: ...

    @specialization(Tuple)
    @specialization(List)
    def SetItem_i(obj, key: intptr_t, value) -> Void: ...

    @specialization(Dict)
    def SetItem_s(obj, key: utf_string, value) -> Void: ...

    def DelItem(obj, key) -> Void: ...

    def DelItem_i(obj, key: intptr_t) -> Void: ...

    def DelItem_s(obj, key: utf_string) -> Void: ...

    def GetAttr(obj, attr): ...

    def GetAttr_s(obj, attr: utf_string): ...

    def HasAttr(obj, attr) -> bool: ...

    def HasAttr_s(obj, attr: utf_string) -> bool: ...

    def SetAttr(obj, attr, value) -> Void: ...

    def SetAttr_s(obj, attr: utf_string, value) -> Void: ...

    def Contains(container, key) -> bool: ...

    @no_fail
    def Type(obj) -> Class: ...

    @no_fail
    def TypeCheck(obj, cls: Class) -> bool: ...

    def IsInstance(obj, cls: Class) -> bool: ...

    def Repr(obj) -> Str: ...

    def Str(obj) -> Str: ...

    def ASCII(obj) -> Str: ...

    def Hash(obj) -> intptr_t: ...

    def CallMethod(attr, args: [object], nargsf: intptr_t): ...

    def IsAnIter(obj) -> bool: ...

    def IsCallable(obj) -> bool: ...

    def UnaryOp(op: uint8_t, argument): ...

    def BinaryOp(op: uint8_t, left, right): ...

    def Compare(op: uint8_t, left, right): ...

    def CompareBool(op: uint8_t, left, right) -> bool: ...


class Exception:

    def New(cls: Class, message: utf_string) -> Self: ...

    def New_s(cls: Class, message) -> Self: ...

    @no_fail
    def Fatal(message: utf_string) -> Void: ...

    def FromErrnoWithFilename(cls: Class, filename: utf_string): ...

    def RaiseNew(cls: Class, message: utf_string):
        """Always fails. Barring another error,
        will raise the newly created exception.
        """

    def RaiseNew_s(cls: Class, message):
        """Always fails. Barring another error,
        will raise the newly created exception.
        """

    def Raise(self):
        "Always fails. will raise `exc`."

    @no_fail
    def NoMemory():
        "Raises a MemoryError"

    @no_fail
    def Get() -> Exception:
        """If the immediately previous API call failed,
        then return the exception set by that exception.
        Otherwise:
            In debug mode, return an instance of APIMisuse.
            In release mode, return an arbitrary exception."""

    def Matches(exc, exc_cls: Class) -> bool: ...

    @no_fail
    def WriteUnraisable(exc) -> Void: ...

    def Warn(category, message: utf_string, stack_level: int) -> Void: ...


@namespace
class Call:

    def TupleDict(callable, args: Tuple, kwargs: Dict): ...

    def Vector(callable, args: [object], nargsf: intptr_t, kwnames: Tuple): ...

    def Method(name: str, args: [object], nargsf: intptr_t, kwnames: Tuple): ...

@namespace
class Iter:

    def Next(obj): ...
    Next.__doc__ = f" Returns {MISSING} if iterator is exhausted. {ERROR} if there is an exception."

    def Send(obj): ...

    def SendX(obj, result: Pointer[object]) -> int:
        """Returns 0 for a yield, 1 for a return and -1 for an exception.
           `*result` is set to the actual value yielded or returned.
           In case of an exception `*result` is set to None.
           This is more efficient than the plain `Send` function as there
           is no need to wrap the return value in an exception.
           """


class Bytes:

    def GetItem(self, index: uintptr_t)-> uint8_t: ...

    def FromArray(data: "const char *", length: uintptr_t) -> Self: ...

    def GetSize(self) -> uintptr_t: ...



del preferred, namespace, no_fail, function_pointer
