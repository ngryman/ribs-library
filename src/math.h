/*!
 * ribs
 * Copyright (c) 2013 Nicolas Gryman <ngryman@gmail.com>
 * LGPL Licensed
 */

#ifndef __RIBS_MATH_H__
#define __RIBS_MATH_H__

#include "error.h"

namespace ribs {

class Math {
public:
	static void coordinates(Origin origin, uint32_t width, uint32_t height, uint32_t* x, uint32_t* y);
};

}

#endif