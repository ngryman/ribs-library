/*!
 * ribs
 * Copyright (c) 2014 Nicolas Gryman <ngryman@gmail.com>
 * LGPL Licensed
 */

#ifndef __RIBS_IO_H__
#define __RIBS_IO_H__

#include "error.h"

namespace ribs {

class IO {
public:
	static void Read(const std::string& filename, Callback<pixels> callback);
	static void Write(const std::string& filename, Callback<pixels> callback);
};

}

#endif