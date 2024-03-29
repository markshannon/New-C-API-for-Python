import builtins
from unicodedata import name
from .abi import *

utf_string = "const UtfString"

class Tuple:

    @no_fail
    def Empty() -> Self: ...

    @abi("Cn")
    def FromNonEmptyArray(array: [object], length: uintptr_t) -> Self: ...

    def FromArray(array: [object], length: uintptr_t) -> Self: ...

    def GetItem(self, index: uintptr_t): ...

    @no_fail
    def GetSize(self) -> uintptr_t: ...


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
@shared
def none(): ...
none.__name__ = "None"

@no_fail
def IsTrue(obj) -> bool: ...

@no_fail
@shared
def true(): ...
true.__name__ = "True"

@no_fail
def IsFalse(obj) -> bool: ...

@no_fail
@shared
def false(): ...
false.__name__ = "False"

builtin_base_exception = BaseException
for name, cls in builtins.__dict__.items():
    # Maybe we don't want every last exception class,
    # but that's the simplest approach for now.
    if isinstance(cls, type) and name[0] != "_":
        @no_fail
        @shared
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

    @abi("C")
    def ToStr(Self) -> Str: ...

class TupleBuilder:

    def New(capacity: uintptr_t) -> Self: ...

    def Add(Self, s:Str) -> Void: ...

    @abi("C")
    def ToTuple(Self) -> Str: ...

@namespace
class Object:

    def GetItem(obj, key): ...

    def GetItem_i(obj, key: intptr_t): ...

    def GetItem_s(obj, key: utf_string): ...

    def SetItem(obj, key, value) -> Void: ...

    def SetItem_i(obj, key: intptr_t, value) -> Void: ...

    def SetItem_s(obj, key: utf_string, value) -> Void: ...

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

    def Repr(obj) -> Str: ...

    def Str(obj) -> Str: ...

    def Hash(obj) -> intptr_t: ...

    def CallMethod(attr, args: [object], nargsf: intptr_t): ...

    def Compare(op: uint8_t, left, right) -> bool: ...

    def IsIter(obj) -> bool: ...

    def IsAnIter(obj) -> bool: ...

class Dict:

    def Get(self, key, default): ...

    def GetItem(self, key): ...

    def New() -> Self: ...

class Int:

    def FromInt32(val: int32_t) -> Self: ...

    def FromUInt32(val: int32_t) -> Self: ...

    def FromInt64(val: int32_t) -> Self: ...

    def FromUInt64(val: int32_t) -> Self: ...

    def ToInt32(self) -> int32_t: ...

    def ToInt64(self) -> int64_t: ...


class List:

    def New() -> Self: ...

    @abi("BC")
    def Append(self, item) -> Void: ...

    def GetItem(self, index: uintptr_t): ...

    @no_fail
    def GetSize(self) -> uintptr_t: ...

    def Pop(self): ...


@namespace
class Operators:

    def UnaryOp(op: uint8_t, argument): ...

    def BinaryOp(op: uint8_t, left, right): ...

    def Compare(left, right, op: uint8_t): ...

    def CompareBool(left, right, op: uint8_t) -> bool: ...


class Exception:

    def FromString(cls: Class, message: utf_string) -> Self: ...

    def FromValue(cls: Class, message) -> Self: ...

    @no_fail
    def Fatal(message: utf_string) -> Void: ...

    def FromErrnoWithFilename(cls: Class, filename: utf_string) -> Self: ...

    def RaiseFromString(cls: Class, message: utf_string) -> Self:
        """Always fails. Barring another error,
        will set *error to the newly created exception.
        """

    def RaiseFromValue(cls: Class, message) -> Self:
        """Always fails. Barring another error,
        will set *error to the newly created exception.
        """

@no_fail
def GetLatestException() -> Exception:
    """If the immediately previous API call failed,
    then return the exception set by that exception.
    Otherwise, return either an arbitrary exception
    or PyRef_NO_EXCEPTION"""

@namespace
class Call:

    def IsCallable(obj) -> bool: ...

    def TupleDict(callable, args: Tuple, kwargs: Dict): ...

    def Vector(callable, args: [object], nargsf: intptr_t, kwnames: Tuple): ...

@namespace
class Iter:

    def Next(obj): ...

    def NextX(obj):
        """If no more results are available then, instead of raising StopIteration,
*error = PyRef_NO_EXCEPTION.
This is more efficient than the plain Next function."""

    def Send(obj): ...

    def SendX(obj, returned: "int *"):
        """If no exception is raised, then returned is set to 0 for
a yield, and 1 for a return.
This is more efficient than the plain Send function."""

class Bytes:

    def GetItem(self, index: uintptr_t)-> uint8_t: ...

    def FromArray(data: "const char *", length: uintptr_t) -> Self: ...

    def GetSize(self) -> uintptr_t: ...

class Code:

    "To do"

@namespace
class FrameStack:

    def GetLocal(depth: uintptr_t, index: uintptr_t): ...

    def GetLocalByName(depth: uintptr_t, name: Str): ...

    def GetLocalByCName(depth: uintptr_t, name: utf_string): ...

    def GetCode(depth: uintptr_t) -> Code: ...

del abi, namespace, no_fail, function_pointer, shared
