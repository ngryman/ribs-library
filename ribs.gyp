#
# ribs
# Copyright (c) 2014 Nicolas Gryman <ngryman@gmail.com>
# LGPL Licensed
#

{
    'variables': {
        'src%': '.',
        'target_arch%': 'ia32',
        'library%': 'static_library',
        'source_files': [
            'src/error.cc',
            'src/image.cc',
            'src/io.cc',
            'src/math.cc'
        ]
    },

    'targets': [{
        'target_name': 'ribs',
        'product_prefix': 'lib',
        'type': '<(library)',

        'sources': [
            '<@(source_files)'
        ],

        'dependencies': [
            'deps/libuv/uv.gyp:libuv',
        ],

        'conditions': [
            ['OS=="linux"', {
                'libraries': [
                    '-luv'
                ],
                'cflags': [
                    '-Wall -std=c++11'
                ]
            }]
        ]
    }]
}
