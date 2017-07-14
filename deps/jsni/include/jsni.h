// JavaScript Native Interface Release License.
//
// Copyright (c) 2015-2016 Alibaba Group. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Alibaba Group nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef INCLUDE_JSNI_H_
#define INCLUDE_JSNI_H_

// For size_t.
#include <stddef.h>

// JS type.
typedef struct _JSValueRef* JSValueRef;

// JSNI interface extended.
typedef struct _JSNIEnv JSNIEnv;

// GCCallback helper types.
typedef void (*JSNIGCCallback)(JSNIEnv*, void*);

// Callback helper types.
typedef struct _JSNICallbackInfo* JSNICallbackInfo;
typedef void (*JSNICallback)(JSNIEnv*, const JSNICallbackInfo);
typedef struct _JSGlobalValueRef* JSGlobalValueRef;

// Type array.
typedef enum {
  JsArrayTypeNone,
  JsArrayTypeInt8,
  JsArrayTypeUint8,
  /* JsArrayTypeUint8Clamped represents an array
   of 8-bit unsigned integers clamped to 0-255.
  **/
  JsArrayTypeUint8Clamped,
  JsArrayTypeInt16,
  JsArrayTypeUint16,
  JsArrayTypeInt32,
  JsArrayTypeUint32,
  JsArrayTypeFloat32,
  JsArrayTypeFloat64
} JsTypedArrayType;

/* Types
** Define types here.
*/

typedef enum {
  JSNINone       = 0,
  JSNIReadOnly   = 1 << 0,
  JSNIDontEnum   = 1 << 1,
  JSNIDontDelete = 1 << 2
} JSNIPropertyAttributes;

typedef struct {
  JSValueRef value;
  JSNIPropertyAttributes attributes;
} JSNIDataPropertyDescriptor;

typedef struct {
  JSNICallback getter;
  JSNICallback setter;
  JSNIPropertyAttributes attributes;
  void* data;
} JSNIAccessorPropertyDescriptor;

typedef struct {
  JSNIDataPropertyDescriptor* data_attributes;
  JSNIAccessorPropertyDescriptor* accessor_attributes;
  // TODO(jiny) Maybe add void* data?
} JSNIPropertyDescriptor;

typedef enum {
  // No error
  JSNIOK,
  // Generic error
  JSNIERR
} JSNIErrorCode;

typedef struct {
  const char* msg;
  JSNIErrorCode error_code;
} JSNIErrorInfo;


#if defined(__cplusplus)
extern "C" {
#endif
/**
 * JSNI functions.
 */

// \summary:
//    Returns the version of the JSNI.
// \param:
//    None.
// \returns:
//    Returns the version of the JSNI.
int JSNIGetVersion(JSNIEnv* env);

// \summary:
//    Registers a native callback function.
// \param:
//    recv: the method receiver. It is passed through JSNIInit to receive the
//          registered JS function associated with the callback.
//    name: a function name.
//    callback: a native callback function to be registered.
// \returns:
//    Returns true on success.
bool JSNIRegisterMethod(JSNIEnv* env,
                        const JSValueRef recv,
                        const char* name,
                        JSNICallback callback);
// \summary:
//    Returns the number of arguments for the callback.
// \param:
//    info: the callback info.
// \returns:
//    Returns the number of arguments.
int JSNIGetArgsLengthOfCallback(JSNIEnv* env, JSNICallbackInfo info);

// \summary:
//    Returns the argument for the callback.
// \param:
//    info: the callback info.
//    id: the index of arguments.
// \returns:
//    Returns the argument.
JSValueRef JSNIGetArgOfCallback(JSNIEnv* env, JSNICallbackInfo info, int id);

// \summary:
//    Returns "this" JavaScript object of the JavaScript function
//    which current callback associated with.
// \param:
//    info: the callback info.
// \returns:
//    Returns "this" JavaScript object..
JSValueRef JSNIGetThisOfCallback(JSNIEnv* env, JSNICallbackInfo info);

// \summary:
//    Get the raw data which is passed to this callback.
// \param:
//    info: the callback info.
// \returns:
//    Returns the data.
void* JSNIGetDataOfCallback(JSNIEnv* env, JSNICallbackInfo info);

// \summary:
//    Sets the JavaScript return value for the callback.
// \param:
//    info: the callback info.
//    val: the JavaScript value to return to JavaScript.
// \returns:
//    None.
void JSNISetReturnValue(JSNIEnv* env,
                                  JSNICallbackInfo info,
                                  JSValueRef val);

// Primitive Operations

// \summary:
//    Tests whether the JavaScript value is undefined.
// \param:
//    val: a JavaScript value.
// \returns:
//    Returns true if the value is undefined.
bool JSNIIsUndefined(JSNIEnv* env, JSValueRef val);

// \summary:
//    Constructs a new Undefined JavaScript value.
// \param:
//    None.
// \returns:
//    Returns an Undefined JavaScript value.
JSValueRef JSNINewUndefined(JSNIEnv* env);

// \summary:
//    Tests whether the JavaScript value is Null.
// \param:
//    val: a JavaScript value.
// \returns:
//    Returns true if the value is Null.
bool JSNIIsNull(JSNIEnv* env, JSValueRef val);

// \summary:
//    Constructs a new Null JavaScript value.
// \param:
//    None.
// \returns:
//    Returns a Null JavaScript value.
JSValueRef JSNINewNull(JSNIEnv* env);


// \summary:
//    Tests whether the JavaScript value is Boolean.
// \param:
//    val: a JavaScript value.
// \returns:
//    Returns true if the value is Boolean.
bool JSNIIsBoolean(JSNIEnv* env, JSValueRef val);

// \summary:
//    Converts the JavaScript value to C bool.
// \param:
//    val: a JavaScript value.
// \returns:
//    Returns the C bool value.
bool JSNIToCBool(JSNIEnv* env, JSValueRef val);

// \summary:
//    Constructs a new Boolean JavaScript value.
// \param:
//    val: a bool value.
// \returns:
//    Returns a Boolean JavaScript value.
JSValueRef JSNINewBoolean(JSNIEnv* env, bool val);

// \summary:
//    Tests whether the JavaScript value is Number.
// \param:
//    val: a JavaScript value.
// \returns:
//    Returns true if the value is Number.
bool JSNIIsNumber(JSNIEnv* env, JSValueRef val);

// \summary:
//    Constructs a new Number JavaScript value.
// \param:
//    val: a double value.
// \returns:
//    Returns a Number JavaScript value.
JSValueRef JSNINewNumber(JSNIEnv* env, double val);

// \summary:
//    Converts the JavaScript value to C double.
// \param:
//    val: a JavaScript value.
// \returns:
//    Returns the C double value.
double JSNIToCDouble(JSNIEnv* env, JSValueRef val);

// \summary:
//    Tests whether the JavaScript value is Symbol.
// \param:
//    val: a JavaScript value.
// \returns:
//    Returns true if the value is Symbol.
bool JSNIIsSymbol(JSNIEnv* env, JSValueRef val);

// \summary:
//    Constructs a new Symbol JavaScript value
// \param:
//    val: the description of the symbol.
// \returns:
//    Returns a Symbol JavaScript value.
JSValueRef JSNINewSymbol(JSNIEnv* env, JSValueRef val);

// \summary:
//    Tests whether the JavaScript value is String.
// \param:
//    val: a JavaScript value.
// \returns:
//    Returns true if the value is String.
bool JSNIIsString(JSNIEnv* env, JSValueRef val);

// \summary:
//    Constructs a new String value from an array of characters
//    in UTF-8 encoding.
// \param:
//    src: the pointer to a UTF-8 string.
// \returns:
//    Returns a String value, or NULL if the string can not be constructed.
JSValueRef JSNINewStringFromUtf8(JSNIEnv* env, const char* src, size_t length);

// \summary:
//    Returns the length in bytes of the UTF-8 representation of a string.
// \param:
//    string: a JavaScript string value.
// \returns:
//    Returns the UTF-8 length of the string.
size_t JSNIGetStringUtf8Length(JSNIEnv* env, JSValueRef string);

// \summary:
//    Copyies a JavaScript string into a UTF-8 encoding string buffer.
// \param:
//    string: a JavaScript string value.
//    copy: the buffer copied to.
// \returns:
//    Returns the size of copied.
size_t JSNIGetStringUtf8Chars(JSNIEnv* env,
                              JSValueRef string,
                              char* copy,
                              size_t length);

// Object Operations

// \summary:
//    Tests whether a JavaScript value is a JavaScript object.
// \param:
//    val: a JavaScript value.
// \returns:
//    Returns true if val is a JavaScript object.
bool JSNIIsObject(JSNIEnv* env, JSValueRef val);

// \summary:
//    Tests whether a JavaScript value is empty.
// \param:
//    val: a JavaScript value.
// \returns:
//    Returns true if val is empty.
bool JSNIIsEmpty(JSNIEnv* env, JSValueRef val);

// \summary:
//    Constructs a JavaScript object.
// \param:
//    None.
// \returns:
//    Returns a JavaScript object.
JSValueRef JSNINewObject(JSNIEnv* env);

// \summary:
//    Tests whether a JavaScript object has a property named name.
// \param:
//    object: a JavaScript object.
//    name: a property name.
// \returns:
//    Returns true if object has property named name.
bool JSNIHasProperty(JSNIEnv* env, JSValueRef object, const char* name);

// \summary:
//    Returns the property of the JavaScript object.
// \param:
//    object: a JavaScript object.
//    name: a property name.
// \returns:
//    Returns the property of the JavaScript object.
JSValueRef JSNIGetProperty(JSNIEnv* env, JSValueRef object, const char* name);

// \summary:
//    Sets a property of a JavaScript object.
// \param:
//    object: a JavaScript object.
//    name: a property name.
//    property: a JavaScript value.
// \returns:
//    Returns true if the operation succeeds.
bool JSNISetProperty(JSNIEnv* env,
                     JSValueRef object,
                     const char* name,
                     JSValueRef property);

// \summary:
//    Defines a new property directly on an object, or modifies
//    an existing property on an object.
// \param:
//    object: the object on which to define the property.
//    name: the name of the property to be defined or modified.
//    descriptor: the descriptor for the property being defined or modified.
// \returns:
//    Returns true on success.
bool JSNIDefineProperty(JSNIEnv* env,
                        JSValueRef object,
                        const char* name,
                        const JSNIPropertyDescriptor descriptor);

// \summary:
//    Deletes the property of a JavaScript object.
// \param:
//    object: a JavaScript object.
//    name: a property name.
// \returns:
//    Returns true if the operation succeeds.
bool JSNIDeleteProperty(JSNIEnv* env, JSValueRef object, const char* name);

// \summary:
//    Returns a prototype of a JavaScript object.
// \param:
//    object: a JavaScript object.
// \returns:
//    Returns a JavaScript value.
JSValueRef JSNIGetPrototype(JSNIEnv* env, JSValueRef object);

// \summary:
//    Constructs a JavaScript object with internal field.
//    Internal field is a raw C pointer which can not be
//    get in JavaScript.
// \param:
//    count: a number of internal fields.
// \returns:
//    Returns a JavaScript object.
JSValueRef JSNINewObjectWithInternalField(JSNIEnv* env, int count);

// \summary:
//    Gets the number of the internal field fo a JavaScript object.
// \param:
//    object: a JavaScript object.
// \returns:
//    Returns the number of the internal internal field.
int JSNIInternalFieldCount(JSNIEnv* env, JSValueRef object);

// \summary:
//    Sets an internal field of a JavaScript object.
// \param:
//    object: a JavaScript object.
//    index: index of an internal field.
//    field: an internal field. This is a raw C pointer,
//           and it will not be freed when object is Garbage Collected.
// \returns:
//    None.
void JSNISetInternalField(JSNIEnv* env,
                          JSValueRef object,
                          int index,
                          void* field);

// \summary:
//    Gets an internal field of a JavaScript object.
// \param:
//    object: a JavaScript object.
//    index: index of an internal field.
// \returns:
//    an internal field.
void* JSNIGetInternalField(JSNIEnv* env, JSValueRef object, int index);

// \summary:
//    Tests whether a JavaScript value is Function.
// \param:
//    val: a JavaScript value.
// \returns:
//    Returns true if val is Function.
bool JSNIIsFunction(JSNIEnv* env, JSValueRef val);

// \summary:
//    Constructs a JavaScript function with callback.
// \param:
//    callback: a native callback function.
// \returns:
//    Returns a JavaScript function.
JSValueRef JSNINewFunction(JSNIEnv* env, JSNICallback callback);

// \summary:
//    Calls a JavaScript function.
// \param:
//    func: a JavaScript funciton.
//    recv: the receiver the func belongs to.
//    argc: the arguments number.
//    argv: a pointer to an array of JavaScript value.
// \returns:
//    Returns the JavaScript value returned from calling func.
JSValueRef JSNICallFunction(JSNIEnv* env,
                            JSValueRef func,
                            JSValueRef recv,
                            int argc,
                            JSValueRef* argv);


// \summary:
//    Tests whether a JavaScript value is Array.
// \param:
//    val: a JavaScript value.
// \returns:
//    Returns true if val is Array.
bool JSNIIsArray(JSNIEnv* env, JSValueRef val);

// \summary:
//    Returns the number of elements in the array.
// \param:
//    array: a JavaScript array.
// \returns:
//    Returns the length of the array.
size_t JSNIGetArrayLength(JSNIEnv* env, JSValueRef array);

// \summary:
//    Constructs a JavaScript array with initial length: initial_length.
// \param:
//    initial_length: initial array size.
// \returns:
//    Returns a JavaScript array object, or NULL if the operation fails.
JSValueRef JSNINewArray(JSNIEnv* env, size_t initial_length);

// \summary:
//    Returns an element of a JavaScript array.
// \param:
//    array: a JavaScript array.
//    index: array index.
// \returns:
//    Returns a JavaScript value.
JSValueRef JSNIGetArrayElement(JSNIEnv* env, JSValueRef array, size_t index);

// \summary:
//    Sets an element of a JavaScript array.
// \param:
//    array: a JavaScript array.
//    index: a array index.
//    value: a new value.
// \returns:
//    None.
void JSNISetArrayElement(JSNIEnv* env,
                         JSValueRef array,
                         size_t index,
                         JSValueRef value);

// \summary:
//    Tests whether a JavaScript value is TypedArray.
// \param:
//    val: a JavaScript value.
// \returns:
//    Returns true if val is TypedArray.
bool JSNIIsTypedArray(JSNIEnv* env, JSValueRef val);

// \summary:
//    Constructs a JavaScript TypedArray object.
// \param:
//    type: the type of the array.
//    data: the pointer to the data buffer of the array.
//    length: the length of the array.
// \returns:
//    Returns a JavaScript TypedArray object.
JSValueRef JSNINewTypedArray(JSNIEnv*,
                             JsTypedArrayType type,
                             void* data,
                             size_t length);

// \summary:
//    Returns the type of the JavaScript TypedArray value.
// \param:
//    typed_array: a JavaScript TypedArray value.
// \returns:
//    Returns the type of the JavaScript TypedArray value.
JsTypedArrayType JSNIGetTypedArrayType(JSNIEnv* env, JSValueRef typed_array);

// \summary:
//    Returns the pointer to the buffer of TypedArray data.
// \param:
//    typed_array: a JavaScript TypedArray value.
// \returns:
//    Returns the pointer to the buffer of TypedArray data.
void* JSNIGetTypedArrayData(JSNIEnv* env, JSValueRef typed_array);

// \summary:
//    Returns the number of elements in the TypedArray value.
// \param:
//    typed_array: a JavaScript TypedArray value.
// \returns:
//    Returns the length of the TypedArray value.
size_t JSNIGetTypedArrayLength(JSNIEnv* env, JSValueRef typed_array);

// Reference

// \summary:
//    Creates a local reference scope, and then all local references will
//    be allocated within this reference scope until the reference scope
//    is deleted using PoplocalScope() or another local reference scope
//    is created.
// \param:
//    None.
// \returns:
//    None.
void JSNIPushLocalScope(JSNIEnv* env);

// \summary:
//    Pops off the current local reference scope, frees all the local
//    references in the local reference scope.
// \param:
//    None.
// \returns:
//    None.
void JSNIPopLocalScope(JSNIEnv* env);

// \summary:
//    Creates a local reference scope, and then all local references will
//    be allocated within this reference scope until the reference scope
//    is deleted using PopEscapableLocalScope() or another local reference scope
//    is created.
// \param:
//    None.
// \returns:
//    None.
void JSNIPushEscapableLocalScope(JSNIEnv* env);

// \summary:
//    Pops off the current local reference scope, frees all the local
//    references in the local reference scope, and returns a local reference
//    in the previous local scope for the given val JavaScript value.
// \param:
//    val: a JavaScript value.
// \returns:
//    Returns a JavaScript value.
JSValueRef JSNIPopEscapableLocalScope(JSNIEnv* env, JSValueRef val);

// \summary:
//    Creates a new global reference to the JavaScript value referred to by
//    the val argument. The global value must be explicitly disposed of by
//    calling DeleteGlobalValue(), except that the global value is set
//    by calling SetGCCallback(). The global value will be alive
//    untile calling DeleteGlobalValue() to dispose it.
// \param:
//    val: a JavaScript value.
// \returns:
//    Returns a global value.
JSGlobalValueRef JSNINewGlobalValue(JSNIEnv* env, JSValueRef val);

// \summary:
//    Deletes the global reference pointed by val.
// \param:
//    val: a JSGlobalValueRef value.
// \returns:
//    None.
void JSNIDeleteGlobalValue(JSNIEnv* env, JSGlobalValueRef val);

// \summary:
//    Returns a local JSValueRef value from a JSGlobalValueRef value.
// \param:
//    val: a JSGlobalValueRef value.
// \returns:
//    Returns a local JSValueRef value.
JSValueRef JSNIGetGlobalValue(JSNIEnv* env, JSGlobalValueRef val);

// \summary:
//    Sets a callback which will be called
//    when the JavaScript value pointed by val is freed.
//    The developer can pass an argument to callback by args.
// \param:
//    val: a JSGlobalValueRef value.
//    args: a pointer to an argument passed to callback.
//    callback: a function callback.
// \returns:
//    None.
void JSNISetGCCallback(JSNIEnv* env,
                       JSGlobalValueRef val,
                       void* args,
                       JSNIGCCallback callback);

// Exception

// \summary:
//    Constructs an error object with the message specified by errmsg
//    and causes that error to be thrown. It throws a JavaScript Exception.
// \param:
//    errmsg: an error message.
// \returns:
//    None.
void JSNIThrowErrorException(JSNIEnv* env, const char* errmsg);

// \summary:
//    Constructs an type error object with the message specified by errmsg
//    and causes that type error to be thrown. It throws a JavaScript Exception.
// \param:
//    errmsg: an error message.
// \returns:
//    None.
void JSNIThrowTypeErrorException(JSNIEnv* env, const char* errmsg);

// \summary:
//    Constructs an range error object with the message specified by errmsg
//    and causes that type error to be thrown. It throws a JavaScript Exception.
// \param:
//    errmsg: an error message.
// \returns:
//    None.
void JSNIThrowRangeErrorException(JSNIEnv* env, const char* errmsg);

// \summary:
//    Tests whether there is error occured during pervious JSNI call. After
//    calling JSNIGetLastErrorInfo(), if there is error occured, the error
//    will be cleared.
// \param:
//    None.
// \returns:
//    Returns true if there is error occured during previous JSNI call.
JSNIErrorInfo JSNIGetLastErrorInfo(JSNIEnv* env);

// \summary:
//    Tests whether a JavaScript exception is being thrown.
//    It's different with error get from JSNIGetLastErrorInfo.
//    Eorror is defined by JSNI, whereas this is a JavaScript exception.
// \param:
//    None.
// \returns:
//    Returns true if a JavaScript exception is being thrown.
bool JSNIHasException(JSNIEnv* env);

// \summary:
//    Clear a JavaScript exception that is being thrown. If there
//    is no exception, this routine has no effect.
// \param:
//    None.
// \returns:
//    None.
void JSNIClearException(JSNIEnv* env);

#if defined(__cplusplus)
}
#endif

/*
 * Extended jsni_env which contains functions table pointer.
 */
struct _JSNIEnv {
  // No specific thing here.
  void* reserved;
};

// JSNI Versions.
#define JSNI_VERSION_1_0 0x00010000
#define JSNI_VERSION_1_1 0x00010001
#define JSNI_VERSION_2_0 0x00020000

#if defined(__cplusplus)
extern "C" {
#endif
/*
 * This function is called by JSNI, not part of JSNI.
 */
int JSNIInit(JSNIEnv* env, JSValueRef exports);

#if defined(__cplusplus)
}
#endif


#endif  // INCLUDE_JSNI_H_
