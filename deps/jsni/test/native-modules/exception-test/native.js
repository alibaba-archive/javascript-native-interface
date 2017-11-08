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

"use strict";

var assert = require("assert");
const native = nativeLoad("native");
var str = "string";

assert.throws(
  () => {
    native.throwTypeError(str);
  },
  function(error) {
    return error.toString() === "TypeError: Wrong parameter type."
  },
  "TypeError should be thrown."
)

assert.throws(
  () => {
    native.throwRangeError(str);
  },
  function(error) {
    return error.toString() === "RangeError: Range is out of limit."
  },
  "RangeError should be thrown."
)

assert.throws(
  () => {
    native.throwError(str);
  },
  function(error) {
    return error.toString() === "Error: Error."
  },
  "Error should be thrown."
)

// Check pending exception and clear pending exception.
var err = new Error("error.");
function throwError() {
  throw err;
}

assert.throws(
  () => {
    native.hasPendingException(throwError);
  },
  function(error) {
    return error === err;
  },
  "Pending exception should be caught."
);

assert.doesNotThrow(
  () => {
    native.clearPendingException(throwError);
  },
  Error,
  "No error should be catched."
)

process.exit();
