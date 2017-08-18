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

#include "myobject.h"
#include <stdio.h>

JSValueRef MyObject::NewInstance(JSNIEnv* env, double counter) {
  MyObject* obj = new MyObject();
  obj->counter = counter;
  JSValueRef instance = JSNINewObjectWithInternalField(env, 1);
  JSNISetInternalField(env, instance, 0, obj);

  // Set c++ member methods to js object.
  JSValueRef func = JSNINewFunction(env, MyObject::PlusOne);
  JSNISetProperty(env, instance, "plusOne", func);

  // Set the desctructor.
  JSGlobalValueRef wrapper = JSNINewGlobalValue(env, instance);
  JSNISetGCCallback(env, wrapper, obj, MyObject::Destructor);

  return instance;
}

void MyObject::Destructor(JSNIEnv* env, void* info) {
  MyObject* obj = reinterpret_cast<MyObject*>(info);
  delete obj;
}

void MyObject::PlusOne(JSNIEnv* env, JSNICallbackInfo info) {
  JSValueRef jsthis = JSNIGetThisOfCallback(env, info);
  MyObject* obj = reinterpret_cast<MyObject*>(
    JSNIGetInternalField(env, jsthis, 0));
  obj->counter ++;
  JSNISetReturnValue(env, info, JSNINewNumber(env, obj->counter));
}