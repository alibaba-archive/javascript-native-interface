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

#include "src/isolate.h"
#include "src/api.h"


#include "src/handles-inl.h"
#include "src/heap/heap.h"
#include "src/heap/heap-inl.h"

#include "jsni-env-ext.h"

namespace v8 {

JsLocalScope::JsLocalScope(internal::Isolate* isolate) {
  Initialize(isolate);
}

void JsLocalScope::Initialize(internal::Isolate* isolate) {
  i::HandleScopeData* current = isolate->handle_scope_data();
  prev_next_ = current->next;
  prev_limit_ = current->limit;
  current->level++;
}

JsEscapableLocalScope::JsEscapableLocalScope(internal::Isolate* isolate) {
  internal::Object* value = reinterpret_cast<internal::Object*>(
                     isolate->heap()->the_hole_value());
  escape_slot_ = internal::HandleScope::CreateHandle(
                 isolate,
                 value);
  Initialize(isolate);
}

JSNIEnvExt* JSNIEnvExt::Create(internal::Isolate* isolate) {
  return new JSNIEnvExt(isolate);
}

JSNIEnvExt::JSNIEnvExt(internal::Isolate* isolate)
      : isolate_(isolate), error_code(0) {
}

internal::Isolate* JSNIEnvExt::GetIsolate() {
  return isolate_;
}

}  // namespace v8
