var nativeCache = {}
const path = require('path');
const extensions = [".node", ".so"];
const dir = path.resolve(".");
const loadPaths = [dir, dir + "/build/Release/", dir + "/build/Debug/"];

function isExtended(filename) {
  for (var i = 0; i < extensions.length; i++) {
    if (filename.endsWith(extensions[i]))
      return true
  }
  return false
}

function tryFile(filename) {
  var Module = require("module");
  return Module._findPath(
                filename,
                loadPaths);
}

exports.nativeLoad = function(filename) {
  var native_exports = {};
  var filename_resolved = false;

  if (isExtended(filename)) {
    filename_resolved = tryFile(filename);
  }

  if (filename_resolved == false) {
    for (var i = 0; i < extensions.length; i++) {
      filename_resolved = tryFile(filename + extensions[i])
      // If we find the native module, break here.
      if (filename_resolved != false)
        break;
    }   
  }

  if (filename_resolved == false) {
    var err = new Error("Cannot find native module '" + filename + "'");
    err.code = 'NATIVE_MODULE_NOT_FOUND';
    throw err;
  }

  var cachedNative = nativeCache[filename_resolved];
  if (cachedNative) {
    return cachedNative;
  }


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

