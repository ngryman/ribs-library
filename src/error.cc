/*!
 * ribs
 * Copyright (c) 2013 Nicolas Gryman <ngryman@gmail.com>
 * LGPL Licensed
 */

#include "error.h"

using namespace std;
using namespace ribs;

static const string ERROR_MESSAGES[] = {
    "Success",
    "Invalid argument",
    "Out of memory",
    "Can't read file",
    "Can't write file",
    "Invalid image format"
};

static const Error Success(ErrorType::Success);
static const Error NoMemory(ErrorType::NoMemory);
static const Error InvalidFormat(ErrorType::InvalidFormat);

Error::Error(ErrorType type) {
	m = ERROR_MESSAGES[static_cast<int>(type)];
}

Error::Error(ErrorType type, const string& info) {
	m = ERROR_MESSAGES[static_cast<int>(type)] + ": " + info;
}