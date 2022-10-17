/* This file is generated from api.py by gen/__main__.py */

PyRef PyRef_INVALID;
PyExceptionRef PyRef_NO_EXCEPTION;


/* Tuple */
PyTupleRef PyApi_Tuple_Empty(PyContext ctx);

PyTupleRef PyApi_Tuple_FromNonEmptyArray(PyContext ctx, PyRef array[], uintptr_t length, PyExceptionRef *exc);

PyTupleRef PyApi_Tuple_FromArray(PyContext ctx, PyRef array[], uintptr_t length, PyExceptionRef *exc);

PyRef PyApi_Tuple_GetItem(PyContext ctx, PyTupleRef self, uintptr_t index, PyExceptionRef *exc);

int PyApi_Tuple_GetSize(PyContext ctx, PyTupleRef self, uintptr_t *result);

int PyApi_IsATuple(PyRef ref);
PyTupleRef PyApi_Tuple_UnsafeCast(PyRef ref);
PyRef PyApi_Tuple_UpCast(PyTupleRef ref);

typedef int (*PyApi_BinaryOperator_FuncPtr)(PyContext ctx, PyRef left, PyRef right, PyRef *result);

typedef int (*PyApi_VectorCall_FuncPtr)(PyContext ctx, PyRef callable, PyRef args[], intptr_t nargsf, PyTupleRef kwnames, PyRef *result);


/* Str */
PyStrRef PyApi_Str_FromUtfString(PyContext ctx, const UtfString data, uintptr_t length, PyExceptionRef *exc);

PyStrRef PyApi_Str_Join(PyContext ctx, PyStrRef self, PyStrRef array[], PyExceptionRef *exc);

PyRef PyApi_Str_GetItem(PyContext ctx, PyStrRef self, uintptr_t index, PyExceptionRef *exc);

int PyApi_IsAStr(PyRef ref);
PyStrRef PyApi_Str_UnsafeCast(PyRef ref);
PyRef PyApi_Str_UpCast(PyStrRef ref);


/* Class */
int PyApi_Class_AddBinaryOperator(PyContext ctx, uint8_t op, PyApi_BinaryOperator_FuncPtr func, PyExceptionRef *exc);

int PyApi_Class_AddVectorCallMethod(PyContext ctx, PyStrRef name, PyApi_VectorCall_FuncPtr func, PyExceptionRef *exc);

int PyApi_IsAClass(PyRef ref);
PyClassRef PyApi_Class_UnsafeCast(PyRef ref);
PyRef PyApi_Class_UpCast(PyClassRef ref);

int PyApi_IsNone(PyContext ctx, PyRef obj);

PyRef PyApi_None(PyContext ctx);

int PyApi_IsTrue(PyContext ctx, PyRef obj);

PyRef PyApi_True(PyContext ctx);

int PyApi_IsFalse(PyContext ctx, PyRef obj);

PyRef PyApi_False(PyContext ctx);


/* Object */
PyRef PyApi_Object_GetItem(PyContext ctx, PyRef obj, PyRef key, PyExceptionRef *exc);

PyRef PyApi_Object_GetItem_i(PyContext ctx, PyRef obj, intptr_t key, PyExceptionRef *exc);

PyRef PyApi_Object_GetItem_s(PyContext ctx, PyRef obj, const UtfString key, PyExceptionRef *exc);

int PyApi_Object_SetItem(PyContext ctx, PyRef obj, PyRef key, PyRef value, PyExceptionRef *exc);

int PyApi_Object_SetItem_i(PyContext ctx, PyRef obj, intptr_t key, PyRef value, PyExceptionRef *exc);

int PyApi_Object_SetItem_s(PyContext ctx, PyRef obj, const UtfString key, PyRef value, PyExceptionRef *exc);

PyRef PyApi_Object_GetAttr(PyContext ctx, PyRef obj, PyRef attr, PyExceptionRef *exc);

PyRef PyApi_Object_GetAttr_s(PyContext ctx, PyRef obj, const UtfString attr, PyExceptionRef *exc);

int PyApi_Object_HasAttr(PyContext ctx, PyRef obj, PyRef attr, PyExceptionRef *exc);

int PyApi_Object_HasAttr_s(PyContext ctx, PyRef obj, const UtfString attr, PyExceptionRef *exc);

int PyApi_Object_SetAttr(PyContext ctx, PyRef obj, PyRef attr, PyRef value, PyExceptionRef *exc);

int PyApi_Object_SetAttr_s(PyContext ctx, PyRef obj, const UtfString attr, PyRef value, PyExceptionRef *exc);

int PyApi_Object_Contains(PyContext ctx, PyRef container, PyRef key, PyExceptionRef *exc);

PyClassRef PyApi_Object_Type(PyContext ctx, PyRef obj);

int PyApi_Object_TypeCheck(PyContext ctx, PyRef obj, PyClassRef cls);

PyStrRef PyApi_Object_Repr(PyContext ctx, PyRef obj, PyExceptionRef *exc);

PyStrRef PyApi_Object_Str(PyContext ctx, PyRef obj, PyExceptionRef *exc);

int PyApi_Object_Hash(PyContext ctx, PyRef obj, intptr_t *result, PyExceptionRef *exc);

PyRef PyApi_Object_CallMethod(PyContext ctx, PyRef attr, PyRef args[], intptr_t nargsf, PyExceptionRef *exc);


/* Dict */
PyRef PyApi_Dict_Get(PyContext ctx, PyDictRef self, PyRef key, PyRef default, PyExceptionRef *exc);

PyRef PyApi_Dict_GetItem(PyContext ctx, PyDictRef self, PyRef key, PyExceptionRef *exc);

PyDictRef PyApi_Dict_New(PyContext ctx, PyExceptionRef *exc);

int PyApi_IsADict(PyRef ref);
PyDictRef PyApi_Dict_UnsafeCast(PyRef ref);
PyRef PyApi_Dict_UpCast(PyDictRef ref);


/* List */
PyListRef PyApi_List_New(PyContext ctx, PyExceptionRef *exc);

int PyApi_List_Append(PyContext ctx, PyListRef self, PyRef item, PyExceptionRef *exc);

PyRef PyApi_List_GetItem(PyContext ctx, PyListRef self, uintptr_t index, PyExceptionRef *exc);

int PyApi_List_GetSize(PyContext ctx, PyListRef self, uintptr_t *result);

int PyApi_IsAList(PyRef ref);
PyListRef PyApi_List_UnsafeCast(PyRef ref);
PyRef PyApi_List_UpCast(PyListRef ref);


/* Operators */
PyRef PyApi_Operators_BinaryOp(PyContext ctx, uint8_t op, PyRef left, PyRef right, PyExceptionRef *exc);

PyRef PyApi_Operators_Compare(PyContext ctx, PyRef left, PyRef right, uint8_t op, PyExceptionRef *exc);

int PyApi_Operators_CompareBool(PyContext ctx, PyRef left, PyRef right, uint8_t op, PyExceptionRef *exc);


/* Exception */
PyExceptionRef PyApi_Exception_FromString(PyContext ctx, PyClassRef cls, const UtfString message, PyExceptionRef *exc);

PyExceptionRef PyApi_Exception_FromValue(PyContext ctx, PyClassRef cls, PyRef message, PyExceptionRef *exc);

int PyApi_IsAnException(PyRef ref);
PyExceptionRef PyApi_Exception_UnsafeCast(PyRef ref);
PyRef PyApi_Exception_UpCast(PyExceptionRef ref);


/* Call */
int PyApi_Call_IsCallable(PyContext ctx, PyRef obj, PyExceptionRef *exc);

PyRef PyApi_Call_TupleDict(PyContext ctx, PyRef callable, PyTupleRef args, PyDictRef kwargs, PyExceptionRef *exc);

PyRef PyApi_Call_Vector(PyContext ctx, PyRef callable, PyRef args[], intptr_t nargsf, PyTupleRef kwnames, PyExceptionRef *exc);


/* Bytes */
int PyApi_Bytes_GetItem(PyContext ctx, PyBytesRef self, uintptr_t index, PyExceptionRef *exc);

PyBytesRef PyApi_Bytes_FromArray(PyContext ctx, const char * data, uintptr_t length, PyExceptionRef *exc);

int PyApi_Bytes_GetSize(PyContext ctx, PyBytesRef self, uintptr_t *result, PyExceptionRef *exc);

int PyApi_IsABytes(PyRef ref);
PyBytesRef PyApi_Bytes_UnsafeCast(PyRef ref);
PyRef PyApi_Bytes_UpCast(PyBytesRef ref);

