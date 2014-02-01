/*!
 * ribs
 * Copyright (c) 2013 Nicolas Gryman <ngryman@gmail.com>
 * LGPL Licensed
 */

#ifndef __RIBS_COMMON_H__
#define __RIBS_COMMON_H__

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "config.h"

namespace ribs {

//using Pixels = cv::Mat;
typedef uint8_t* pixels;

enum Origin {
	Center,
	TopLeft,
	Top,
	TopRight,
	Right,
	RightBottom,
	Bottom,
	LeftBottom,
	Left
};

class Error;

template<class T>
struct Callback : std::function<void(const Error&, T)> {};

}

#endif