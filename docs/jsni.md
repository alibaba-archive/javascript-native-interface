
### JSNIGetVersion
`int JSNIGetVersion(JSNIEnv* env)`

**SUMMARY**

Returns the version of the JSNI. 


**PARAMETERS**

None.


**RETURNS**

Returns the version of the JSNI. 

### JSNIRegisterMethod
`bool JSNIRegisterMethod(JSNIEnv* env, const JSValueRef recv, const char* name, JSNICallback callback)`

**SUMMARY**

Registers a native callback function. 


**PARAMETERS**

recv: the method receiver. It is passed through JSNIInit to receive the

registered JS function associated with the callback.

name: a function name.

callback: a native callback function to be registered.


**RETURNS**

Returns true on success. 

### JSNIGetArgsLengthOfCallback
`int JSNIGetArgsLengthOfCallback(JSNIEnv* env, JSNICallbackInfo info)`

**SUMMARY**

Returns the number of arguments for the callback. 


**PARAMETERS**

info: the callback info.


**RETURNS**

Returns the number of arguments. 

### JSNIGetArgOfCallback
`JSValueRef JSNIGetArgOfCallback(JSNIEnv* env, JSNICallbackInfo info, int id)`

**SUMMARY**

Returns the argument for the callback. 


**PARAMETERS**

info: the callback info.

id: the index of arguments.


**RETURNS**

Returns the argument. 

### JSNIGetThisOfCallback
`JSValueRef JSNIGetThisOfCallback(JSNIEnv* env, JSNICallbackInfo info)`

**SUMMARY**

Returns "this" JavaScript object of the JavaScript function 
which current callback associated with. 


**PARAMETERS**

info: the callback info.


**RETURNS**

Returns "this" JavaScript object.. 

### JSNIGetDataOfCallback
`void* JSNIGetDataOfCallback(JSNIEnv* env, JSNICallbackInfo info)`

**SUMMARY**

Get the raw data which is passed to this callback. 


**PARAMETERS**

info: the callback info.


**RETURNS**

Returns the data. 

### JSNISetReturnValue
`void JSNISetReturnValue(JSNIEnv* env, JSNICallbackInfo info, JSValueRef val)`

**SUMMARY**

Sets the JavaScript return value for the callback. 


**PARAMETERS**

info: the callback info.

val: the JavaScript value to return to JavaScript.


**RETURNS**

None. 

### JSNIIsUndefined
`bool JSNIIsUndefined(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Tests whether the JavaScript value is undefined. 


**PARAMETERS**

val: a JavaScript value.


**RETURNS**

Returns true if the value is undefined. 

### JSNINewUndefined
`JSValueRef JSNINewUndefined(JSNIEnv* env)`

**SUMMARY**

Constructs a new Undefined JavaScript value. 


**PARAMETERS**

None.


**RETURNS**

Returns an Undefined JavaScript value. 

### JSNIIsNull
`bool JSNIIsNull(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Tests whether the JavaScript value is Null. 


**PARAMETERS**

val: a JavaScript value.


**RETURNS**

Returns true if the value is Null. 

### JSNINewNull
`JSValueRef JSNINewNull(JSNIEnv* env)`

**SUMMARY**

Constructs a new Null JavaScript value. 


**PARAMETERS**

None.


**RETURNS**

Returns a Null JavaScript value. 

### JSNIIsBoolean
`bool JSNIIsBoolean(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Tests whether the JavaScript value is Boolean. 


**PARAMETERS**

val: a JavaScript value.


**RETURNS**

Returns true if the value is Boolean. 

### JSNIToCBool
`bool JSNIToCBool(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Converts the JavaScript value to C bool. 


**PARAMETERS**

val: a JavaScript value.


**RETURNS**

Returns the C bool value. 

### JSNINewBoolean
`JSValueRef JSNINewBoolean(JSNIEnv* env, bool val)`

**SUMMARY**

Constructs a new Boolean JavaScript value. 


**PARAMETERS**

val: a bool value.


**RETURNS**

Returns a Boolean JavaScript value. 

### JSNIIsNumber
`bool JSNIIsNumber(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Tests whether the JavaScript value is Number. 


**PARAMETERS**

val: a JavaScript value.


**RETURNS**

Returns true if the value is Number. 

### JSNINewNumber
`JSValueRef JSNINewNumber(JSNIEnv* env, double val)`

**SUMMARY**

Constructs a new Number JavaScript value. 


**PARAMETERS**

val: a double value.


**RETURNS**

Returns a Number JavaScript value. 

### JSNIToCDouble
`double JSNIToCDouble(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Converts the JavaScript value to C double. 


**PARAMETERS**

val: a JavaScript value.


**RETURNS**

Returns the C double value. 

### JSNIIsSymbol
`bool JSNIIsSymbol(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Tests whether the JavaScript value is Symbol. 


**PARAMETERS**

val: a JavaScript value.


**RETURNS**

Returns true if the value is Symbol. 

### JSNINewSymbol
`JSValueRef JSNINewSymbol(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Constructs a new Symbol JavaScript value 


**PARAMETERS**

val: the description of the symbol.


**RETURNS**

Returns a Symbol JavaScript value. 

### JSNIIsString
`bool JSNIIsString(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Tests whether the JavaScript value is String. 


**PARAMETERS**

val: a JavaScript value.


**RETURNS**

Returns true if the value is String. 

### JSNINewStringFromUtf8
`JSValueRef JSNINewStringFromUtf8(JSNIEnv* env, const char* src, size_t length)`

**SUMMARY**

Constructs a new String value from an array of characters 
in UTF-8 encoding. 


**PARAMETERS**

src: the pointer to a UTF-8 string.


**RETURNS**

Returns a String value, or NULL if the string can not be constructed. 

### JSNIGetStringUtf8Length
`size_t JSNIGetStringUtf8Length(JSNIEnv* env, JSValueRef string)`

**SUMMARY**

Returns the length in bytes of the UTF-8 representation of a string. 


**PARAMETERS**

string: a JavaScript string value.


**RETURNS**

Returns the UTF-8 length of the string. 

### JSNIGetStringUtf8Chars
`size_t JSNIGetStringUtf8Chars(JSNIEnv* env, JSValueRef string, char* copy, size_t length)`

**SUMMARY**

Copyies a JavaScript string into a UTF-8 encoding string buffer. 


**PARAMETERS**

string: a JavaScript string value.

copy: the buffer copied to.

length: the length to copy.


**RETURNS**

Returns the size of copied. 

### JSNIIsObject
`bool JSNIIsObject(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Tests whether a JavaScript value is a JavaScript object. 


**PARAMETERS**

val: a JavaScript value.


**RETURNS**

Returns true if val is a JavaScript object. 

### JSNIIsEmpty
`bool JSNIIsEmpty(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Tests whether a JavaScript value is empty. 


**PARAMETERS**

val: a JavaScript value.


**RETURNS**

Returns true if val is empty. 

### JSNINewObject
`JSValueRef JSNINewObject(JSNIEnv* env)`

**SUMMARY**

Constructs a JavaScript object. 


**PARAMETERS**

None.


**RETURNS**

Returns a JavaScript object. 

### JSNIHasProperty
`bool JSNIHasProperty(JSNIEnv* env, JSValueRef object, const char* name)`

**SUMMARY**

Tests whether a JavaScript object has a property named name. 


**PARAMETERS**

object: a JavaScript object.

name: a property name.


**RETURNS**

Returns true if object has property named name. 

### JSNIGetProperty
`JSValueRef JSNIGetProperty(JSNIEnv* env, JSValueRef object, const char* name)`

**SUMMARY**

Returns the property of the JavaScript object. 


**PARAMETERS**

object: a JavaScript object.

name: a property name.


**RETURNS**

Returns the property of the JavaScript object. 

### JSNISetProperty
`bool JSNISetProperty(JSNIEnv* env, JSValueRef object, const char* name, JSValueRef property)`

**SUMMARY**

Sets a property of a JavaScript object. 


**PARAMETERS**

object: a JavaScript object.

name: a property name.

property: a JavaScript value.


**RETURNS**

Returns true if the operation succeeds. 

### JSNIDefineProperty
`bool JSNIDefineProperty(JSNIEnv* env, JSValueRef object, const char* name, const JSNIPropertyDescriptor descriptor)`

**SUMMARY**

Defines a new property directly on an object, or modifies 
an existing property on an object. 


**PARAMETERS**

object: the object on which to define the property.

name: the name of the property to be defined or modified.

descriptor: the descriptor for the property being defined or modified.


**RETURNS**

Returns true on success. 

### JSNIDeleteProperty
`bool JSNIDeleteProperty(JSNIEnv* env, JSValueRef object, const char* name)`

**SUMMARY**

Deletes the property of a JavaScript object. 


**PARAMETERS**

object: a JavaScript object.

name: a property name.


**RETURNS**

Returns true if the operation succeeds. 

### JSNIGetPrototype
`JSValueRef JSNIGetPrototype(JSNIEnv* env, JSValueRef object)`

**SUMMARY**

Returns a prototype of a JavaScript object. 


**PARAMETERS**

object: a JavaScript object.


**RETURNS**

Returns a JavaScript value. 

### JSNINewObjectWithInternalField
`JSValueRef JSNINewObjectWithInternalField(JSNIEnv* env, int count)`

**SUMMARY**

Constructs a JavaScript object with internal field. 
Internal field is a raw C pointer which can not be 
get in JavaScript. 


**PARAMETERS**

count: a number of internal fields.


**RETURNS**

Returns a JavaScript object. 

### JSNIInternalFieldCount
`int JSNIInternalFieldCount(JSNIEnv* env, JSValueRef object)`

**SUMMARY**

Gets the number of the internal field fo a JavaScript object. 


**PARAMETERS**

object: a JavaScript object.


**RETURNS**

Returns the number of the internal internal field. 

### JSNISetInternalField
`void JSNISetInternalField(JSNIEnv* env, JSValueRef object, int index, void* field)`

**SUMMARY**

Sets an internal field of a JavaScript object. 


**PARAMETERS**

object: a JavaScript object.

index: index of an internal field.

field: an internal field. This is a raw C pointer,

and it will not be freed when object is Garbage Collected.


**RETURNS**

None. 

### JSNIGetInternalField
`void* JSNIGetInternalField(JSNIEnv* env, JSValueRef object, int index)`

**SUMMARY**

Gets an internal field of a JavaScript object. 


**PARAMETERS**

object: a JavaScript object.

index: index of an internal field.


**RETURNS**

an internal field. 

### JSNIIsFunction
`bool JSNIIsFunction(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Tests whether a JavaScript value is Function. 


**PARAMETERS**

val: a JavaScript value.


**RETURNS**

Returns true if val is Function. 

### JSNINewFunction
`JSValueRef JSNINewFunction(JSNIEnv* env, JSNICallback callback)`

**SUMMARY**

Constructs a JavaScript function with callback. 


**PARAMETERS**

callback: a native callback function.


**RETURNS**

Returns a JavaScript function. 

### JSNICallFunction
`JSValueRef JSNICallFunction(JSNIEnv* env, JSValueRef func, JSValueRef recv, int argc, JSValueRef* argv)`

**SUMMARY**

Calls a JavaScript function. 


**PARAMETERS**

func: a JavaScript funciton.

recv: the receiver the func belongs to.

argc: the arguments number.

argv: a pointer to an array of JavaScript value.


**RETURNS**

Returns the JavaScript value returned from calling func. 

### JSNIIsArray
`bool JSNIIsArray(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Tests whether a JavaScript value is Array. 


**PARAMETERS**

val: a JavaScript value.


**RETURNS**

Returns true if val is Array. 

### JSNIGetArrayLength
`size_t JSNIGetArrayLength(JSNIEnv* env, JSValueRef array)`

**SUMMARY**

Returns the number of elements in the array. 


**PARAMETERS**

array: a JavaScript array.


**RETURNS**

Returns the length of the array. 

### JSNINewArray
`JSValueRef JSNINewArray(JSNIEnv* env, size_t initial_length)`

**SUMMARY**

Constructs a JavaScript array with initial length: initial_length. 


**PARAMETERS**

initial_length: initial array size.


**RETURNS**

Returns a JavaScript array object, or NULL if the operation fails. 

### JSNIGetArrayElement
`JSValueRef JSNIGetArrayElement(JSNIEnv* env, JSValueRef array, size_t index)`

**SUMMARY**

Returns an element of a JavaScript array. 


**PARAMETERS**

array: a JavaScript array.

index: array index.


**RETURNS**

Returns a JavaScript value. 

### JSNISetArrayElement
`void JSNISetArrayElement(JSNIEnv* env, JSValueRef array, size_t index, JSValueRef value)`

**SUMMARY**

Sets an element of a JavaScript array. 


**PARAMETERS**

array: a JavaScript array.

index: a array index.

value: a new value.


**RETURNS**

None. 

### JSNIIsTypedArray
`bool JSNIIsTypedArray(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Tests whether a JavaScript value is TypedArray. 


**PARAMETERS**

val: a JavaScript value.


**RETURNS**

Returns true if val is TypedArray. 

### JSNINewTypedArray
`JSValueRef JSNINewTypedArray(JSNIEnv*, JsTypedArrayType type, void* data, size_t length)`

**SUMMARY**

Constructs a JavaScript TypedArray object. 


**PARAMETERS**

type: the type of the array.

data: the pointer to the data buffer of the array.

length: the length of the array.


**RETURNS**

Returns a JavaScript TypedArray object. 

### JSNIGetTypedArrayType
`JsTypedArrayType JSNIGetTypedArrayType(JSNIEnv* env, JSValueRef typed_array)`

**SUMMARY**

Returns the type of the JavaScript TypedArray value. 


**PARAMETERS**

typed_array: a JavaScript TypedArray value.


**RETURNS**

Returns the type of the JavaScript TypedArray value. 

### JSNIGetTypedArrayData
`void* JSNIGetTypedArrayData(JSNIEnv* env, JSValueRef typed_array)`

**SUMMARY**

Returns the pointer to the buffer of TypedArray data. 


**PARAMETERS**

typed_array: a JavaScript TypedArray value.


**RETURNS**

Returns the pointer to the buffer of TypedArray data. 

### JSNIGetTypedArrayLength
`size_t JSNIGetTypedArrayLength(JSNIEnv* env, JSValueRef typed_array)`

**SUMMARY**

Returns the number of elements in the TypedArray value. 


**PARAMETERS**

typed_array: a JavaScript TypedArray value.


**RETURNS**

Returns the length of the TypedArray value. 

### JSNIPushLocalScope
`void JSNIPushLocalScope(JSNIEnv* env)`

**SUMMARY**

Creates a local reference scope, and then all local references will 
be allocated within this reference scope until the reference scope 
is deleted using PoplocalScope() or another local reference scope 
is created. 


**PARAMETERS**

None.


**RETURNS**

None. 

### JSNIPopLocalScope
`void JSNIPopLocalScope(JSNIEnv* env)`

**SUMMARY**

Pops off the current local reference scope, frees all the local 
references in the local reference scope. 


**PARAMETERS**

None.


**RETURNS**

None. 

### JSNIPushEscapableLocalScope
`void JSNIPushEscapableLocalScope(JSNIEnv* env)`

**SUMMARY**

Creates a local reference scope, and then all local references will 
be allocated within this reference scope until the reference scope 
is deleted using PopEscapableLocalScope() or another local reference scope 
is created. 


**PARAMETERS**

None.


**RETURNS**

None. 

### JSNIPopEscapableLocalScope
`JSValueRef JSNIPopEscapableLocalScope(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Pops off the current local reference scope, frees all the local 
references in the local reference scope, and returns a local reference 
in the previous local scope for the given val JavaScript value. 


**PARAMETERS**

val: a JavaScript value.


**RETURNS**

Returns a JavaScript value. 

### JSNINewGlobalValue
`JSGlobalValueRef JSNINewGlobalValue(JSNIEnv* env, JSValueRef val)`

**SUMMARY**

Creates a new global reference to the JavaScript value referred to by 
the val argument. The global value must be explicitly disposed of by 
calling DeleteGlobalValue(), except that the global value is set 
by calling SetGCCallback(). The global value will be alive 
untile calling DeleteGlobalValue() to dispose it. 


**PARAMETERS**

val: a JavaScript value.


**RETURNS**

Returns a global value. 

### JSNIDeleteGlobalValue
`void JSNIDeleteGlobalValue(JSNIEnv* env, JSGlobalValueRef val)`

**SUMMARY**

Deletes the global reference pointed by val. 


**PARAMETERS**

val: a JSGlobalValueRef value.


**RETURNS**

None. 

### JSNIGetGlobalValue
`JSValueRef JSNIGetGlobalValue(JSNIEnv* env, JSGlobalValueRef val)`

**SUMMARY**

Returns a local JSValueRef value from a JSGlobalValueRef value. 


**PARAMETERS**

val: a JSGlobalValueRef value.


**RETURNS**

Returns a local JSValueRef value. 

### JSNISetGCCallback
`void JSNISetGCCallback(JSNIEnv* env, JSGlobalValueRef val, void* args, JSNIGCCallback callback)`

**SUMMARY**

Sets a callback which will be called 
when the JavaScript value pointed by val is freed. 
The developer can pass an argument to callback by args. 


**PARAMETERS**

val: a JSGlobalValueRef value.

args: a pointer to an argument passed to callback.

callback: a function callback.


**RETURNS**

None. 

### JSNIThrowErrorException
`void JSNIThrowErrorException(JSNIEnv* env, const char* errmsg)`

**SUMMARY**

Constructs an error object with the message specified by errmsg 
and causes that error to be thrown. It throws a JavaScript Exception. 


**PARAMETERS**

errmsg: an error message.


**RETURNS**

None. 

### JSNIThrowTypeErrorException
`void JSNIThrowTypeErrorException(JSNIEnv* env, const char* errmsg)`

**SUMMARY**

Constructs an type error object with the message specified by errmsg 
and causes that type error to be thrown. It throws a JavaScript Exception. 


**PARAMETERS**

errmsg: an error message.


**RETURNS**

None. 

### JSNIThrowRangeErrorException
`void JSNIThrowRangeErrorException(JSNIEnv* env, const char* errmsg)`

**SUMMARY**

Constructs an range error object with the message specified by errmsg 
and causes that type error to be thrown. It throws a JavaScript Exception. 


**PARAMETERS**

errmsg: an error message.


**RETURNS**

None. 

### JSNIGetLastErrorInfo
`JSNIErrorInfo JSNIGetLastErrorInfo(JSNIEnv* env)`

**SUMMARY**

Tests whether there is error occured during pervious JSNI call. After 
calling JSNIGetLastErrorInfo(), if there is error occured, the error 
will be cleared. 


**PARAMETERS**

None.


**RETURNS**

Returns true if there is error occured during previous JSNI call. 

### JSNIHasException
`bool JSNIHasException(JSNIEnv* env)`

**SUMMARY**

Tests whether a JavaScript exception is being thrown. 
It's different with error get from JSNIGetLastErrorInfo. 
Eorror is defined by JSNI, whereas this is a JavaScript exception. 


**PARAMETERS**

None.


**RETURNS**

Returns true if a JavaScript exception is being thrown. 

### JSNIClearException
`void JSNIClearException(JSNIEnv* env)`

**SUMMARY**

Clear a JavaScript exception that is being thrown. If there 
is no exception, this routine has no effect. 


**PARAMETERS**

None.


**RETURNS**

None. 

