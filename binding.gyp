{
    'targets': [
        {
            'target_name': 'napi-abe',
            'sources': ['src/napi-abe.cc'],
            'include_dirs': [
                '<!@(node -p \'require("node-addon-api").include\')',
                '<(module_root_dir)/src/',
            ],
            'cflags': ['-fexceptions','-frtti','-no-pie'],
            'cflags_cc': ['-fexceptions', '-frtti', '-std=c++14', '-lopenabe',
            '-lcrypto', '-lrelic', '-lrelic_ec',
            '-no-pie'],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
            'libraries': [
                '/usr/local/lib/libopenabe.so',
                '/usr/local/lib/librelic.so',
                '/usr/local/lib/librelic_ec.so',
                '/usr/lib/libgmp.so',
                '/usr/lib/libgmpxx.so'],
        }
    ]
}
