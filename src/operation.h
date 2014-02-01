/*!
 * ribs
 * Copyright (c) 2013 Nicolas Gryman <ngryman@gmail.com>
 * LGPL Licensed
 */

#ifndef __RIBS_OPERATION_H__
#define __RIBS_OPERATION_H__

#include "image.h"

namespace ribs {

class Operation {
public:
	static void Resize(Image* image, uint32_t width, uint32_t height, uint32_t x, uint32_t y, Callback<Image&> callback);
	static void Crop(Image* image, uint32_t width, uint32_t height, uint32_t x, uint32_t y, Callback<Image&> callback);
};

}

#endif