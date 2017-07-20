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

#include <jsni.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

void createTypedArray(JSNIEnv* env, JSNICallbackInfo info) {
  uint8_t a[] = {1, 2, 3};
  uint8_t* new_array = static_cast<uint8_t*>(malloc(sizeof a));
  memcpy(new_array, a, sizeof a);
  JSValueRef js_typed_array =
    JSNINewTypedArray(env, JsArrayTypeUint8,
                      reinterpret_cast<char*>(new_array), sizeof a);

  assert(JSNIIsTypedArray(env, js_typed_array));
  assert(JSNIGetTypedArrayType(env, js_typed_array) == JsArrayTypeUint8);
  uint8_t* data =
    reinterpret_cast<uint8_t*>(JSNIGetTypedArrayData(env, js_typed_array));
  size_t len = JSNIGetTypedArrayLength(env, js_typed_array);
  assert(len = 3);
  assert(data[0] == 1);
  assert(data[1] == 2);
  assert(data[2] == 3);

  JSNISetReturnValue(env, info, js_typed_array);
}

void testIsArray(JSNIEnv* env, JSNICallbackInfo info) {
  JSValueRef check = JSNIGetArgOfCallback(env, info, 0);
  assert(JSNIIsArray(env, check));
}

int JSNIInit(JSNIEnv* env, JSValueRef exports) {
  JSNIRegisterMethod(env, exports, "createTypedArray", createTypedArray);
  JSNIRegisterMethod(env, exports, "testIsArray", testIsArray);
  return JSNI_VERSION_2_0;
}
