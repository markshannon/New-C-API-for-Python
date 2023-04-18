
from __future__ import annotations
from types import FunctionType
from .abi import is_namespace, Int, Self, Void, Size, uint8_t, no_result, cannot_fail, is_function_pointer, is_shared

from . import api

CONTEXT = "PyContext ctx"

def func_ptr_name(func):
    return f"PyApi_{func.__name__}_FuncPtr"

def ctype_for_class(cls, namespace):
    if cls is object:
        return "PyRef"
    if isinstance(cls, FunctionType):
        return func_ptr_name(cls)
    if isinstance(cls, str):
        return cls
    if cls is Self:
        return f"Py{namespace}Ref"
    if cls is bool:
        return "bool"
    if cls is int:
        return "int"
    if cls is Void:
        return "void"
    if isinstance(cls, Int):
        return cls.name
    return f"Py{cls.__name__}Ref"

def get_arg_decl(name, namespace, annotations):
    if name == "self":
        return [f"Py{namespace}Ref", "self"]
    cls = annotations.get(name, object)
    if isinstance(cls, list):
        return [f"{ctype_for_class(cls[0], namespace)}", f"{name}[]"]
    else:
        return [f"{ctype_for_class(cls, namespace)}", f"{name}"]

def flatten_args(arg_list):
    return [ f"{type} {name}" for (type, name) in arg_list]

def get_result_type(func):
    return func.__annotations__.get("return", object)

def generate_function_pointer(func):
    func_name = func_ptr_name(func)
    arg_names = func.__code__.co_varnames[: func.__code__.co_argcount]
    annotations = func.__annotations__
    arg_decls = [ get_arg_decl(name, None, annotations) for name in arg_names]
    assert not cannot_fail(func)
    result_type = get_result_type(func)
    assert result_type is object
    all_args = [ CONTEXT ] + flatten_args(arg_decls)
    print(f"typedef PyRef (*{func_name})({', '.join(all_args)});\n")


def generate_api_func(namespace, func):
    if namespace:
        func_name = f"PyApi_{namespace}_{func.__name__}"
    else:
        func_name = f"PyApi_{func.__name__}"
    arg_names = func.__code__.co_varnames[: func.__code__.co_argcount]
    annotations = func.__annotations__
    arg_decls = [ get_arg_decl(name, namespace, annotations) for name in arg_names]
    return_type = get_result_type(func)
    return_arg = None
    if not cannot_fail(func):
        if return_type is Void or return_type is bool:
            return_type = int
        if isinstance(cls, Int):
            return_arg = return_type
            return_type = int
    return_type = ctype_for_class(return_type, namespace)
    all_args = flatten_args(arg_decls)
    if not is_shared(func):
        all_args = [ CONTEXT ] + all_args
    if return_arg is not None:
        all_args.append(ctype_for_class(return_arg, namespace)+"*")
    if func.__doc__:
        print(f"/* {func.__doc__} */")
    print(f"{return_type} {func_name}({', '.join(all_args)});\n")


print("/* This file is generated from api.py by gen/__main__.py */\n")

#Helpers
print("PyRef PyRef_INVALID;")
print("PyExceptionRef PyRef_NO_EXCEPTION;\n")

print("PyRef PyRef_Dup(PyRef ref);")
print("PyRef PyRef_Close(PyRef ref);")

for name, obj in api.__dict__.items():
    if isinstance(obj, FunctionType):
        if is_function_pointer(obj):
            generate_function_pointer(obj)
        else:
            generate_api_func(None, obj)
    if not isinstance(obj, type):
        continue
    cls = obj
    print(f"\n/* {name} */")
    for fname, func in cls.__dict__.items():
        if not fname.startswith("_"):
            generate_api_func(name, func)
    if not is_namespace(cls):
        #Checks and casts
        print(f"bool PyApi_IsA{'n' if name[0] in 'AEIOU' else ''}{name}(PyRef ref);")
        print(f"Py{name}Ref PyApi_{name}_UnsafeCast(PyRef ref);")
        print(f"Py{name}Ref PyApi_{name}_DownCast(PyRef ref);")
        print(f"PyRef PyApi_{name}_UpCast(Py{name}Ref ref);\n")
