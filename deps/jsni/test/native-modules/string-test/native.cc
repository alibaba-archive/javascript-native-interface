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
#include <string.h>
#include <stdio.h>

void testUtf8(JSNIEnv* env, JSNICallbackInfo info) {
  if (JSNIGetArgsLengthOfCallback(env, info) < 1) {
    JSNIThrowRangeErrorException(env, "Arguments should be more than 0.");
  }
  JSValueRef string = JSNIGetArgOfCallback(env, info, 0);
  assert(JSNIIsString(env, string));
  const char* native_str = "hello, world!";
  const size_t string_length = strlen(native_str);

  JSValueRef str_val = JSNINewStringFromUtf8(env, native_str, string_length);
  assert(JSNIGetStringUtf8Length(env, str_val) == string_length);

  char c_string[string_length + 1];
  JSNIGetStringUtf8Chars(env, str_val, c_string, string_length + 1);
  for (size_t i = 0; i < string_length + 1; i++) {
    assert(c_string[i] == native_str[i]);
  }

  JSNISetReturnValue(env, info, str_val);
}

void testNewStringUtf8(JSNIEnv* env, JSNICallbackInfo info) {
  if (JSNIGetArgsLengthOfCallback(env, info) < 1) {
    JSNIThrowRangeErrorException(env, "Arguments should be more than 0.");
  }
  JSValueRef string = JSNIGetArgOfCallback(env, info, 0);
  assert(JSNIIsString(env, string));

  size_t string_length = JSNIGetStringUtf8Length(env, string);
  char c_string[string_length];
  JSNIGetStringUtf8Chars(env, string, c_string, string_length + 1);

  JSValueRef new_string = JSNINewStringFromUtf8(env, c_string, string_length);
  JSNISetReturnValue(env, info, new_string);
}


int JSNIInit(JSNIEnv* env, JSValueRef exports) {
  JSNIRegisterMethod(env, exports, "testUtf8", testUtf8);
  JSNIRegisterMethod(env, exports, "testNewStringUtf8", testNewStringUtf8);
  return JSNI_VERSION_2_0;
}
