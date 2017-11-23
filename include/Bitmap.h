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

namespace bitmap {

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
	std::unique_ptr<uint8_t[]> pixels;

public:
	Bitmap(uint32_t width, uint32_t height) :
		width(width),
		height(height),
		pixels(make_unique<uint8_t[]>(width*height*3)) {
	};
	void setPixel(int x, int y, int red, int green, int blue);
	void write(const std::string& filename);
};

} // namespace bitmap

#endif /* BITMAP_H_ */
