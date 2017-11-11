/*
 * Bitmap.h
 *
 *  Created on: Oct 24, 2017
 *      Author: vergel
 */

#ifndef BITMAP_H_
#define BITMAP_H_

#include <cstdint>
#include <string>
#include <memory>

#include "Rgb.h"

using namespace std;

namespace mandelbrot {

class BitmapException : public std::exception {
public:
	BitmapException(const std::string& message) noexcept :
		msg(message) {
	}
	const char* what() const noexcept {
		return msg.c_str();
	}
private:
	std::string msg;
};

class Bitmap {
private:
	uint32_t width;
	uint32_t height;
	unique_ptr<uint8_t[]> pixels;
public:
	Bitmap(uint32_t _width, uint32_t _height) :
		width(_width),
		height(_height),
		pixels(new uint8_t[_width*_height*3]{}) {};
	void setPixel(int x, int y, mandelbrot::Rgb color);
	void write(const std::string& filename);
};

} // namespace mandelbrot

#endif /* BITMAP_H_ */
