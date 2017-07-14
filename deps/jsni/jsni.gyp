{
  'targets': [
    {
      'target_name': 'jsni',
      'type': 'static_library',
      'dependencies': ['../v8/tools/gyp/v8.gyp:v8'],
      'cflags': [],
      'direct_dependent_settings': {
        'include_dirs': ['include'],
      },
      'include_dirs': ['.',
        'include',
        '../v8',
        '../../src/',
        '../uv/src/ares',
        '<(SHARED_INTERMEDIATE_DIR)',
        '../uv/include',
        '../cares/include'
      ],
      'sources': [
        'src/v8/jsni.cc',
        'src/v8/jsni-nativeload.cc',
      ],
      'link_settings': {
        'libraries': [
          '-ldl',
          '-lrt',
          '-lgcov'
        ],
        },
      "cflags" : ["-fprofile-arcs -ftest-coverage"],
      "ldflags" : ["-lgcov --coverage"],
    },
  ],
}
