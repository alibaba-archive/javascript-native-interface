var nativeCache = {}
const path = require('path');

exports.nativeLoad = function(filename) {
  var Module = require("module");
  var filename_resolved = Module._findPath(filename, [path.resolve(".")]);

  var cachedNative = nativeCache[filename_resolved];
  if (cachedNative) {
    return cachedNative;
  }

  var native_exports = {};

  nativeCache[filename_resolved] = native_exports;
  var hadException = true;
  try {
    process.nativeLoad(native_exports, filename_resolved);
    hadException = false;
  } finally {
    if (hadException) {
      delete nativeCache[filename_resolved];
    }
  }

  return native_exports;
}

