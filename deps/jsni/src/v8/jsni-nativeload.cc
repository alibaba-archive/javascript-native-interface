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

#include <dlfcn.h>
#include "jsni-nativeload.h"

#include "src/isolate.h"
#include "src/api.h"


#include "src/handles-inl.h"
#include "src/heap/heap.h"
#include "src/heap/heap-inl.h"

#include "jsni-env-ext.h"

using namespace v8;

// For calling nativeLoad(exports, path):
// exports: the exports module JS object.
// path: the resolved filename.
static void JSNINativeLoad(JSNIEnv* env, JSNICallbackInfo info) {
  JSValueRef exports = JSNIGetArgOfCallback(env, info, 0);
  JSValueRef path = JSNIGetArgOfCallback(env, info, 1);
  Local<Value> v8_path = *reinterpret_cast<Local<Value>*>(&path);
  String::Utf8Value filename(v8_path);

  void* handle = dlopen(*filename, RTLD_LAZY);

  if (handle == nullptr) {
    char errmsg[1024];
    snprintf(errmsg,
             sizeof(errmsg),
             "Can not open native module: %s. %s",
             *filename, dlerror());
    JSNIThrowErrorException(env, errmsg);
    return;
  }

  // Call JSNIInit to Register native methods.
  typedef int (*JSNIInitFn) (void*, JSValueRef);
  void* ptr = nullptr;
  ptr = dlsym(handle, "JSNIInit");

  if (ptr != nullptr) {
    JSNIInitFn jsni_init = reinterpret_cast<JSNIInitFn>(ptr);
    int version = jsni_init(env, exports);
    if (version < JSNI_VERSION_2_0) {
      char errmsg[1024];
      snprintf(errmsg,
               sizeof(errmsg),
               "Native module version mismatch. Expected >= %d, got %d.",
               JSNI_VERSION_2_0, version);
      dlclose(handle);
      JSNIThrowErrorException(env, errmsg);
      return;
    }
  } else {
    dlclose(handle);
    JSNIThrowErrorException(env,
      "Native module has no declared entry point: JSNIInit.");
    return;
  }
}

int RegisterJSNINativeLoad(JSNIEnv* env, JSValueRef exports) {
  JSNIRegisterMethod(env, exports, "nativeLoad", JSNINativeLoad);
  return JSNI_VERSION_2_0;
}

void V8RegisterJSNIEnvironment(Isolate* isolate,
                              Local<Object> native_load_holder,
                              void* reserved) {
  JSNIEnv* jsni_env = reinterpret_cast<JSNIEnv*>(isolate->GetEnv());
  JSValueRef exports = reinterpret_cast<JSValueRef>(*native_load_holder);
  RegisterJSNINativeLoad(jsni_env, exports);
}
