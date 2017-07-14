{
  "targets": [
    {
      "target_name": "native",
      "sources": [ "native.cc"],
      "include_dirs": ["../../include"],
      "cflags" : ["-fprofile-arcs -ftest-coverage"],
      "ldflags" : ["-lgcov --coverage"],
    }
  ]
}
