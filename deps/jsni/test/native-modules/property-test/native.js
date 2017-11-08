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

var assert = require("assert");
const native = nativeLoad("native");

// Test getter and setter.
var obj = {};
native.testDefineProperty(obj);

assert.strictEqual(obj.abc, 101);
obj.abc = 1000;
assert.strictEqual(obj.abc, 1001);
assert.strictEqual(obj.getter, "getter is set.");
assert.strictEqual(obj.setter, "setter is set.");

// Test define property.
var testPropertyObject = {};
native.testDefineProperty2(testPropertyObject);

// Writable
assert.strictEqual(testPropertyObject.readWrite, 1);
testPropertyObject.readWrite = 2;
assert.strictEqual(testPropertyObject.readWrite, 2);

assert.strictEqual(testPropertyObject.readOnly, 1);
assert.throws(
  () => { "use strict"; testPropertyObject.readOnly = 2; },
  TypeError,
  "The property is read only."
);

// Enumerable
assert.strictEqual(testPropertyObject.propertyIsEnumerable("enumerable"), true);
assert.strictEqual(testPropertyObject.propertyIsEnumerable("notEnumerable"), false);

// Configurable
delete testPropertyObject.deletable;
assert.strictEqual(testPropertyObject.deletable, undefined);

delete testPropertyObject.notDeletable;
assert.strictEqual(testPropertyObject.notDeletable, 1);
assert.throws(
  () => {
    Object.defineProprety(testPropertyObject, "notDeletable", {
      configurable: true
    })
  },
  TypeError,
  "The property is not configurable(deletable)."
)

process.exit();
