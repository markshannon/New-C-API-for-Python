
class Int:
    def __init__(self, size, signed = True):
        self.size = size
        self.signed = signed
        prefix = "" if signed else "u"
        self.name = f"{prefix}int{size}_t"

intptr_t = Int("ptr")
uintptr_t = Int("ptr", False)
uint8_t = Int(8, False)
int32_t = Int(32)
uint32_t = Int(32, False)
int64_t = Int(64)
uint64_t = Int(64, False)

def abi(abi_string):
    def deco(func):
        func.abi_string = abi_string
        return func
    return deco

def namespace(cls):
    cls._is_namespace = True
    return cls

def is_namespace(cls):
    return hasattr(cls, "_is_namespace")

Self = object()
Void = object()
Size = object()

def no_fail(func):
    func._no_fail = True
    return func

def cannot_fail(func):
    return hasattr(func, "_no_fail")

def function_pointer(func):
    func._function_pointer = True
    return func

def is_function_pointer(func):
    return hasattr(func, "_function_pointer")

def no_monadic(func):
    func._no_monadic = True
    return func

def allows_monadic(func):
    return not hasattr(func, "_no_monadic")

def no_result(func):
    ret_type = func.__annotations__.get("return", None)
    return ret_type is Void

def shared(func):
    "Marker for things that returned shared references."
    return func

exports = (
    intptr_t, uintptr_t, uint8_t, int32_t, uint32_t, int64_t, uint64_t,
    abi, namespace, Self, Void, no_fail, function_pointer, no_monadic,
    shared
)


__all__ = [name for name in globals() if globals()[name] in exports]