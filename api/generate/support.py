PREFIX = "PyNI"
REF = "PyRef"
def TYPED_REF(t):
    return f"Py{t}Ref"
CONTEXT = "PyContext ctx"
MISSING = REF + "_MISSING"
ERROR = REF + "_ERROR"

utf_string = "const UtfString"

class Pointer:

    def __init__(self, cls):
        self.cls = cls

    def __class_getitem__(self, item):
        return Pointer(item)

class CInt:
    def __init__(self, size, signed = True):
        self.size = size
        self.signed = signed
        prefix = "" if signed else "u"
        self.name = f"{prefix}int{size}_t"

class Struct:
    pass

int8_t = CInt(8)
int16_t = CInt(16)
int32_t = CInt(32)
int64_t = CInt(64)
intptr_t = CInt("ptr")

uint8_t = CInt(8, False)
uint16_t = CInt(16, False)
uint32_t = CInt(32, False)
uint64_t = CInt(64, False)
uintptr_t = CInt("ptr", False)

def preferred(ref_string):
    def deco(func):
        func.ref_string = ref_string
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

def no_result(func):
    ret_type = func.__annotations__.get("return", None)
    return ret_type is Void

# To do -- Generate specializations
def specialization(type):
    def deco(func):
        return func
    return deco
