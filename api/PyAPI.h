/* This file is generated from api.py by gen/__main__.py */

PyRef PyRef_INVALID;
PyExceptionRef PyRef_NO_EXCEPTION;

PyRef PyRef_Dup(PyRef ref);
PyRef PyRef_Close(PyRef ref);

/* Tuple */
PyTupleRef PyApi_Tuple_Empty(PyContext ctx);

PyTupleRef PyApi_Tuple_FromNonEmptyArray(PyContext ctx, PyRef array[], uintptr_t length);

PyTupleRef PyApi_Tuple_FromArray(PyContext ctx, PyRef array[], uintptr_t length);

PyRef PyApi_Tuple_GetItem(PyContext ctx, PyTupleRef self, uintptr_t index);

uintptr_t PyApi_Tuple_GetSize(PyContext ctx, PyTupleRef self);

bool PyApi_IsATuple(PyRef ref);
PyTupleRef PyApi_Tuple_UnsafeCast(PyRef ref);
PyTupleRef PyApi_Tuple_DownCast(PyRef ref);
PyRef PyApi_Tuple_UpCast(PyTupleRef ref);

typedef PyRef (*PyApi_BinaryOperator_FuncPtr)(PyContext ctx, PyRef left, PyRef right);

typedef PyRef (*PyApi_VectorCall_FuncPtr)(PyContext ctx, PyRef callable, PyRef args[], intptr_t nargsf, PyTupleRef kwnames);


/* Str */
PyStrRef PyApi_Str_FromUtfString(PyContext ctx, const UtfString data, uintptr_t length);

PyStrRef PyApi_Str_Join(PyContext ctx, PyStrRef self, PyStrRef array[]);

PyRef PyApi_Str_GetItem(PyContext ctx, PyStrRef self, uintptr_t index);

uintptr_t PyApi_Str_GetSize(PyContext ctx, PyStrRef self);

bool PyApi_IsAStr(PyRef ref);
PyStrRef PyApi_Str_UnsafeCast(PyRef ref);
PyStrRef PyApi_Str_DownCast(PyRef ref);
PyRef PyApi_Str_UpCast(PyStrRef ref);


/* Class */
int PyApi_Class_AddBinaryOperator(PyContext ctx, uint8_t op, PyApi_BinaryOperator_FuncPtr func);

int PyApi_Class_AddVectorCallMethod(PyContext ctx, PyStrRef name, PyApi_VectorCall_FuncPtr func);

PyRef PyApi_Class_New(PyContext ctx, PyClassRef self);

bool PyApi_IsAClass(PyRef ref);
PyClassRef PyApi_Class_UnsafeCast(PyRef ref);
PyClassRef PyApi_Class_DownCast(PyRef ref);
PyRef PyApi_Class_UpCast(PyClassRef ref);

bool PyApi_IsNone(PyContext ctx, PyRef obj);

PyRef PyApi_None();

bool PyApi_IsTrue(PyContext ctx, PyRef obj);

PyRef PyApi_True();

bool PyApi_IsFalse(PyContext ctx, PyRef obj);

PyRef PyApi_False();

PyClassRef PyApi_TimeoutError();

PyClassRef PyApi_bool();

PyClassRef PyApi_memoryview();

PyClassRef PyApi_bytearray();

PyClassRef PyApi_bytes();

PyClassRef PyApi_classmethod();

PyClassRef PyApi_complex();

PyClassRef PyApi_dict();

PyClassRef PyApi_enumerate();

PyClassRef PyApi_filter();

PyClassRef PyApi_float();

PyClassRef PyApi_frozenset();

PyClassRef PyApi_property();

PyClassRef PyApi_int();

PyClassRef PyApi_list();

PyClassRef PyApi_map();

PyClassRef PyApi_object();

PyClassRef PyApi_range();

PyClassRef PyApi_reversed();

PyClassRef PyApi_set();

PyClassRef PyApi_slice();

PyClassRef PyApi_staticmethod();

PyClassRef PyApi_str();

PyClassRef PyApi_super();

PyClassRef PyApi_tuple();

PyClassRef PyApi_type();

PyClassRef PyApi_zip();

PyClassRef PyApi_BaseException();

PyClassRef PyApi_Exception();

PyClassRef PyApi_TypeError();

PyClassRef PyApi_StopAsyncIteration();

PyClassRef PyApi_StopIteration();

PyClassRef PyApi_GeneratorExit();

PyClassRef PyApi_SystemExit();

PyClassRef PyApi_KeyboardInterrupt();

PyClassRef PyApi_ImportError();

PyClassRef PyApi_ModuleNotFoundError();

PyClassRef PyApi_OSError();

PyClassRef PyApi_EnvironmentError();

PyClassRef PyApi_IOError();

PyClassRef PyApi_EOFError();

PyClassRef PyApi_RuntimeError();

PyClassRef PyApi_RecursionError();

PyClassRef PyApi_NotImplementedError();

PyClassRef PyApi_NameError();

PyClassRef PyApi_UnboundLocalError();

PyClassRef PyApi_AttributeError();

PyClassRef PyApi_SyntaxError();

PyClassRef PyApi_IndentationError();

PyClassRef PyApi_TabError();

PyClassRef PyApi_LookupError();

PyClassRef PyApi_IndexError();

PyClassRef PyApi_KeyError();

PyClassRef PyApi_ValueError();

PyClassRef PyApi_UnicodeError();

PyClassRef PyApi_UnicodeEncodeError();

PyClassRef PyApi_UnicodeDecodeError();

PyClassRef PyApi_UnicodeTranslateError();

PyClassRef PyApi_AssertionError();

PyClassRef PyApi_ArithmeticError();

PyClassRef PyApi_FloatingPointError();

PyClassRef PyApi_OverflowError();

PyClassRef PyApi_ZeroDivisionError();

PyClassRef PyApi_SystemError();

PyClassRef PyApi_ReferenceError();

PyClassRef PyApi_MemoryError();

PyClassRef PyApi_BufferError();

PyClassRef PyApi_Warning();

PyClassRef PyApi_UserWarning();

PyClassRef PyApi_EncodingWarning();

PyClassRef PyApi_DeprecationWarning();

PyClassRef PyApi_PendingDeprecationWarning();

PyClassRef PyApi_SyntaxWarning();

PyClassRef PyApi_RuntimeWarning();

PyClassRef PyApi_FutureWarning();

PyClassRef PyApi_ImportWarning();

PyClassRef PyApi_UnicodeWarning();

PyClassRef PyApi_BytesWarning();

PyClassRef PyApi_ResourceWarning();

PyClassRef PyApi_ConnectionError();

PyClassRef PyApi_BlockingIOError();

PyClassRef PyApi_BrokenPipeError();

PyClassRef PyApi_ChildProcessError();

PyClassRef PyApi_ConnectionAbortedError();

PyClassRef PyApi_ConnectionRefusedError();

PyClassRef PyApi_ConnectionResetError();

PyClassRef PyApi_FileExistsError();

PyClassRef PyApi_FileNotFoundError();

PyClassRef PyApi_IsADirectoryError();

PyClassRef PyApi_NotADirectoryError();

PyClassRef PyApi_InterruptedError();

PyClassRef PyApi_PermissionError();

PyClassRef PyApi_ProcessLookupError();

PyClassRef PyApi_TimeoutError();


/* Bytes */
uint8_t PyApi_Bytes_GetItem(PyContext ctx, PyBytesRef self, uintptr_t index);

PyBytesRef PyApi_Bytes_FromArray(PyContext ctx, const char * data, uintptr_t length);

uintptr_t PyApi_Bytes_GetSize(PyContext ctx, PyBytesRef self);

bool PyApi_IsABytes(PyRef ref);
PyBytesRef PyApi_Bytes_UnsafeCast(PyRef ref);
PyBytesRef PyApi_Bytes_DownCast(PyRef ref);
PyRef PyApi_Bytes_UpCast(PyBytesRef ref);


/* StrBuilder */
PyStrBuilderRef PyApi_StrBuilder_New(PyContext ctx, uintptr_t capacity);

int PyApi_StrBuilder_AppendStr(PyContext ctx, PyRef Self, PyStrRef s);

int PyApi_StrBuilder_AppendUtf8String(PyContext ctx, PyRef Self, const UtfString s);

PyStrRef PyApi_StrBuilder_ToStr(PyContext ctx, PyRef Self);

bool PyApi_IsAStrBuilder(PyRef ref);
PyStrBuilderRef PyApi_StrBuilder_UnsafeCast(PyRef ref);
PyStrBuilderRef PyApi_StrBuilder_DownCast(PyRef ref);
PyRef PyApi_StrBuilder_UpCast(PyStrBuilderRef ref);


/* TupleBuilder */
PyTupleBuilderRef PyApi_TupleBuilder_New(PyContext ctx, uintptr_t capacity);

int PyApi_TupleBuilder_Add(PyContext ctx, PyRef Self, PyStrRef s);

PyStrRef PyApi_TupleBuilder_ToTuple(PyContext ctx, PyRef Self);

bool PyApi_IsATupleBuilder(PyRef ref);
PyTupleBuilderRef PyApi_TupleBuilder_UnsafeCast(PyRef ref);
PyTupleBuilderRef PyApi_TupleBuilder_DownCast(PyRef ref);
PyRef PyApi_TupleBuilder_UpCast(PyTupleBuilderRef ref);


/* Object */
PyRef PyApi_Object_GetItem(PyContext ctx, PyRef obj, PyRef key);

PyRef PyApi_Object_GetItem_i(PyContext ctx, PyRef obj, intptr_t key);

PyRef PyApi_Object_GetItem_s(PyContext ctx, PyRef obj, const UtfString key);

int PyApi_Object_SetItem(PyContext ctx, PyRef obj, PyRef key, PyRef value);

int PyApi_Object_SetItem_i(PyContext ctx, PyRef obj, intptr_t key, PyRef value);

int PyApi_Object_SetItem_s(PyContext ctx, PyRef obj, const UtfString key, PyRef value);

PyRef PyApi_Object_GetAttr(PyContext ctx, PyRef obj, PyRef attr);

PyRef PyApi_Object_GetAttr_s(PyContext ctx, PyRef obj, const UtfString attr);

int PyApi_Object_HasAttr(PyContext ctx, PyRef obj, PyRef attr);

int PyApi_Object_HasAttr_s(PyContext ctx, PyRef obj, const UtfString attr);

int PyApi_Object_SetAttr(PyContext ctx, PyRef obj, PyRef attr, PyRef value);

int PyApi_Object_SetAttr_s(PyContext ctx, PyRef obj, const UtfString attr, PyRef value);

int PyApi_Object_Contains(PyContext ctx, PyRef container, PyRef key);

PyClassRef PyApi_Object_Type(PyContext ctx, PyRef obj);

bool PyApi_Object_TypeCheck(PyContext ctx, PyRef obj, PyClassRef cls);

PyStrRef PyApi_Object_Repr(PyContext ctx, PyRef obj);

PyStrRef PyApi_Object_Str(PyContext ctx, PyRef obj);

intptr_t PyApi_Object_Hash(PyContext ctx, PyRef obj);

PyRef PyApi_Object_CallMethod(PyContext ctx, PyRef attr, PyRef args[], intptr_t nargsf);

int PyApi_Object_Compare(PyContext ctx, uint8_t op, PyRef left, PyRef right);

int PyApi_Object_IsIter(PyContext ctx, PyRef obj);

int PyApi_Object_IsAnIter(PyContext ctx, PyRef obj);


/* Dict */
PyRef PyApi_Dict_Get(PyContext ctx, PyDictRef self, PyRef key, PyRef default);

PyRef PyApi_Dict_GetItem(PyContext ctx, PyDictRef self, PyRef key);

PyDictRef PyApi_Dict_New(PyContext ctx);

bool PyApi_IsADict(PyRef ref);
PyDictRef PyApi_Dict_UnsafeCast(PyRef ref);
PyDictRef PyApi_Dict_DownCast(PyRef ref);
PyRef PyApi_Dict_UpCast(PyDictRef ref);


/* Int */
PyIntRef PyApi_Int_FromInt32(PyContext ctx, int32_t val);

PyIntRef PyApi_Int_FromUInt32(PyContext ctx, int32_t val);

PyIntRef PyApi_Int_FromInt64(PyContext ctx, int32_t val);

PyIntRef PyApi_Int_FromUInt64(PyContext ctx, int32_t val);

int32_t PyApi_Int_ToInt32(PyContext ctx, PyIntRef self);

int64_t PyApi_Int_ToInt64(PyContext ctx, PyIntRef self);

bool PyApi_IsAnInt(PyRef ref);
PyIntRef PyApi_Int_UnsafeCast(PyRef ref);
PyIntRef PyApi_Int_DownCast(PyRef ref);
PyRef PyApi_Int_UpCast(PyIntRef ref);


/* List */
PyListRef PyApi_List_New(PyContext ctx);

int PyApi_List_Append(PyContext ctx, PyListRef self, PyRef item);

PyRef PyApi_List_GetItem(PyContext ctx, PyListRef self, uintptr_t index);

uintptr_t PyApi_List_GetSize(PyContext ctx, PyListRef self);

PyRef PyApi_List_Pop(PyContext ctx, PyListRef self);

bool PyApi_IsAList(PyRef ref);
PyListRef PyApi_List_UnsafeCast(PyRef ref);
PyListRef PyApi_List_DownCast(PyRef ref);
PyRef PyApi_List_UpCast(PyListRef ref);


/* Operators */
PyRef PyApi_Operators_UnaryOp(PyContext ctx, uint8_t op, PyRef argument);

PyRef PyApi_Operators_BinaryOp(PyContext ctx, uint8_t op, PyRef left, PyRef right);

PyRef PyApi_Operators_Compare(PyContext ctx, PyRef left, PyRef right, uint8_t op);

int PyApi_Operators_CompareBool(PyContext ctx, PyRef left, PyRef right, uint8_t op);


/* Exception */
PyExceptionRef PyApi_Exception_FromString(PyContext ctx, PyClassRef cls, const UtfString message);

PyExceptionRef PyApi_Exception_FromValue(PyContext ctx, PyClassRef cls, PyRef message);

void PyApi_Exception_Fatal(PyContext ctx, const UtfString message);

PyExceptionRef PyApi_Exception_FromErrnoWithFilename(PyContext ctx, PyClassRef cls, const UtfString filename);

/* Always fails. Barring another error,
        will set *error to the newly created exception.
         */
PyExceptionRef PyApi_Exception_RaiseFromString(PyContext ctx, PyClassRef cls, const UtfString message);

/* Always fails. Barring another error,
        will set *error to the newly created exception.
         */
PyExceptionRef PyApi_Exception_RaiseFromValue(PyContext ctx, PyClassRef cls, PyRef message);

/* If the immediately previous API call failed,
        then return the exception set by that exception.
        Otherwise, return either an arbitrary exception
        or PyRef_NO_EXCEPTION */
PyExceptionRef PyApi_Exception_GetLatestException(PyContext ctx);

bool PyApi_IsAnException(PyRef ref);
PyExceptionRef PyApi_Exception_UnsafeCast(PyRef ref);
PyExceptionRef PyApi_Exception_DownCast(PyRef ref);
PyRef PyApi_Exception_UpCast(PyExceptionRef ref);


/* Call */
int PyApi_Call_IsCallable(PyContext ctx, PyRef obj);

PyRef PyApi_Call_TupleDict(PyContext ctx, PyRef callable, PyTupleRef args, PyDictRef kwargs);

PyRef PyApi_Call_Vector(PyContext ctx, PyRef callable, PyRef args[], intptr_t nargsf, PyTupleRef kwnames);


/* Iter */
PyRef PyApi_Iter_Next(PyContext ctx, PyRef obj);

/* If no more results are available then, instead of raising StopIteration,
*error = PyRef_NO_EXCEPTION.
This is more efficient than the plain Next function. */
PyRef PyApi_Iter_NextX(PyContext ctx, PyRef obj);

PyRef PyApi_Iter_Send(PyContext ctx, PyRef obj);

/* If no exception is raised, then returned is set to 0 for
a yield, and 1 for a return.
This is more efficient than the plain Send function. */
PyRef PyApi_Iter_SendX(PyContext ctx, PyRef obj, int * returned);


/* Code */
bool PyApi_IsACode(PyRef ref);
PyCodeRef PyApi_Code_UnsafeCast(PyRef ref);
PyCodeRef PyApi_Code_DownCast(PyRef ref);
PyRef PyApi_Code_UpCast(PyCodeRef ref);


/* FrameStack */
PyRef PyApi_FrameStack_GetLocal(PyContext ctx, uintptr_t depth, uintptr_t index);

PyRef PyApi_FrameStack_GetLocalByName(PyContext ctx, uintptr_t depth, PyStrRef name);

PyRef PyApi_FrameStack_GetLocalByCName(PyContext ctx, uintptr_t depth, const UtfString name);

PyCodeRef PyApi_FrameStack_GetCode(PyContext ctx, uintptr_t depth);

