{
    'targets': [
        {
            'target_name': 'napi-abe',
            'sources': ['src/napi-abe.cc'],
            'include_dirs': [
                '<!@(node -p \'require("node-addon-api").include\')',
                '<(module_root_dir)/external/',
                '<(module_root_dir)/src/',
                '/Users/hal/.nvm/versions/node/v12.17.0/lib/node_modules/node-addon-api',
                '/Users/hal/.nvm/versions/node/v12.17.0/include/node',
                '/Users/hal/include',
                '/Users/hal/workspace/abeJS/src',
            ],
            'cflags!': ['-fexceptions','-frtti'],
            'cflags_cc!': ['-fexceptions', '-frtti', '-std=c++14', '-lopenabe',
            '-lcrypto', '-lrelic', '-lrelic_ec',
            '-L/Users/hal/lib'],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
            'libraries': ['/Users/hal/lib/libopenabe.a',
                '/Users/hal/lib/librelic_s.a',
                '/Users/hal/lib/librelic_s_ec.a',
                '/usr/local/lib/libgmp.a',
                '/usr/local/lib/libgmpxx.a'],
            'conditions': [
                [
                    'OS=="mac"',
                    {
                        'xcode_settings': {
                            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                            'GCC_ENABLE_CPP_RTTI': 'YES',
                            'CLANG_CXX_LIBRARY': 'libc++',
                            'CLANG_CXX_LANGUAGE_STANDARD': 'c++14',
                            'MACOSX_DEPLOYMENT_TARGET': '10.15'
                        }
                    },
                ]
            ],
        }
    ]
}
