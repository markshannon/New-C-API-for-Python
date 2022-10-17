/* This file is generated from api.py by gen/__main__.py */

PyRef PyRef_INVALID;
PyExceptionRef PyRef_NO_EXCEPTION;


/* Tuple */
PyTupleRef PyApi_Tuple_Empty(PyContext ctx);

PyTupleRefOrError PyApi_Tuple_FromNonEmptyArray(PyContext ctx, PyRef array[], uintptr_t length);

PyTupleRefOrError PyApi_Tuple_FromArray(PyContext ctx, PyRef array[], uintptr_t length);

PyRefOrError PyApi_Tuple_GetItem(PyContext ctx, PyTupleRef self, uintptr_t index);

PyRefOrError PyApi_Tuple_GetItem_M(PyContext ctx, PyTupleRefOrError self, uintptr_t index);

int PyApi_Tuple_GetSize(PyContext ctx, PyTupleRef self);

int PyApi_Tuple_GetSize_M(PyContext ctx, PyTupleRefOrError self);

int PyApi_IsATuple(PyRef ref);
PyTupleRef PyApi_Tuple_UnsafeCast(PyRef ref);
PyTupleRefOrError PyApi_Tuple_DownCast(PyRef ref);
PyRef PyApi_Tuple_UpCast(PyTupleRef ref);

typedef int (*PyApi_BinaryOperator_FuncPtr)(PyContext ctx, PyRef left, PyRef right, PyRef *result);

typedef int (*PyApi_VectorCall_FuncPtr)(PyContext ctx, PyRef callable, PyRef args[], intptr_t nargsf, PyTupleRef kwnames, PyRef *result);


/* Str */
PyStrRefOrError PyApi_Str_FromUtfString(PyContext ctx, const UtfString data, uintptr_t length);

PyStrRefOrError PyApi_Str_Join(PyContext ctx, PyStrRef self, PyStrRef array[]);

PyStrRefOrError PyApi_Str_Join_M(PyContext ctx, PyStrRefOrError self, PyStrRef array[]);

PyRefOrError PyApi_Str_GetItem(PyContext ctx, PyStrRef self, uintptr_t index);

PyRefOrError PyApi_Str_GetItem_M(PyContext ctx, PyStrRefOrError self, uintptr_t index);

int PyApi_Str_GetSize(PyContext ctx, PyStrRef self);

int PyApi_Str_GetSize_M(PyContext ctx, PyStrRefOrError self);

int PyApi_IsAStr(PyRef ref);
PyStrRef PyApi_Str_UnsafeCast(PyRef ref);
PyStrRefOrError PyApi_Str_DownCast(PyRef ref);
PyRef PyApi_Str_UpCast(PyStrRef ref);


/* Class */
int PyApi_Class_AddBinaryOperator(PyContext ctx, uint8_t op, PyApi_BinaryOperator_FuncPtr func);

int PyApi_Class_AddVectorCallMethod(PyContext ctx, PyStrRef name, PyApi_VectorCall_FuncPtr func);

int PyApi_Class_AddVectorCallMethod_M(PyContext ctx, PyStrRefOrError name, PyApi_VectorCall_FuncPtr func);

PyRefOrError PyApi_Class_New(PyContext ctx, PyClassRef self);

PyRefOrError PyApi_Class_New_M(PyContext ctx, PyClassRefOrError self);

int PyApi_IsAClass(PyRef ref);
PyClassRef PyApi_Class_UnsafeCast(PyRef ref);
PyClassRefOrError PyApi_Class_DownCast(PyRef ref);
PyRef PyApi_Class_UpCast(PyClassRef ref);

int PyApi_IsNone(PyContext ctx, PyRef obj);

int PyApi_IsNone_M(PyContext ctx, PyRefOrError obj);

PyRef PyApi_None(PyContext ctx);

int PyApi_IsTrue(PyContext ctx, PyRef obj);

int PyApi_IsTrue_M(PyContext ctx, PyRefOrError obj);

PyRef PyApi_True(PyContext ctx);

int PyApi_IsFalse(PyContext ctx, PyRef obj);

int PyApi_IsFalse_M(PyContext ctx, PyRefOrError obj);

PyRef PyApi_False(PyContext ctx);

PyClassRef PyApi_TimeoutError(PyContext ctx);

PyClassRef PyApi_BaseException(PyContext ctx);


/* Exception */
PyExceptionRefOrError PyApi_Exception_FromString(PyContext ctx, PyClassRef cls, const UtfString message);

PyExceptionRefOrError PyApi_Exception_FromValue(PyContext ctx, PyClassRef cls, PyRef message);

int PyApi_Exception_Fatal(PyContext ctx, const UtfString message);

PyExceptionRefOrError PyApi_Exception_FromErrnoWithFilename(PyContext ctx, PyClassRef cls, const UtfString filename);

PyExceptionRefOrError PyApi_Exception_RaiseFromString(PyContext ctx, PyClassRef cls, const UtfString message);

PyExceptionRefOrError PyApi_Exception_RaiseFromValue(PyContext ctx, PyClassRef cls, PyRef message);

int PyApi_IsAnException(PyRef ref);
PyExceptionRef PyApi_Exception_UnsafeCast(PyRef ref);
PyExceptionRefOrError PyApi_Exception_DownCast(PyRef ref);
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
int PyApi_Bytes_GetItem(PyContext ctx, PyBytesRef self, uintptr_t index);

int PyApi_Bytes_GetItem_M(PyContext ctx, PyBytesRefOrError self, uintptr_t index);

PyBytesRefOrError PyApi_Bytes_FromArray(PyContext ctx, const char * data, uintptr_t length);

int PyApi_Bytes_GetSize(PyContext ctx, PyBytesRef self);

int PyApi_Bytes_GetSize_M(PyContext ctx, PyBytesRefOrError self);

int PyApi_IsABytes(PyRef ref);
PyBytesRef PyApi_Bytes_UnsafeCast(PyRef ref);
PyBytesRefOrError PyApi_Bytes_DownCast(PyRef ref);
PyRef PyApi_Bytes_UpCast(PyBytesRef ref);


/* StrBuilder */
PyStrBuilderRefOrError PyApi_StrBuilder_New(PyContext ctx, uintptr_t capacity);

int PyApi_StrBuilder_AppendStr(PyContext ctx, PyRef Self, PyStrRef s);

int PyApi_StrBuilder_AppendStr_M(PyContext ctx, PyRefOrError Self, PyStrRef s);

int PyApi_StrBuilder_AppendUtf8String(PyContext ctx, PyRef Self, const UtfString s);

int PyApi_StrBuilder_AppendUtf8String_M(PyContext ctx, PyRefOrError Self, const UtfString s);

PyStrRefOrError PyApi_StrBuilder_ToStr(PyContext ctx, PyRef Self);

PyStrRefOrError PyApi_StrBuilder_ToStr_M(PyContext ctx, PyRefOrError Self);

int PyApi_IsAStrBuilder(PyRef ref);
PyStrBuilderRef PyApi_StrBuilder_UnsafeCast(PyRef ref);
PyStrBuilderRefOrError PyApi_StrBuilder_DownCast(PyRef ref);
PyRef PyApi_StrBuilder_UpCast(PyStrBuilderRef ref);


/* TupleBuilder */
PyTupleBuilderRefOrError PyApi_TupleBuilder_New(PyContext ctx, uintptr_t capacity);

int PyApi_TupleBuilder_Add(PyContext ctx, PyRef Self, PyStrRef s);

int PyApi_TupleBuilder_Add_M(PyContext ctx, PyRefOrError Self, PyStrRef s);

PyStrRefOrError PyApi_TupleBuilder_ToTuple(PyContext ctx, PyRef Self);

PyStrRefOrError PyApi_TupleBuilder_ToTuple_M(PyContext ctx, PyRefOrError Self);

int PyApi_IsATupleBuilder(PyRef ref);
PyTupleBuilderRef PyApi_TupleBuilder_UnsafeCast(PyRef ref);
PyTupleBuilderRefOrError PyApi_TupleBuilder_DownCast(PyRef ref);
PyRef PyApi_TupleBuilder_UpCast(PyTupleBuilderRef ref);


/* Object */
PyRefOrError PyApi_Object_GetItem(PyContext ctx, PyRef obj, PyRef key);

PyRefOrError PyApi_Object_GetItem_M(PyContext ctx, PyRefOrError obj, PyRef key);

PyRefOrError PyApi_Object_GetItem_i(PyContext ctx, PyRef obj, intptr_t key);

PyRefOrError PyApi_Object_GetItem_i_M(PyContext ctx, PyRefOrError obj, intptr_t key);

PyRefOrError PyApi_Object_GetItem_s(PyContext ctx, PyRef obj, const UtfString key);

PyRefOrError PyApi_Object_GetItem_s_M(PyContext ctx, PyRefOrError obj, const UtfString key);

int PyApi_Object_SetItem(PyContext ctx, PyRef obj, PyRef key, PyRef value);

int PyApi_Object_SetItem_M(PyContext ctx, PyRefOrError obj, PyRef key, PyRef value);

int PyApi_Object_SetItem_i(PyContext ctx, PyRef obj, intptr_t key, PyRef value);

int PyApi_Object_SetItem_i_M(PyContext ctx, PyRefOrError obj, intptr_t key, PyRef value);

int PyApi_Object_SetItem_s(PyContext ctx, PyRef obj, const UtfString key, PyRef value);

int PyApi_Object_SetItem_s_M(PyContext ctx, PyRefOrError obj, const UtfString key, PyRef value);

PyRefOrError PyApi_Object_GetAttr(PyContext ctx, PyRef obj, PyRef attr);

PyRefOrError PyApi_Object_GetAttr_M(PyContext ctx, PyRefOrError obj, PyRef attr);

PyRefOrError PyApi_Object_GetAttr_s(PyContext ctx, PyRef obj, const UtfString attr);

PyRefOrError PyApi_Object_GetAttr_s_M(PyContext ctx, PyRefOrError obj, const UtfString attr);

int PyApi_Object_HasAttr(PyContext ctx, PyRef obj, PyRef attr);

int PyApi_Object_HasAttr_M(PyContext ctx, PyRefOrError obj, PyRef attr);

int PyApi_Object_HasAttr_s(PyContext ctx, PyRef obj, const UtfString attr);

int PyApi_Object_HasAttr_s_M(PyContext ctx, PyRefOrError obj, const UtfString attr);

int PyApi_Object_SetAttr(PyContext ctx, PyRef obj, PyRef attr, PyRef value);

int PyApi_Object_SetAttr_M(PyContext ctx, PyRefOrError obj, PyRef attr, PyRef value);

int PyApi_Object_SetAttr_s(PyContext ctx, PyRef obj, const UtfString attr, PyRef value);

int PyApi_Object_SetAttr_s_M(PyContext ctx, PyRefOrError obj, const UtfString attr, PyRef value);

int PyApi_Object_Contains(PyContext ctx, PyRef container, PyRef key);

int PyApi_Object_Contains_M(PyContext ctx, PyRefOrError container, PyRef key);

PyClassRef PyApi_Object_Type(PyContext ctx, PyRef obj);

PyClassRef PyApi_Object_Type_M(PyContext ctx, PyRefOrError obj);

int PyApi_Object_TypeCheck(PyContext ctx, PyRef obj, PyClassRef cls);

int PyApi_Object_TypeCheck_M(PyContext ctx, PyRefOrError obj, PyClassRef cls);

PyStrRefOrError PyApi_Object_Repr(PyContext ctx, PyRef obj);

PyStrRefOrError PyApi_Object_Repr_M(PyContext ctx, PyRefOrError obj);

PyStrRefOrError PyApi_Object_Str(PyContext ctx, PyRef obj);

PyStrRefOrError PyApi_Object_Str_M(PyContext ctx, PyRefOrError obj);

int PyApi_Object_Hash(PyContext ctx, PyRef obj);

int PyApi_Object_Hash_M(PyContext ctx, PyRefOrError obj);

PyRefOrError PyApi_Object_CallMethod(PyContext ctx, PyRef attr, PyRef args[], intptr_t nargsf);

PyRefOrError PyApi_Object_CallMethod_M(PyContext ctx, PyRefOrError attr, PyRef args[], intptr_t nargsf);

int PyApi_Object_Compare(PyContext ctx, uint8_t op, PyRef left, PyRef right);

int PyApi_Object_IsIter(PyContext ctx, PyRef obj);

int PyApi_Object_IsIter_M(PyContext ctx, PyRefOrError obj);

int PyApi_Object_IsAIter(PyContext ctx, PyRef obj);

int PyApi_Object_IsAIter_M(PyContext ctx, PyRefOrError obj);


/* Dict */
PyRefOrError PyApi_Dict_Get(PyContext ctx, PyDictRef self, PyRef key, PyRef default);

PyRefOrError PyApi_Dict_Get_M(PyContext ctx, PyDictRefOrError self, PyRef key, PyRef default);

PyRefOrError PyApi_Dict_GetItem(PyContext ctx, PyDictRef self, PyRef key);

PyRefOrError PyApi_Dict_GetItem_M(PyContext ctx, PyDictRefOrError self, PyRef key);

PyDictRefOrError PyApi_Dict_New(PyContext ctx);

int PyApi_IsADict(PyRef ref);
PyDictRef PyApi_Dict_UnsafeCast(PyRef ref);
PyDictRefOrError PyApi_Dict_DownCast(PyRef ref);
PyRef PyApi_Dict_UpCast(PyDictRef ref);


/* Int */
PyIntRefOrError PyApi_Int_FromInt32(PyContext ctx, int32_t val);

PyIntRefOrError PyApi_Int_FromUInt32(PyContext ctx, int32_t val);

PyIntRefOrError PyApi_Int_FromInt64(PyContext ctx, int32_t val);

PyIntRefOrError PyApi_Int_FromUInt64(PyContext ctx, int32_t val);

int PyApi_Int_ToInt32(PyContext ctx, PyIntRef self);

int PyApi_Int_ToInt32_M(PyContext ctx, PyIntRefOrError self);

int PyApi_Int_ToInt64(PyContext ctx, PyIntRef self);

int PyApi_Int_ToInt64_M(PyContext ctx, PyIntRefOrError self);

int PyApi_IsAnInt(PyRef ref);
PyIntRef PyApi_Int_UnsafeCast(PyRef ref);
PyIntRefOrError PyApi_Int_DownCast(PyRef ref);
PyRef PyApi_Int_UpCast(PyIntRef ref);


/* List */
PyListRefOrError PyApi_List_New(PyContext ctx);

int PyApi_List_Append(PyContext ctx, PyListRef self, PyRef item);

int PyApi_List_Append_M(PyContext ctx, PyListRefOrError self, PyRef item);

PyRefOrError PyApi_List_GetItem(PyContext ctx, PyListRef self, uintptr_t index);

PyRefOrError PyApi_List_GetItem_M(PyContext ctx, PyListRefOrError self, uintptr_t index);

int PyApi_List_GetSize(PyContext ctx, PyListRef self);

int PyApi_List_GetSize_M(PyContext ctx, PyListRefOrError self);

PyRefOrError PyApi_List_Pop(PyContext ctx, PyListRef self);

PyRefOrError PyApi_List_Pop_M(PyContext ctx, PyListRefOrError self);

int PyApi_IsAList(PyRef ref);
PyListRef PyApi_List_UnsafeCast(PyRef ref);
PyListRefOrError PyApi_List_DownCast(PyRef ref);
PyRef PyApi_List_UpCast(PyListRef ref);


/* Operators */
PyRefOrError PyApi_Operators_UnaryOp(PyContext ctx, uint8_t op, PyRef argument);

PyRefOrError PyApi_Operators_BinaryOp(PyContext ctx, uint8_t op, PyRef left, PyRef right);

PyRefOrError PyApi_Operators_Compare(PyContext ctx, PyRef left, PyRef right, uint8_t op);

PyRefOrError PyApi_Operators_Compare_M(PyContext ctx, PyRefOrError left, PyRef right, uint8_t op);

int PyApi_Operators_CompareBool(PyContext ctx, PyRef left, PyRef right, uint8_t op);

int PyApi_Operators_CompareBool_M(PyContext ctx, PyRefOrError left, PyRef right, uint8_t op);


/* Call */
int PyApi_Call_IsCallable(PyContext ctx, PyRef obj);

int PyApi_Call_IsCallable_M(PyContext ctx, PyRefOrError obj);

PyRefOrError PyApi_Call_TupleDict(PyContext ctx, PyRef callable, PyTupleRef args, PyDictRef kwargs);

PyRefOrError PyApi_Call_TupleDict_M(PyContext ctx, PyRefOrError callable, PyTupleRef args, PyDictRef kwargs);

PyRefOrError PyApi_Call_Vector(PyContext ctx, PyRef callable, PyRef args[], intptr_t nargsf, PyTupleRef kwnames);

PyRefOrError PyApi_Call_Vector_M(PyContext ctx, PyRefOrError callable, PyRef args[], intptr_t nargsf, PyTupleRef kwnames);


/* Iter */
PyRefOrError PyApi_Iter_Next(PyContext ctx, PyRef obj);

PyRefOrError PyApi_Iter_Next_M(PyContext ctx, PyRefOrError obj);

PyRefOrError PyApi_Iter_Send(PyContext ctx, PyRef obj);

PyRefOrError PyApi_Iter_Send_M(PyContext ctx, PyRefOrError obj);


/* Code */
int PyApi_IsACode(PyRef ref);
PyCodeRef PyApi_Code_UnsafeCast(PyRef ref);
PyCodeRefOrError PyApi_Code_DownCast(PyRef ref);
PyRef PyApi_Code_UpCast(PyCodeRef ref);


/* FrameStack */
PyRefOrError PyApi_FrameStack_GetLocal(PyContext ctx, uintptr_t depth, uintptr_t index);

PyRefOrError PyApi_FrameStack_GetLocalByName(PyContext ctx, uintptr_t depth, PyStrRef name);

PyRefOrError PyApi_FrameStack_GetLocalByCName(PyContext ctx, uintptr_t depth, const UtfString name);

PyCodeRefOrError PyApi_FrameStack_GetCode(PyContext ctx, uintptr_t depth);

