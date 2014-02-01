/*!
 * ribs
 * Copyright (c) 2014 Nicolas Gryman <ngryman@gmail.com>
 * LGPL Licensed
 */

#include "../io.h"

using namespace std;
using namespace ribs;

#ifdef USE_LIBUV

#include <uv.h>

struct Baton {
	Callback<pixels> callback;
	uv_fs_t          fs;
	uv_file          fd;
	uv_work_t        work;
	vector<uint8_t>  buffer;
	pixels           data;

	Baton(Callback<pixels> callback) :
	    callback(callback) {
		buffer.reserve(IO_CHUNK_SIZE);
	}
};

static void OnOpen(uv_fs_t* req);
static void OnRead(uv_fs_t* req);
static void BeginDecode(Baton* baton);
static void DecodeAsync(uv_work_t* req);
static void OnDecoded(uv_work_t* req);
static void Close(uv_fs_t* req);
static void Done(const Error& error, Baton* baton);

void IO::Read(const string& filename, Callback<pixels> callback) {
	// allocate baton, handle potential out of memory
	Baton* baton;
	try {
		baton = new Baton(callback);
	}
	catch (const bad_alloc& ex) {
		return callback(Error::NoMemory, NULL);
	}

	// open the file async
	uv_fs_open(uv_default_loop(), &baton->fs, filename.c_str(), 0 /* O_RDONLY */, 0, OnOpen);
}

void OnOpen(uv_fs_t* req) {
	Baton* baton = static_cast<Baton*>(req->data);

	if (req->result < 0) {
		uv_fs_req_cleanup(req);
		return Done(Error(ErrorType::FileRead, uv_strerror(req->result)), baton);
	}

	// stores file descriptor for further reads
	baton->fd = req->result;

	// read the file async
	uv_fs_req_cleanup(req);
	uv_fs_read(uv_default_loop(),
		&baton->fs,
		baton->fd,
		&baton->buffer[0],
		IO_CHUNK_SIZE,
		0,
		OnRead);
}

void OnRead(uv_fs_t* req) {
	Baton* baton = static_cast<Baton*>(req->data);

	if (req->result < 0) {
		return Done(Error(ErrorType::FileRead, uv_strerror(req->result)), baton);
	}

	// increase vector's capacity for next read,
	// handle potential out of memory
	const size_t size = baton->buffer.size();
	try {
		baton->buffer.resize(size + IO_CHUNK_SIZE);
	}
	catch (const bad_alloc& ex) {
		uv_fs_req_cleanup(req);
		return Done(Error::NoMemory, NULL);
	}

	// schedule a new read if all the buffer was read
	if (req->result == IO_CHUNK_SIZE) {
		uv_fs_req_cleanup(req);
		uv_fs_read(uv_default_loop(),
			&baton->fs,
			baton->fd,
			&baton->buffer[size],
			IO_CHUNK_SIZE,
			size,
			OnRead);
	}
	else {
		Close(req);
		BeginDecode(baton);
	}
}

void Close(uv_fs_t* req) {
	Baton* baton = static_cast<Baton*>(req->data);

	// close file sync
	// it's a quick operation that does not need threading overhead
	uv_fs_req_cleanup(req);
	int err = uv_fs_close(uv_default_loop(), req, baton->fd, NULL);

	// fail silently
	if (-1 == err) {
		// TODO: log warning
		//baton->result.error = RibsError("Error closing file", uv_strerror(uv_last_error(uv_default_loop())));
		uv_fs_req_cleanup(req);
	}
}

void BeginDecode(Baton* baton) {
	// reference baton in the request
	baton->work.data = baton;
	// pass the request to libuv to be run when a worker-thread is available to
	uv_queue_work(
		uv_default_loop(),
		&baton->work,
		DecodeAsync,
		(uv_after_work_cb)OnDecoded
	);
}

void DecodeAsync(uv_work_t* req) {
	Baton* baton = static_cast<Baton*>(req->data);
//	baton->data = imdecode(&baton->buffer[0], CV_LOAD_IMAGE_ANYDEPTH);
}

void OnDecoded(uv_work_t* req) {
	Baton* baton = static_cast<Baton*>(req->data);

	// check if image was decoded correctly
	if (NULL == baton->data) {
		return Done(Error::InvalidFormat, NULL);
	}

	Done(Error::Success, baton);
};

void Done(const Error& error, Baton* baton) {
//	if (Error::Success != error.type) {
//	}

	// ensure baton is destroyed, even if an exception is raised
	// RAII benediction ;)
	auto_ptr<Baton> p(baton);

	// forward result to the callback
	baton->callback(error, baton->data);
}

#else

void IO::Read(const string& filename, Callback<pixels> callback) {
//	Mat m = imread(filename, CV_LOAD_IMAGE_ANYDEPTH);
//	pixels* pixel = static_cast<pixels*>(m.data);
	pixels pix;
	callback(ErrorType::Success, pixels);
}

#endif