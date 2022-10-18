/* This file is generated from api.py by gen/__main__.py */

PyRef PyRef_INVALID;
PyExceptionRef PyRef_NO_EXCEPTION;


/* Tuple */
PyTupleRef PyApi_Tuple_Empty(PyContext ctx);

PyTupleRef PyApi_Tuple_FromNonEmptyArray(PyContext ctx, PyRef array[], uintptr_t length, PyExceptionRef *exc);

PyTupleRef PyApi_Tuple_FromArray(PyContext ctx, PyRef array[], uintptr_t length, PyExceptionRef *exc);

PyRef PyApi_Tuple_GetItem(PyContext ctx, PyTupleRef self, uintptr_t index, PyExceptionRef *exc);

uintptr_t PyApi_Tuple_GetSize(PyContext ctx, PyTupleRef self);

bool PyApi_IsATuple(PyRef ref);
PyTupleRef PyApi_Tuple_UnsafeCast(PyRef ref);
PyTupleRef PyApi_Tuple_DownCast(PyRef ref);
PyRef PyApi_Tuple_UpCast(PyTupleRef ref);

typedef int (*PyApi_BinaryOperator_FuncPtr)(PyContext ctx, PyRef left, PyRef right, PyRef *result);

typedef int (*PyApi_VectorCall_FuncPtr)(PyContext ctx, PyRef callable, PyRef args[], intptr_t nargsf, PyTupleRef kwnames, PyRef *result);


/* Str */
PyStrRef PyApi_Str_FromUtfString(PyContext ctx, const UtfString data, uintptr_t length, PyExceptionRef *exc);

PyStrRef PyApi_Str_Join(PyContext ctx, PyStrRef self, PyStrRef array[], PyExceptionRef *exc);

PyRef PyApi_Str_GetItem(PyContext ctx, PyStrRef self, uintptr_t index, PyExceptionRef *exc);

uintptr_t PyApi_Str_GetSize(PyContext ctx, PyStrRef self);

bool PyApi_IsAStr(PyRef ref);
PyStrRef PyApi_Str_UnsafeCast(PyRef ref);
PyStrRef PyApi_Str_DownCast(PyRef ref);
PyRef PyApi_Str_UpCast(PyStrRef ref);


/* Class */
PyExceptionRef PyApi_Class_AddBinaryOperator(PyContext ctx, uint8_t op, PyApi_BinaryOperator_FuncPtr func);

PyExceptionRef PyApi_Class_AddVectorCallMethod(PyContext ctx, PyStrRef name, PyApi_VectorCall_FuncPtr func);

PyRef PyApi_Class_New(PyContext ctx, PyClassRef self, PyExceptionRef *exc);

bool PyApi_IsAClass(PyRef ref);
PyClassRef PyApi_Class_UnsafeCast(PyRef ref);
PyClassRef PyApi_Class_DownCast(PyRef ref);
PyRef PyApi_Class_UpCast(PyClassRef ref);

bool PyApi_IsNone(PyContext ctx, PyRef obj);

PyRef PyApi_None(PyContext ctx);

bool PyApi_IsTrue(PyContext ctx, PyRef obj);

PyRef PyApi_True(PyContext ctx);

bool PyApi_IsFalse(PyContext ctx, PyRef obj);

PyRef PyApi_False(PyContext ctx);

PyClassRef PyApi_TimeoutError(PyContext ctx);

PyClassRef PyApi_BaseException(PyContext ctx);


/* Exception */
PyExceptionRef PyApi_Exception_FromString(PyContext ctx, PyClassRef cls, const UtfString message, PyExceptionRef *exc);

PyExceptionRef PyApi_Exception_FromValue(PyContext ctx, PyClassRef cls, PyRef message, PyExceptionRef *exc);

void PyApi_Exception_Fatal(PyContext ctx, const UtfString message);

PyExceptionRef PyApi_Exception_FromErrnoWithFilename(PyContext ctx, PyClassRef cls, const UtfString filename, PyExceptionRef *exc);

/* Always fails. Returns, barring another error,
        { PyRef PyRef_INVALID, new_exception }
         */
PyExceptionRef PyApi_Exception_RaiseFromString(PyContext ctx, PyClassRef cls, const UtfString message, PyExceptionRef *exc);

/* Always fails. Returns, barring another error,
        { PyRef PyRef_INVALID, new_exception }
         */
PyExceptionRef PyApi_Exception_RaiseFromValue(PyContext ctx, PyClassRef cls, PyRef message, PyExceptionRef *exc);

bool PyApi_IsAnException(PyRef ref);
PyExceptionRef PyApi_Exception_UnsafeCast(PyRef ref);
PyExceptionRef PyApi_Exception_DownCast(PyRef ref);
PyRef PyApi_Exception_UpCast(PyExceptionRef ref);

PyClassRef PyApi_TypeError(PyContext ctx);

PyClassRef PyApi_StopAsyncIteration(PyContext ctx);

PyClassRef PyApi_StopIteration(PyContext ctx);

PyClassRef PyApi_GeneratorExit(PyContext ctx);

PyClassRef PyApi_SystemExit(PyContext ctx);

PyClassRef PyApi_KeyboardInterrupt(PyContext ctx);

PyClassRef PyApi_ImportError(PyContext ctx);

PyClassRef PyApi_ModuleNotFoundError(PyContext ctx);

PyClassRef PyApi_OSError(PyContext ctx);

PyClassRef PyApi_EnvironmentError(PyContext ctx);

PyClassRef PyApi_IOError(PyContext ctx);

PyClassRef PyApi_EOFError(PyContext ctx);

PyClassRef PyApi_RuntimeError(PyContext ctx);

PyClassRef PyApi_RecursionError(PyContext ctx);

PyClassRef PyApi_NotImplementedError(PyContext ctx);

PyClassRef PyApi_NameError(PyContext ctx);

PyClassRef PyApi_UnboundLocalError(PyContext ctx);

PyClassRef PyApi_AttributeError(PyContext ctx);

PyClassRef PyApi_SyntaxError(PyContext ctx);

PyClassRef PyApi_IndentationError(PyContext ctx);

PyClassRef PyApi_TabError(PyContext ctx);

PyClassRef PyApi_LookupError(PyContext ctx);

PyClassRef PyApi_IndexError(PyContext ctx);

PyClassRef PyApi_KeyError(PyContext ctx);

PyClassRef PyApi_ValueError(PyContext ctx);

PyClassRef PyApi_UnicodeError(PyContext ctx);

PyClassRef PyApi_UnicodeEncodeError(PyContext ctx);

PyClassRef PyApi_UnicodeDecodeError(PyContext ctx);

PyClassRef PyApi_UnicodeTranslateError(PyContext ctx);

PyClassRef PyApi_AssertionError(PyContext ctx);

PyClassRef PyApi_ArithmeticError(PyContext ctx);

PyClassRef PyApi_FloatingPointError(PyContext ctx);

PyClassRef PyApi_OverflowError(PyContext ctx);

PyClassRef PyApi_ZeroDivisionError(PyContext ctx);

PyClassRef PyApi_SystemError(PyContext ctx);

PyClassRef PyApi_ReferenceError(PyContext ctx);

PyClassRef PyApi_MemoryError(PyContext ctx);

PyClassRef PyApi_BufferError(PyContext ctx);

PyClassRef PyApi_Warning(PyContext ctx);

PyClassRef PyApi_UserWarning(PyContext ctx);

PyClassRef PyApi_DeprecationWarning(PyContext ctx);

PyClassRef PyApi_PendingDeprecationWarning(PyContext ctx);

PyClassRef PyApi_SyntaxWarning(PyContext ctx);

PyClassRef PyApi_RuntimeWarning(PyContext ctx);

PyClassRef PyApi_FutureWarning(PyContext ctx);

PyClassRef PyApi_ImportWarning(PyContext ctx);

PyClassRef PyApi_UnicodeWarning(PyContext ctx);

PyClassRef PyApi_BytesWarning(PyContext ctx);

PyClassRef PyApi_ResourceWarning(PyContext ctx);

PyClassRef PyApi_ConnectionError(PyContext ctx);

PyClassRef PyApi_BlockingIOError(PyContext ctx);

PyClassRef PyApi_BrokenPipeError(PyContext ctx);

PyClassRef PyApi_ChildProcessError(PyContext ctx);

PyClassRef PyApi_ConnectionAbortedError(PyContext ctx);

PyClassRef PyApi_ConnectionRefusedError(PyContext ctx);

PyClassRef PyApi_ConnectionResetError(PyContext ctx);

PyClassRef PyApi_FileExistsError(PyContext ctx);

PyClassRef PyApi_FileNotFoundError(PyContext ctx);

PyClassRef PyApi_IsADirectoryError(PyContext ctx);

PyClassRef PyApi_NotADirectoryError(PyContext ctx);

PyClassRef PyApi_InterruptedError(PyContext ctx);

PyClassRef PyApi_PermissionError(PyContext ctx);

PyClassRef PyApi_ProcessLookupError(PyContext ctx);

PyClassRef PyApi_TimeoutError(PyContext ctx);


/* Bytes */
uint8_t PyApi_Bytes_GetItem(PyContext ctx, PyBytesRef self, uintptr_t index, PyExceptionRef *exc);

PyBytesRef PyApi_Bytes_FromArray(PyContext ctx, const char * data, uintptr_t length, PyExceptionRef *exc);

uintptr_t PyApi_Bytes_GetSize(PyContext ctx, PyBytesRef self, PyExceptionRef *exc);

bool PyApi_IsABytes(PyRef ref);
PyBytesRef PyApi_Bytes_UnsafeCast(PyRef ref);
PyBytesRef PyApi_Bytes_DownCast(PyRef ref);
PyRef PyApi_Bytes_UpCast(PyBytesRef ref);


/* StrBuilder */
PyStrBuilderRef PyApi_StrBuilder_New(PyContext ctx, uintptr_t capacity, PyExceptionRef *exc);

PyExceptionRef PyApi_StrBuilder_AppendStr(PyContext ctx, PyRef Self, PyStrRef s);

PyExceptionRef PyApi_StrBuilder_AppendUtf8String(PyContext ctx, PyRef Self, const UtfString s);

PyStrRef PyApi_StrBuilder_ToStr(PyContext ctx, PyRef Self, PyExceptionRef *exc);

bool PyApi_IsAStrBuilder(PyRef ref);
PyStrBuilderRef PyApi_StrBuilder_UnsafeCast(PyRef ref);
PyStrBuilderRef PyApi_StrBuilder_DownCast(PyRef ref);
PyRef PyApi_StrBuilder_UpCast(PyStrBuilderRef ref);


/* TupleBuilder */
PyTupleBuilderRef PyApi_TupleBuilder_New(PyContext ctx, uintptr_t capacity, PyExceptionRef *exc);

PyExceptionRef PyApi_TupleBuilder_Add(PyContext ctx, PyRef Self, PyStrRef s);

PyStrRef PyApi_TupleBuilder_ToTuple(PyContext ctx, PyRef Self, PyExceptionRef *exc);

bool PyApi_IsATupleBuilder(PyRef ref);
PyTupleBuilderRef PyApi_TupleBuilder_UnsafeCast(PyRef ref);
PyTupleBuilderRef PyApi_TupleBuilder_DownCast(PyRef ref);
PyRef PyApi_TupleBuilder_UpCast(PyTupleBuilderRef ref);


/* Object */
PyRef PyApi_Object_GetItem(PyContext ctx, PyRef obj, PyRef key, PyExceptionRef *exc);

PyRef PyApi_Object_GetItem_i(PyContext ctx, PyRef obj, intptr_t key, PyExceptionRef *exc);

PyRef PyApi_Object_GetItem_s(PyContext ctx, PyRef obj, const UtfString key, PyExceptionRef *exc);

PyExceptionRef PyApi_Object_SetItem(PyContext ctx, PyRef obj, PyRef key, PyRef value);

PyExceptionRef PyApi_Object_SetItem_i(PyContext ctx, PyRef obj, intptr_t key, PyRef value);

PyExceptionRef PyApi_Object_SetItem_s(PyContext ctx, PyRef obj, const UtfString key, PyRef value);

PyRef PyApi_Object_GetAttr(PyContext ctx, PyRef obj, PyRef attr, PyExceptionRef *exc);

PyRef PyApi_Object_GetAttr_s(PyContext ctx, PyRef obj, const UtfString attr, PyExceptionRef *exc);

int PyApi_Object_HasAttr(PyContext ctx, PyRef obj, PyRef attr, PyExceptionRef *exc);

int PyApi_Object_HasAttr_s(PyContext ctx, PyRef obj, const UtfString attr, PyExceptionRef *exc);

PyExceptionRef PyApi_Object_SetAttr(PyContext ctx, PyRef obj, PyRef attr, PyRef value);

PyExceptionRef PyApi_Object_SetAttr_s(PyContext ctx, PyRef obj, const UtfString attr, PyRef value);

int PyApi_Object_Contains(PyContext ctx, PyRef container, PyRef key, PyExceptionRef *exc);

PyClassRef PyApi_Object_Type(PyContext ctx, PyRef obj);

bool PyApi_Object_TypeCheck(PyContext ctx, PyRef obj, PyClassRef cls);

PyStrRef PyApi_Object_Repr(PyContext ctx, PyRef obj, PyExceptionRef *exc);

PyStrRef PyApi_Object_Str(PyContext ctx, PyRef obj, PyExceptionRef *exc);

intptr_t PyApi_Object_Hash(PyContext ctx, PyRef obj, PyExceptionRef *exc);

PyRef PyApi_Object_CallMethod(PyContext ctx, PyRef attr, PyRef args[], intptr_t nargsf, PyExceptionRef *exc);

int PyApi_Object_Compare(PyContext ctx, uint8_t op, PyRef left, PyRef right, PyExceptionRef *exc);

int PyApi_Object_IsIter(PyContext ctx, PyRef obj, PyExceptionRef *exc);

int PyApi_Object_IsAIter(PyContext ctx, PyRef obj, PyExceptionRef *exc);


/* Dict */
PyRef PyApi_Dict_Get(PyContext ctx, PyDictRef self, PyRef key, PyRef default, PyExceptionRef *exc);

PyRef PyApi_Dict_GetItem(PyContext ctx, PyDictRef self, PyRef key, PyExceptionRef *exc);

PyDictRef PyApi_Dict_New(PyContext ctx, PyExceptionRef *exc);

bool PyApi_IsADict(PyRef ref);
PyDictRef PyApi_Dict_UnsafeCast(PyRef ref);
PyDictRef PyApi_Dict_DownCast(PyRef ref);
PyRef PyApi_Dict_UpCast(PyDictRef ref);


/* Int */
PyIntRef PyApi_Int_FromInt32(PyContext ctx, int32_t val, PyExceptionRef *exc);

PyIntRef PyApi_Int_FromUInt32(PyContext ctx, int32_t val, PyExceptionRef *exc);

PyIntRef PyApi_Int_FromInt64(PyContext ctx, int32_t val, PyExceptionRef *exc);

PyIntRef PyApi_Int_FromUInt64(PyContext ctx, int32_t val, PyExceptionRef *exc);

int32_t PyApi_Int_ToInt32(PyContext ctx, PyIntRef self, PyExceptionRef *exc);

int64_t PyApi_Int_ToInt64(PyContext ctx, PyIntRef self, PyExceptionRef *exc);

bool PyApi_IsAnInt(PyRef ref);
PyIntRef PyApi_Int_UnsafeCast(PyRef ref);
PyIntRef PyApi_Int_DownCast(PyRef ref);
PyRef PyApi_Int_UpCast(PyIntRef ref);


/* List */
PyListRef PyApi_List_New(PyContext ctx, PyExceptionRef *exc);

PyExceptionRef PyApi_List_Append(PyContext ctx, PyListRef self, PyRef item);

PyRef PyApi_List_GetItem(PyContext ctx, PyListRef self, uintptr_t index, PyExceptionRef *exc);

uintptr_t PyApi_List_GetSize(PyContext ctx, PyListRef self);

PyRef PyApi_List_Pop(PyContext ctx, PyListRef self, PyExceptionRef *exc);

bool PyApi_IsAList(PyRef ref);
PyListRef PyApi_List_UnsafeCast(PyRef ref);
PyListRef PyApi_List_DownCast(PyRef ref);
PyRef PyApi_List_UpCast(PyListRef ref);


/* Operators */
PyRef PyApi_Operators_UnaryOp(PyContext ctx, uint8_t op, PyRef argument, PyExceptionRef *exc);

PyRef PyApi_Operators_BinaryOp(PyContext ctx, uint8_t op, PyRef left, PyRef right, PyExceptionRef *exc);

PyRef PyApi_Operators_Compare(PyContext ctx, PyRef left, PyRef right, uint8_t op, PyExceptionRef *exc);

int PyApi_Operators_CompareBool(PyContext ctx, PyRef left, PyRef right, uint8_t op, PyExceptionRef *exc);


/* Call */
int PyApi_Call_IsCallable(PyContext ctx, PyRef obj, PyExceptionRef *exc);

PyRef PyApi_Call_TupleDict(PyContext ctx, PyRef callable, PyTupleRef args, PyDictRef kwargs, PyExceptionRef *exc);

PyRef PyApi_Call_Vector(PyContext ctx, PyRef callable, PyRef args[], intptr_t nargsf, PyTupleRef kwnames, PyExceptionRef *exc);


/* Iter */
PyRef PyApi_Iter_Next(PyContext ctx, PyRef obj, PyExceptionRef *exc);

/* If no more results are available then, instead of raising StopIteration,
*error = PyRef_NO_EXCEPTION.
This is more efficient than the plain Next function. */
PyRef PyApi_Iter_NextX(PyContext ctx, PyRef obj, PyExceptionRef *exc);

PyRef PyApi_Iter_Send(PyContext ctx, PyRef obj, PyExceptionRef *exc);

/* If no exception is raised, then returned is set to 0 for
a yield, and 1 for a return.
This is more efficient than the plain Send function. */
PyRef PyApi_Iter_SendX(PyContext ctx, PyRef obj, int * returned, PyExceptionRef *exc);


/* Code */
bool PyApi_IsACode(PyRef ref);
PyCodeRef PyApi_Code_UnsafeCast(PyRef ref);
PyCodeRef PyApi_Code_DownCast(PyRef ref);
PyRef PyApi_Code_UpCast(PyCodeRef ref);


/* FrameStack */
PyRef PyApi_FrameStack_GetLocal(PyContext ctx, uintptr_t depth, uintptr_t index, PyExceptionRef *exc);

PyRef PyApi_FrameStack_GetLocalByName(PyContext ctx, uintptr_t depth, PyStrRef name, PyExceptionRef *exc);

PyRef PyApi_FrameStack_GetLocalByCName(PyContext ctx, uintptr_t depth, const UtfString name, PyExceptionRef *exc);

PyCodeRef PyApi_FrameStack_GetCode(PyContext ctx, uintptr_t depth, PyExceptionRef *exc);

