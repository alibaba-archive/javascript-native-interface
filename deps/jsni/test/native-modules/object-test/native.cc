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

#include <assert.h>
#include <jsni.h>

void testObject(JSNIEnv* env, JSNICallbackInfo info) {
  JSValueRef obj = JSNINewObject(env);
  assert(JSNIIsObject(env, obj));
  assert(!JSNIIsEmpty(env, obj));

  JSValueRef property1 = JSNINewNumber(env, 100);
  JSNISetProperty(env, obj, "property1", property1);
  assert(JSNIHasProperty(env, obj, "property1"));

  JSValueRef get_property1 = JSNIGetProperty(env, obj, "property1");
  assert(JSNIIsNumber(env, get_property1));
  assert(JSNIToCDouble(env, get_property1) == 100);

  JSNIDeleteProperty(env, obj, "property1");
  assert(!JSNIHasProperty(env, obj, "property1"));
}

void testObjectGet(JSNIEnv* env, JSNICallbackInfo info) {
  if (JSNIGetArgsLengthOfCallback(env, info) < 2) {
    JSNIThrowRangeErrorException(env, "Arguments should be more than or equal 2.");
  }
  JSValueRef arg0 = JSNIGetArgOfCallback(env, info, 0);
  JSValueRef arg1 = JSNIGetArgOfCallback(env, info, 1);
  size_t string_length = JSNIGetStringUtf8Length(env, arg1);
  char name[string_length + 1];
  JSNIGetStringUtf8Chars(env, arg1, name, string_length + 1);
  JSValueRef property = JSNIGetProperty(env, arg0, name);
  JSNISetReturnValue(env, info, property);
}

void testObjectHas(JSNIEnv* env, JSNICallbackInfo info) {
  if (JSNIGetArgsLengthOfCallback(env, info) < 2) {
    JSNIThrowRangeErrorException(env, "Arguments should be more than or equal 2.");
  }
  JSValueRef arg0 = JSNIGetArgOfCallback(env, info, 0);
  JSValueRef arg1 = JSNIGetArgOfCallback(env, info, 1);
  size_t string_length = JSNIGetStringUtf8Length(env, arg1);
  char name[string_length + 1];
  JSNIGetStringUtf8Chars(env, arg1, name, string_length + 1);
  bool has_property = JSNIHasProperty(env, arg0, name);
  JSValueRef js_has_property = JSNINewBoolean(env, has_property);
  JSNISetReturnValue(env, info, js_has_property);
}

void testObjectGetProto(JSNIEnv* env, JSNICallbackInfo info) {
  JSValueRef obj = JSNIGetArgOfCallback(env, info, 0);
  JSValueRef proto = JSNIGetPrototype(env, obj);
  JSNISetReturnValue(env, info, proto);
}

int JSNIInit(JSNIEnv* env, JSValueRef exports) {
  JSNIRegisterMethod(env, exports, "testObject", testObject);
  JSNIRegisterMethod(env, exports, "testObjectGetProto", testObjectGetProto);
  JSNIRegisterMethod(env, exports, "testObjectHas", testObjectHas);
  JSNIRegisterMethod(env, exports, "testObjectGet", testObjectGet);
  return JSNI_VERSION_2_0;
}
