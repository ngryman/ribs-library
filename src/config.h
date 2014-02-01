/*!
 * ribs
 * Copyright (c) 2014 Nicolas Gryman <ngryman@gmail.com>
 * LGPL Licensed
 */

#ifndef __RIBS_CONFIG_H__
#define __RIBS_CONFIG_H__

namespace ribs {

//#define USE_OPENCV

#define USE_LIBUV

// TODO: benchmark this size
// TODO: when custom allocator will be implemented, perhaps a big increase would be possible
#define IO_CHUNK_SIZE   32 * 1024

}

#endif